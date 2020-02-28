#include <QObject>
#include <QThread>

#include "Model/Model.h"
#include "RandomWorker.h"
#include "Forms/ControlForm.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    explicit Controller(QObject *parent);
    ~Controller();

    void showForm(QWidget *w);

private:
    Model *m_model;

    QPointer<ControlForm> m_form;

    QThread *m_workerThread;

    RandomWorker *m_worker;

private slots:
    void startRandomWorkerSlot();
    void pauseRandomWorkerSlot();
    void stopRandomWorkerSlot();
};
