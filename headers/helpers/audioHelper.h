#pragma once
#include<QObject>
#include<QMediaPlayer>
#include<QTimer>

class AudioHelper : public QObject
{
    Q_OBJECT
private:
    QMediaPlayer *_mediaPlayer;
    QTimer *_mainTimer;
    QTimer *_vibroTimer;
    QString _path;
    int _playTime;
    int _pauseTime;
    int _countOfSignals = 3;
    bool _isPlaying;
    AudioHelper(QObject*pwgt = nullptr);
public:
    AudioHelper() = delete;
    AudioHelper(const AudioHelper&) = delete;
    void operator=(const AudioHelper&) = delete;
    static AudioHelper *getInstance(QObject*pwgt = nullptr);
    ~AudioHelper();
    bool isPlaying() const;
    void setDuration(const int duration);
    void setPauseTime(const int pauseTime);
    void setPlayTime(const int playTime);
    void setPauseCount(const int pauseCount);
    bool canResume;
public slots:
    bool start();
    bool stop();
    bool Resume();
    bool Pause();
    void setPath(const QString&path);
signals:
    void close();
    void startAudio();
    void pauseAudio();
    void stopAudio();
};
