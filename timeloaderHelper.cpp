#include "timeloaderHelper.h"
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QStandardPaths>

TimeLoader::TimeLoader(QObject*pwgt)
    :QObject(pwgt)
{
#if defined (Q_OS_ANDROID)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    coutriesAndRegionsFile.setFileName(path.append(("/" TIMEZONESFILENAME)));
#else
    coutriesAndRegionsFile.setFileName(TIMEZONESFILENAME);
#endif
    manager = new QNetworkAccessManager(this);
    connect(manager,&QNetworkAccessManager::finished,this,&TimeLoader::finishedRegionDownload);
}

void TimeLoader::startRequest()
{

    if(coutriesAndRegionsFile.size()>0)
        return;
    QNetworkRequest request;
    request.setUrl(QUrl("http://worldtimeapi.org/api/timezone"));
    manager->get(request);
    qDebug()<<"get";
}



QByteArray TimeLoader::getTimeData()
{
    QByteArray result;
    if(coutriesAndRegionsFile.open(QIODevice::ReadOnly))
    {
        result = coutriesAndRegionsFile.readAll();
    }
    coutriesAndRegionsFile.close();

    return result;
}

TimeLoader::~TimeLoader()
{
    if(coutriesAndRegionsFile.isOpen())
        coutriesAndRegionsFile.close();
}


void TimeLoader::writeToFile(const QByteArray &arr)
{

    if(coutriesAndRegionsFile.open(QFile::WriteOnly))
    {
        qDebug()<<"Open";
        QTextStream out(&coutriesAndRegionsFile);
        out<<arr;
    }
    coutriesAndRegionsFile.close();
}

void TimeLoader::finishedRegionDownload(QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug()<<reply->errorString();
        return;
    }
    qDebug()<<"Connect - "<<reply->readAll();
    writeToFile(reply->readAll());
}
