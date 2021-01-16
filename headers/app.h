#pragma once
#include<QApplication>
#include<QObject>
#include"core.h"


class App : public QApplication
{
    Q_OBJECT
private:
    bool running;
public:
    App(int &argc, char **argv);
    Core core;
    int exec();
    bool isRunning();
public slots:
    void onApplicationStateChange(const Qt::ApplicationState state);
};

