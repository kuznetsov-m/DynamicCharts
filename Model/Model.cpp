#include "Model.h"

#include <QThread>

#include "../Forms/ControlForm.h"

Model::Model(QObject *parent)
    : QObject(parent)
{
    qDebug() << "ThreadId: " << QThread::currentThreadId() << " (Model)";
}

Model::~Model()
{
    if(m_form == nullptr)
        delete m_form;
}

void Model::showForm(QWidget *parent)
{
    if(m_form == nullptr)
        m_form = new ControlForm(parent, this);
}

const QList<QPoint> &Model::Coordinates() const
{
    return m_coordinates;
}

void Model::appendCoordinate(const QPoint &point)
{
    m_coordinates.append(point);
}

void Model::updateCoordinate(int index, const QPoint &point)
{
    if (0 <= index && index <= m_coordinates.size())
    {
        m_coordinates[index] = point;
    }
}

void Model::removeCoordinateAt(int index)
{
    if (0 <= index && index <= m_coordinates.size())
    {
        m_coordinates.removeAt(index);
    }
}

void Model::clearCoordinates()
{
    m_coordinates.clear();
}
