#include"headers/helpers/fileHelper.h"
#include<QUrl>
#include<QFileDialog>
#include<QDebug>
#include<QStandardPaths>
#if defined (Q_OS_ANDROID)
#include<QtAndroid>
#endif

FileHelper::FileHelper(QObject *pwgt)
    :QObject{pwgt}
{}

FileHelper::~FileHelper()
{}

QUrl FileHelper::getUrl()
{
    auto dir = QStandardPaths::writableLocation(QStandardPaths::MusicLocation);

#if defined (Q_OS_ANDROID)
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
                "org/qtproject/qt5/android/QtNative",
                "activity",
                "()Landroid/app/Activity;");

    QAndroidJniObject ACTION_GET_CONTENT = QAndroidJniObject::getStaticObjectField(
                "android/content/Intent",
                "ACTION_GET_CONTENT",
                "Ljava/lang/String;");

    QAndroidJniObject EXTERNAL_CONTENT_URI = QAndroidJniObject::getStaticObjectField(
                "android/provider/MediaStore$Audio$Media",
                "EXTERNAL_CONTENT_URI",
                "Landroid/net/Uri;");

    QAndroidJniObject intent = QAndroidJniObject(
                "android/content/Intent",
                "(Ljava/lang/String;Landroid/net/Uri;)V",
                ACTION_GET_CONTENT.object<jstring>(),
                EXTERNAL_CONTENT_URI.object<jobject>());

    if (ACTION_GET_CONTENT.isValid() && intent.isValid())
    {
        intent.callObjectMethod(
                    "setType",
                    "(Ljava/lang/String;)Landroid/content/Intent;",
                    QAndroidJniObject::fromString("audio/*").object<jstring>());

        QtAndroid::startActivity(intent.object<jobject>(), 101,this);

        _fileName = _androidUrl.fileName();
        return  _androidUrl;
    }
#else
    QUrl url = QFileDialog::getOpenFileUrl(0,"Select one file",dir);
    _fileName = url.fileName();
    return url;
#endif
}

QString FileHelper::getOpenFileName() const
{
    return _fileName;
}

#if defined (Q_OS_ANDROID)
void FileHelper::handleActivityResult(int requestCode, int resultCode, const QAndroidJniObject &data)
{
    jint RESULT_OK = QAndroidJniObject::getStaticField<jint>("android/app/Activity","RESULT_OK");

    if (requestCode == 101 && resultCode == RESULT_OK)
    {
        QAndroidJniObject uri = data.callObjectMethod("getData", "()Landroid/net/Uri;");
        auto path = QtAndroid::androidActivity().callObjectMethod(
                    "getPath",
                    "(Landroid/net/Uri;)Ljava/lang/String;",
                    uri.object<jobject>());

        _androidUrl = path.toString();
        emit this->pathChanged(path.toString());
    }
}
#endif
