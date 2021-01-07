#include "timeloader.h"
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QStandardPaths>

TimeLoader::TimeLoader(QObject*pwgt)
    :QObject(pwgt)
{
#if defined (Q_OS_ANDROID)
    auto path = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    file.setFileName(path.append(("/" TIMEZONESFILENAME)));
#else
    file.setFileName(TIMEZONESFILENAME);
#endif
    manager = new QNetworkAccessManager();
    connect(manager,&QNetworkAccessManager::finished,this,
            [&](QNetworkReply *reply){
        if(reply->error())
        {
            qDebug()<<reply->errorString();
            return;
        }
        qDebug()<<"Connect";
        writeToFile(reply->readAll());
    });
}

void TimeLoader::startRequest(const QUrl &url)
{
    if(file.size()>0)
        return;

    QNetworkRequest request;
    request.setUrl(url);
    manager->get(request);
    qDebug()<<"get";
}

QByteArray TimeLoader::getTimeData()
{
    QByteArray result;
    if(file.open(QIODevice::ReadOnly))
    {
        result = file.readAll();
    }
    file.close();

    return result;
}

TimeLoader::~TimeLoader()
{
    if(file.isOpen())
        file.close();
}

void TimeLoader::writeToFile(const QByteArray &arr)
{
    qDebug()<<arr;
    if(file.open(QFile::WriteOnly))
    {
        qDebug()<<"Open";
        QTextStream out(&file);
        out<<arr;
    }
    file.close();
}
