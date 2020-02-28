#include "ChartForm.h"
#include "ui_ChartForm.h"

#include <QDebug>

ChartForm::ChartForm(QWidget *parent, Model *model) :
    QWidget(parent),
    ui(new Ui::ChartForm),
    m_model(model)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);

    m_points = new QScatterSeries();

    connect(m_points, &QScatterSeries::pressed,
            this, &ChartForm::pointSelectedSlot);

    m_line = new QLineSeries();

    m_chart = new QChart();
    m_chart->addSeries(m_line);
    m_chart->addSeries(m_points);
    m_chart->createDefaultAxes();

    m_chartView = new QChartView(m_chart);

    ui->wChart->layout()->addWidget(m_chartView);

    connect(ui->hs, &QSlider::valueChanged,
            this, &ChartForm::hValueChangedSlot);
    connect(ui->vs, &QSlider::valueChanged,
            this, &ChartForm::vValueChangedSlot);

    initializateView();
}

ChartForm::~ChartForm()
{
    delete m_points;
    delete m_chart;
    delete m_chartView;

    delete ui;
}

void ChartForm::initializateView()
{
    QPen pen(QRgb(0x000000));
    pen.setWidth(2);
    m_points->setPen(pen);

    m_chart->legend()->hide();

    // Настройка заголовка для Chart
//    QFont font;
//    font.setPixelSize(18);
//    m_chart->setTitleFont(font);
//    m_chart->setTitleBrush(QBrush(Qt::black));
//    m_chart->setTitle("test title");

    //
//    QCategoryAxis *axisX = new QCategoryAxis();
//    axisX->append("0", 0);
//    axisX->append("1", 1);
//    axisX->append("2", 2);
//    axisX->append("3", 3);
//    axisX->append("4", 4);
//    m_chart->setAxisX(axisX, m_series);

    //m_chart->setAnimationOptions(QChart::AllAnimations);

    m_chartView->setRenderHint(QPainter::Antialiasing);

    ui->rbAuto->setChecked(true);
}

void ChartForm::updateView()
{
    //Управление координатной плоскостью
    int maxX = 1;
    int maxY = 1;

    if (ui->rbAuto->isChecked())
    {
        for(auto item : m_model->Coordinates())
        {
            if (item.x() > maxX)
                maxX = item.x();

            if (item.y() > maxY)
                maxY = item.y();
        }
    }
    else
    {
        maxX = ui->sbMaxX->value();
        maxY = ui->sbMaxY->value();
    }

    m_chart->axisX()->setMax(maxX);
    m_chart->axisY()->setMax(maxY);

    ui->hs->setMaximum(maxX);
    ui->hs->setValue(m_selected.x());
    ui->vs->setMaximum(maxY);
    ui->vs->setValue(m_selected.y());

    //Управление отображением графика
    m_points->clear();
    m_line->clear();

    for(auto item : m_model->Coordinates())
    {
        m_points->append(item.x(), item.y());
        m_line->append(item.x(), item.y());
    }
}

void ChartForm::selectedItemSlot(int num)
{
    m_selected = m_points->at(num);
}

void ChartForm::pointSelectedSlot(const QPointF &point)
{
    m_selected = point;

    emit pointSelectedSignal(point);

    ui->hs->setValue(point.x());
    ui->vs->setValue(point.y());
}

void ChartForm::hValueChangedSlot(int value)
{
    for(int i = 0; i < m_model->Coordinates().size(); ++i)
    {
        if (m_model->Coordinates()[i] == m_selected)
        {
            auto point = m_model->Coordinates()[i];
            point.setX(value);
            m_model->updateCoordinate(i, point);

            m_selected.setX(value);
        }
    }
}

void ChartForm::vValueChangedSlot(int value)
{
    for(int i = 0; i < m_model->Coordinates().size(); ++i)
    {
        if (m_model->Coordinates()[i] == m_selected)
        {
            auto point = m_model->Coordinates()[i];
            point.setY(value);
            m_model->updateCoordinate(i, point);

            m_selected.setY(value);
        }
    }
}
