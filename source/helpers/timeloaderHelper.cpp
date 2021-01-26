#include "headers/helpers/timeloaderHelper.h"
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QStandardPaths>

TimeLoaderHelper::TimeLoaderHelper(QObject*pwgt)
    :QObject{pwgt}
{
#if defined (Q_OS_ANDROID)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    _coutriesAndRegionsFile.setFileName(path.append(("/" TIMEZONESFILENAME)));
#else
    _coutriesAndRegionsFile.setFileName(TIMEZONESFILENAME);
#endif
    _manager = new QNetworkAccessManager(this);
    connect(_manager,&QNetworkAccessManager::finished,this,&TimeLoaderHelper::finishedRegionDownload);
}

void TimeLoaderHelper::startRequest()
{

    if(_coutriesAndRegionsFile.size()>0)
        return;
    QNetworkRequest request;
    request.setUrl(QUrl("http://worldtimeapi.org/api/timezone"));
    _manager->get(request);
    qDebug()<<"get";
}



QByteArray TimeLoaderHelper::getTimeData()
{
    QByteArray result;

    if(_coutriesAndRegionsFile.open(QIODevice::ReadOnly))
    {
        result = (_coutriesAndRegionsFile.readAll());
    }
    _coutriesAndRegionsFile.close();

    return result;
}

TimeLoaderHelper::~TimeLoaderHelper()
{
    if(_coutriesAndRegionsFile.isOpen())
        _coutriesAndRegionsFile.close();
}


void TimeLoaderHelper::writeToFile(const QByteArray &arr)
{

    if(_coutriesAndRegionsFile.open(QFile::WriteOnly))
    {
        qDebug()<<"Open";
       _coutriesAndRegionsFile.write(arr);
    }
    _coutriesAndRegionsFile.close();
}

void TimeLoaderHelper::finishedRegionDownload(QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug()<<reply->errorString();
        return;
    }
    writeToFile(reply->readAll());

}
