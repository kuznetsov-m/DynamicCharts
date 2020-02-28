/// Source: https://www.youtube.com/watch?v=MHn3ZTWcyXk

#include "mainwindow.h"
#include <QApplication>

#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QBrush>
#include <QtCharts/QChartView>

#include <QtCharts/QScatterSeries>

#include <QDebug>
#include <time.h>

QT_CHARTS_USE_NAMESPACE

using namespace QtCharts;

double rand(double fMin, double fMax)
{
    double rd;
    auto r = rand();
    qDebug() << r;
    rd = (double)r / RAND_MAX;
    qDebug() << rd;
    rd = fMin + rd * (fMax - fMin);
    qDebug() << rd;
    return rd;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QLineSeries *series = new QLineSeries();
    series->append(0, 16);
    series->append(1, 25);
    series->append(2, 35);
    series->append(3, 47);
    series->append(4, 55);
    series->setPointLabelsVisible(true);

    srand(time(nullptr));

    QScatterSeries *series2 = new QScatterSeries();
    series2->append(1, 19);
    for(int i = 0; i < 10; ++i)
        series2->append(rand(0.5, 4), rand(0.5, 55));

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->createDefaultAxes();

    QFont font;
    font.setPixelSize(18);
    chart->setTitleFont(font);
    chart->setTitleBrush(QBrush(Qt::black));
    chart->setTitle("test title");

    QPen pen(QRgb(0x000000));
    pen.setWidth(5);
    series->setPen(pen);

    chart->setAnimationOptions(QChart::AllAnimations);

    QCategoryAxis *axisX = new QCategoryAxis();
    axisX->append("1986", 0);
    axisX->append("1992", 1);
    axisX->append("1995", 2);
    axisX->append("1996", 3);
    axisX->append("1999", 4);
    chart->setAxisX(axisX, series);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    MainWindow w;
    //w.setCentralWidget(chartView);
    //w.resize(500,500);
    w.show();

    return a.exec();
}
