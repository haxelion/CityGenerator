#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*Connections des événements

    connect(ui->, SIGNAL(valueChanged(int)), ui->glWidget, SLOT(setXRotation(int)));

    setWindowTitle(tr("Generateur de ville"));*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
