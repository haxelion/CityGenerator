#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myCity = NULL;
    connect(ui->minBlockSize, SIGNAL(valueChanged(int)), this, SLOT(minBlockSizeChanged(int)));
    connect(ui->Start, SIGNAL(clicked()),this, SLOT(start()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    if (myCity !=NULL)
    {
        ui->glWidget->setCity(0);
        delete myCity;
    }

    myCity = new City (ui->cityLength->value(),ui->cityWidth->value());
    myCity->setGarden(ui->garden->checkState());
    myCity->setMinBlockSize (ui->minBlockSize->value());
    myCity->setMaxBlockSize (ui->maxBlockSize->value());
    myCity->setHeightMean (ui->heightMean->value());
    myCity->setHeightVariance (ui->heightVariance->value());
    myCity->setMinBuildingHeight (ui->minBuildingHeight->value());
    myCity->setMaxBuildingHeight (ui->maxBuildingHeight->value());
    myCity->divideInBlocks(Zone(0,0,ui->cityLength->value(),ui->cityWidth->value()));
    ui->glWidget->setCity(myCity);
}

void MainWindow::minBlockSizeChanged(int x)
{
    ui->maxBlockSize->setMinimum(2*x+1);
}

