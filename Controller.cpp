#include "Controller.h"

#include <QApplication>
#include <QLayout>
#include <QWidget>

Controller::Controller(QObject *parent) :
    QObject(parent)
{
    qDebug() << "ThreadId: " << QThread::currentThreadId() << " (Controller)";

    m_model = new Model(nullptr);

    m_workerThread = new QThread();

    m_worker = new RandomWorker(nullptr, m_model);
    m_worker->moveToThread(m_workerThread);
    connect(m_workerThread, &QThread::started,
            m_worker, &RandomWorker::start);
    connect(m_workerThread, &QThread::finished,
            m_worker, &RandomWorker::stop);
}

Controller::~Controller()
{
    if (m_workerThread->isRunning())
        m_workerThread->quit();
    m_workerThread->deleteLater();

    delete m_worker;

    if (m_form != nullptr)
        delete m_form;

    delete m_model;
}

void Controller::showForm(QWidget *w)
{
    if (m_form == nullptr)
    {
        m_form = new ControlForm(nullptr, m_model);

        connect(m_form.data(), &ControlForm::startRandomSignal,
                this, &Controller::startRandomWorkerSlot);
        connect(m_form.data(), &ControlForm::pauseRandomSignal,
                this, &Controller::pauseRandomWorkerSlot);
        connect(m_form.data(), &ControlForm::stopRandomSignal,
                this, &Controller::stopRandomWorkerSlot);
    }

    w->layout()->addWidget(m_form);
}

void Controller::startRandomWorkerSlot()
{
    m_workerThread->start();
}

void Controller::pauseRandomWorkerSlot()
{
    m_workerThread->quit();
}

void Controller::stopRandomWorkerSlot()
{
    m_workerThread->quit();

    m_model->clearCoordinates();
}
