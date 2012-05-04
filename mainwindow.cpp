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
    int reponse = QMessageBox::information(this, "Fenetre d'aide", "<p> Bonjour à tous et bienvenue dans notre générateur de ville en 3D. Ce programme a pour but de générer une ville simpliste en 3D dans le zone à gauche de votre écran.<p> <p> Cliquez simplement sur ''démarrer'' pour lancer le programme. <p>  <p> Souhaitez-vous plus de détails ?", QMessageBox::Yes | QMessageBox::No);

    if (reponse == QMessageBox::Yes)
    {
        int reponse2 = QMessageBox::information(this, "Détails", "<p> Les différents paramètres que vous pouvez entrez sont sur la droite de votre écran. Ceux-ci obéissent parfois à certaines règles dépendantes de la génération de la ville et se modifient automatiquement lors de l'introduction de combinaisons de paramètres impossibles pour que la ville soit générable.<p> <p> Pour faire bouger la ville, il suffit de cliquer avec votre souris sur l'écran et de la bouger en maintenant le bouton enfoncer, ou bien d'utiliser les flèches de votre clavier. <p> La case jardin permet de remplacer les batiments sans connexion avec un axe routier par des jardins. ", QMessageBox::Ok);
        if (reponse2 == QMessageBox::Ok)
            QMessageBox::information(this, "Crédit", " <p> Merci d'utiliser notre générateur de ville en 3D !<p> Réalisé par Hubain Charles et Kettlewell William-James");
    }
}

void MainWindow::minBlockSizeChanged(int x)
{
    ui->maxBlockSize->setMinimum(2*x+1);
}

