#include <QWidget>

#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QBrush>
#include <QtCharts/QChartView>

#include <QtCharts/QScatterSeries>

QT_CHARTS_USE_NAMESPACE

using namespace QtCharts;

#include "../Model/Model.h"

namespace Ui
{
    class ChartForm;
}

class ChartForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChartForm(QWidget *parent, Model *model);
    ~ChartForm();

    void initializateView();

    void updateView();

signals:
    void pointSelectedSignal(const QPointF &point);

public slots:
    void selectedItemSlot(int num);

private:
    Ui::ChartForm *ui;

    Model *m_model;

    QScatterSeries *m_points;

    QLineSeries *m_line;

    QChart *m_chart;

    QChartView *m_chartView;

    QPointF m_selected;

private slots:
    void pointSelectedSlot(const QPointF &point);

    void hValueChangedSlot(int value);
    void vValueChangedSlot(int value);
};
