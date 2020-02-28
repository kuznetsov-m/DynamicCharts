#pragma once

#include <QWidget>
#include <QTimer>
#include <QPointer>

#include "../Model/Model.h"

namespace Ui
{
    class TestForm;
}

class TestForm : public QWidget
{
    Q_OBJECT

public:
    explicit TestForm(QWidget *parent, Model *model);
    ~TestForm();

private:
    void updateView();

    Ui::TestForm *ui;

    Model *m_model;

    QTimer m_uiTimer;

private slots:
    void uiTimerTickSlot();
    void on_pushButton_clicked();
};
