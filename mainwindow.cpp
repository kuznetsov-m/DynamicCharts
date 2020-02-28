#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_controller = new Controller(nullptr);

    m_controller->showForm(ui->wContent);
}

MainWindow::~MainWindow()
{
    delete m_controller;

    delete ui;
}
