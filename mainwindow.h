#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <city.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void start();
    void minBlockSizeChanged(int x);

private:
    Ui::MainWindow *ui;
    City* myCity;
};

#endif // MAINWINDOW_H
