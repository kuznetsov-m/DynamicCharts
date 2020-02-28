#pragma once

#include <QObject>
#include <QPointer>
#include <QList>

class ControlForm;

class Model : public QObject
{
    Q_OBJECT

public:
    explicit Model(QObject *parent = 0);
    ~Model();

    void showForm(QWidget *parent);

    const QList<QPoint> &Coordinates() const;

    void appendCoordinate(const QPoint &point);

    void updateCoordinate(int index, const QPoint &point);

    void removeCoordinateAt(int index);

    void clearCoordinates();

private:

    QPointer<ControlForm> m_form;

    QList<QPoint> m_coordinates;
};
