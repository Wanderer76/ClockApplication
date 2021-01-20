#include "headers/helpers/timeloaderHelper.h"
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QStandardPaths>

TimeLoader::TimeLoader(QObject*pwgt)
    :QObject{pwgt}
{
#if defined (Q_OS_ANDROID)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    _coutriesAndRegionsFile.setFileName(path.append(("/" TIMEZONESFILENAME)));
#else
    _coutriesAndRegionsFile.setFileName(TIMEZONESFILENAME);
#endif
    _manager = new QNetworkAccessManager(this);
    connect(_manager,&QNetworkAccessManager::finished,this,&TimeLoader::finishedRegionDownload);
}

void TimeLoader::startRequest()
{

    if(_coutriesAndRegionsFile.size()>0)
        return;
    QNetworkRequest request;
    request.setUrl(QUrl("http://worldtimeapi.org/api/timezone"));
    _manager->get(request);
    qDebug()<<"get";
}



QByteArray TimeLoader::getTimeData()
{
    QByteArray result;
    if(_coutriesAndRegionsFile.open(QIODevice::ReadOnly))
    {
        result = _coutriesAndRegionsFile.readAll();
    }
    _coutriesAndRegionsFile.close();

    return result;
}

TimeLoader::~TimeLoader()
{
    if(_coutriesAndRegionsFile.isOpen())
        _coutriesAndRegionsFile.close();
}


void TimeLoader::writeToFile(const QByteArray &arr)
{

    if(_coutriesAndRegionsFile.open(QFile::WriteOnly))
    {
        qDebug()<<"Open";
        QTextStream out(&_coutriesAndRegionsFile);
        out<<arr;
    }
    _coutriesAndRegionsFile.close();
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
