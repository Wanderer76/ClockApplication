#include"headers/helpers/audioHelper.h"
#include"headers/helpers/vibrationHelper.h"

static int countOfPause = 0;

AudioHelper::AudioHelper(QObject *pwgt)
    :QObject(pwgt)
{
    _mediaPlayer = new QMediaPlayer(this);
    _mainTimer = new QTimer(this);
    _isPlaying = false;
    _path = "";
    canResume = true;
    _mediaPlayer->setAudioRole(QAudio::Role::AlarmRole);
#if defined (Q_OS_ANDROID)
    _vibroTimer = new QTimer(this);
    _vibroTimer->setInterval(2000);
    connect(_vibroTimer,&QTimer::timeout,this,[](){
        VibrationHelper::vibrate(600);
    });
#endif

    connect(this,&AudioHelper::close,this,[&](){
        if(stop())
        {
            qDebug()<<"Stopped!!";
        }
    });

    connect(_mainTimer,&QTimer::timeout,this,[&]() {

        if(_isPlaying)
        {
            qDebug()<<"Pause";
            _mainTimer->setInterval(_pauseTime);
            countOfPause++;
            if(countOfPause == _countOfSignals)
                stop();
            Pause();
        }
        else
        {
            qDebug()<<"Resume";
            _mainTimer->setInterval(_playTime);
            Resume();
        }
    });
}

AudioHelper *AudioHelper::getInstance(QObject *pwgt)
{
    static AudioHelper *instance = nullptr;
    if(instance == nullptr)
        instance = new AudioHelper(pwgt);
    return instance;
}

AudioHelper::~AudioHelper()
{}

bool AudioHelper::start()
{
    _isPlaying = true;
    _mediaPlayer->play();
    _vibroTimer->start();
    _mainTimer->start(_playTime);
    return true;
}

bool AudioHelper::stop()
{
    _mediaPlayer->stop();
    _vibroTimer->stop();
    _isPlaying = false;
    canResume = false;
    _mainTimer->stop();
    countOfPause = 0;
    return true;
}

bool AudioHelper::isPlaying() const
{
    return _isPlaying;
}

void AudioHelper::setPath(const QString &path)
{
    _mediaPlayer->setMedia(QUrl(path));
}

void AudioHelper::setDuration(const int duration)
{
    emit _mediaPlayer->durationChanged(duration);
}

void AudioHelper::setPauseTime(const int pauseTime)
{
    _pauseTime = pauseTime;
}

void AudioHelper::setPlayTime(const int playTime)
{
    _playTime = playTime;
}

void AudioHelper::setPauseCount(const int pauseCount)
{
    _countOfSignals = pauseCount;
}

bool AudioHelper::Resume()
{
    canResume = true;
    _isPlaying = true;
    _mediaPlayer->play();
    _vibroTimer->start();
    return true;
}

bool AudioHelper::Pause()
{
    canResume = false;
    _isPlaying = false;
    _mediaPlayer->stop();
    _vibroTimer->stop();
    return true;
}
