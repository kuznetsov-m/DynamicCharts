#include "TestForm.h"
#include "ui_TestForm.h"

TestForm::TestForm(QWidget *parent, Model *model) :
    QWidget(parent),
    ui(new Ui::TestForm),
    m_model(model)
{
    ui->setupUi(this);

    connect(&m_uiTimer, &QTimer::timeout,
            this, &TestForm::uiTimerTickSlot);
    m_uiTimer.start(50);
}

TestForm::~TestForm()
{
    m_uiTimer.stop();

    delete ui;
}

void TestForm::updateView()
{
    QString str;

    for (auto item : m_model->Coordinates())
        str += QString::number(item.x()) + " ";

    ui->lineEdit->setText(str);
}

void TestForm::uiTimerTickSlot()
{
    updateView();
}

void TestForm::on_pushButton_clicked()
{
    QPoint point;
    point.setX(1);
    point.setY(2);
    //m_model->m_coordinates.append(point);
}
