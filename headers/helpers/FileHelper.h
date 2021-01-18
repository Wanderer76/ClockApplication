#pragma once
#include<QObject>
#include<QUrl>


class FileHelper : public QObject
{
    Q_OBJECT
private:
    QString fileName;
public:
    FileHelper(QObject*pwgt = nullptr);
    ~FileHelper();
    Q_INVOKABLE QUrl getUrl();
    Q_INVOKABLE QString getOpenFileName() const;
};
