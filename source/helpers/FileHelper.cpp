#include"headers/helpers/FileHelper.h"
#include<QUrl>
#include<QFileDialog>
#include<QDebug>
#include<QStandardPaths>
FileHelper::FileHelper(QObject *pwgt)
    :QObject(pwgt)
{
}

FileHelper::~FileHelper()
{

}


QUrl FileHelper::getUrl()
{
    auto dir = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);
    auto url = QFileDialog::getOpenFileUrl(0,"Select one file",dir);
    fileName = url.fileName();

    qDebug()<<"DIR - "<<dir;
    qDebug()<<"URL - "<<url.toLocalFile();

    return url.toString();
}

QString FileHelper::getOpenFileName() const
{
    return fileName;
}
