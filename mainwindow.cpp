#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->minBlockSize, SIGNAL(valueChanged(int)), this, SLOT(minBlockSizeChanged(int)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{

}

void MainWindow::minBlockSizeChanged(int x)
{
    ui->maxBlockSize->setMinimum(2*x+1);
}

