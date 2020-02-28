#pragma once

#include <QWidget>
#include <QTimer>
#include <QPointer>

#include "../Model/Model.h"
#include "ChartForm.h"

#include <QDebug>

namespace Ui
{
    class ControlForm;
}

class ControlForm : public QWidget
{
    Q_OBJECT

public:
    explicit ControlForm(QWidget *parent, Model *model);
    ~ControlForm();

signals:
    void selectedItemSignal(int num);

    void startRandomSignal();
    void pauseRandomSignal();
    void stopRandomSignal();

private:
    void initializateView();

    void updateView();

    Ui::ControlForm *ui;

    Model *m_model;

    QPointer<ChartForm> m_chartForm;

    QTimer m_uiTimer;

private slots:
    void uiTimerTickSlot();

    void pointSelectedSlot(const QPointF &point);

    void on_pbAdd_clicked();
    void on_pbEdit_clicked();
    void on_pbDelete_clicked();
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pbStartRandom_clicked();
    void on_pbPauseRandom_clicked();
    void on_StopRandom_clicked();
};
