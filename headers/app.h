#pragma once
#include<QApplication>
#include<QObject>
#include"core.h"


class App : public QApplication
{
    Q_OBJECT
private:
    bool _running;
public:
    explicit App(int &argc, char **argv);
    ~App();
    Core core;
    int exec();
    bool isRunning() const;
public slots:
    void onApplicationStateChange(const Qt::ApplicationState state);
};

