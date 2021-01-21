#pragma once
#include<QObject>
#include<QUrl>

#if defined(Q_OS_ANDROID)
#include<QtAndroidExtras>
#endif

class FileHelper : public QObject
        #if defined (Q_OS_ANDROID)
        ,public QAndroidActivityResultReceiver
        #endif
{
    Q_OBJECT
private:
    QString _fileName;
    QUrl _androidUrl;
public:
    explicit FileHelper(QObject*pwgt = nullptr);
    ~FileHelper();
    Q_INVOKABLE QUrl getUrl();
    Q_INVOKABLE QString getOpenFileName() const;

    // QAndroidActivityResultReceiver interface
#if defined (Q_OS_ANDROID)
    virtual void handleActivityResult(int receiverRequestCode, int resultCode, const QAndroidJniObject &data) override;
#endif
signals:
    void pathChanged(QString);
};
