#include <QMainWindow>

#include "Controller.h"
#include "Model/Model.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Model *m_model;

private:
    Ui::MainWindow *ui;

    Controller *m_controller;
};
