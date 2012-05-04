#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myCity = NULL;
    connect(ui->minBlockSize, SIGNAL(valueChanged(int)), this, SLOT(minBlockSizeChanged(int)));
    connect(ui->Start, SIGNAL(clicked()),this, SLOT(start()));
    connect(ui->Help, SIGNAL(clicked()), this, SLOT(help()));

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

void MainWindow::help()
{
    int reponse = QMessageBox::information(this, "Fenetre d'aide", "<p> Bonjour � tous et bienvenue dans notre g�n�rateur de ville en 3D. Ce programme a pour but de g�n�rer une ville simpliste en 3D dans le zone � gauche de votre �cran.<p> <p> Cliquez simplement sur ''d�marrer'' pour lancer le programme. <p>  <p> Souhaitez-vous plus de d�tails ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        int reponse2 = QMessageBox::information(this, "D�tails", "<p> Les diff�rents param�tres que vous pouvez entrez sont sur la droite de votre �cran. Ceux-ci ob�issent parfois � certaines r�gles d�pendantes de la g�n�ration de la ville et se modifient automatiquement lors de l'introduction de combinaisons de param�tres impossibles pour que la ville soit g�n�rable.<p> <p> Pour faire bouger la ville, il suffit de cliquer avec votre souris sur l'�cran et de la bouger en maintenant le bouton enfoncer, ou bien d'utiliser les fl�ches de votre clavier. <p> La case jardin permet de remplacer les batiments sans connexion avec un axe routier par des jardins. ", QMessageBox::Ok);
        if (reponse2 == QMessageBox::Ok)
            QMessageBox::information(this, "Cr�dit", " <p> Merci d'utiliser notre g�n�rateur de ville en 3D !<p> R�alis� par Hubain Charles et Kettlewell William-James");
    }
}

void MainWindow::minBlockSizeChanged(int x)
{
    ui->maxBlockSize->setMinimum(2*x+1);
}

