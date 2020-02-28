#include "RandomWorker.h"

#include "Model/Model.h"

#include <QThread>
#include <QDebug>
#include <time.h>

RandomWorker::RandomWorker(QObject *parent, Model *model) :
    QObject(parent),
    m_model(model)
{
    qDebug() << "ThreadId: " << QThread::currentThreadId() << " (RandomWorker)";

    qsrand(time(NULL));
}

RandomWorker::~RandomWorker()
{
    m_timer->stop();
}

void RandomWorker::start()
{
    m_timer = new QTimer();
    connect(m_timer, &QTimer::timeout, this, &RandomWorker::doWork);

    m_timer->start(TIMER_INTERVAL);
}

void RandomWorker::stop()
{
    m_timer->stop();
}

void RandomWorker::doWork()
{
    qDebug() << "ThreadId: " << QThread::currentThreadId() << " (RandomWorker::doWork())";

    QPoint point;
    point.setX(randValue(MIN, MAX));
    point.setY(randValue(MIN, MAX));

    m_model->appendCoordinate(point);
}

int RandomWorker::randValue(int min, int max)
{
    return qrand() % ((max + 1) - min) + min;
}
