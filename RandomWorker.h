#pragma once

#include <QObject>
#include <QTimer>

class Model;

class RandomWorker : public QObject
{
    Q_OBJECT

public:
    explicit RandomWorker(QObject *parent, Model *model);
    ~RandomWorker();

public slots:
    void start();
    void stop();

    void doWork();

private:
    int randValue(int min, int max);

    Model *m_model;

    const int TIMER_INTERVAL = 1000;
    const int MIN = 0;
    const int MAX = 99;

    QTimer *m_timer;
};
