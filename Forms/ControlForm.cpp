#include "ControlForm.h"
#include "ui_ControlForm.h"

ControlForm::ControlForm(QWidget *parent, Model *model) :
    QWidget(parent),
    ui(new Ui::ControlForm),
    m_model(model)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_chartForm = new ChartForm(this, m_model);
    connect(m_chartForm, &ChartForm::pointSelectedSignal,
            this, &ControlForm::pointSelectedSlot);
    connect(this, &ControlForm::selectedItemSignal,
            m_chartForm, &ChartForm::selectedItemSlot);
    ui->wChart->layout()->addWidget(m_chartForm);

    initializateView();

    connect(&m_uiTimer, &QTimer::timeout,
            this, &ControlForm::uiTimerTickSlot);
    m_uiTimer.start(50);
}

ControlForm::~ControlForm()
{
    m_uiTimer.stop();

    delete ui;
}

void ControlForm::initializateView()
{
    auto tw = ui->tableWidget;
    tw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tw->setSelectionBehavior(QAbstractItemView::SelectRows);
    tw->setSelectionMode(QAbstractItemView::SingleSelection);
    tw->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tw->setColumnCount(2);
    tw->setHorizontalHeaderLabels(QStringList() << "X" << "Y");
    tw->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tw->verticalHeader()->setDefaultSectionSize(20);
    //tw->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    tw->horizontalHeader()->setDefaultSectionSize(50);
}

void ControlForm::updateView()
{
    m_chartForm->updateView();

    ui->tableWidget->setRowCount(m_model->Coordinates().size());

    for(int i = 0; i < m_model->Coordinates().size(); ++i)
    {
        QTableWidgetItem *itemX = new QTableWidgetItem(QString::number(
                                                           m_model->Coordinates()[i].x()));
        ui->tableWidget->setItem(i, 0, itemX);

        QTableWidgetItem *itemY = new QTableWidgetItem(QString::number(
                                                           m_model->Coordinates()[i].y()));
        ui->tableWidget->setItem(i, 1, itemY);
    }

}

void ControlForm::uiTimerTickSlot()
{
    updateView();
}

void ControlForm::pointSelectedSlot(const QPointF &point)
{
    for(int i = 0; i < m_model->Coordinates().size(); ++i)
    {
        if (m_model->Coordinates()[i] == point)
        {
            ui->tableWidget->selectRow(i);
            ui->sbX->setValue(point.x());
            ui->sbY->setValue(point.y());
        }
    }
}

void ControlForm::on_pbAdd_clicked()
{
    QPoint point;
    point.setX(ui->sbX->value());
    point.setY(ui->sbY->value());

    if (ui->chbAutoIncrement->isChecked())
    {
        ui->sbX->setValue(ui->sbX->value() + 1);
        ui->sbY->setValue(ui->sbY->value() + 1);
    }

    m_model->appendCoordinate(point);
}

void ControlForm::on_pbEdit_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();

    if (selected.size() > 0)
    {
        int row = selected.at(0).row();

        QPoint point(ui->sbX->value(), ui->sbY->value());
        m_model->updateCoordinate(row, point);
    }
}

void ControlForm::on_pbDelete_clicked()
{
    QItemSelectionModel *selectionModel = ui->tableWidget->selectionModel();
    QModelIndexList selected = selectionModel->selectedRows();

    if (selected.size() > 0)
    {
        int row = selected.at(0).row();

        m_model->removeCoordinateAt(row);
    }
}

void ControlForm::on_tableWidget_clicked(const QModelIndex &index)
{
    auto row = index.row();

    if (row <= m_model->Coordinates().size())
    {
        emit selectedItemSignal(row);

        ui->sbX->setValue(m_model->Coordinates()[row].x());
        ui->sbY->setValue(m_model->Coordinates()[row].y());
    }
}

void ControlForm::on_pbStartRandom_clicked()
{
    emit startRandomSignal();
}

void ControlForm::on_pbPauseRandom_clicked()
{
    emit pauseRandomSignal();
}

void ControlForm::on_StopRandom_clicked()
{
    emit stopRandomSignal();
}
