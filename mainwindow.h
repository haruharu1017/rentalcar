#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "carwindow.h"
#include "detailwindow.h"
#include "carmanager.h"
#include "car.h"
#include <QDebug>
#include <QString>


using namespace std;
#include <iostream>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    void cancelButtonClicked();
    void submitButtonClicked();
    void renterDisplay(bool checked);
    void hideItems();
    void editContentDisplay(Car* car);

    ~MainWindow();


private:
    Ui::MainWindow *ui;
    Car* currentEditCar;
};

#endif // MAINWINDOW_H
