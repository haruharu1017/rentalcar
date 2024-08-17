#ifndef DETAILWINDOW_H
#define DETAILWINDOW_H

#include <QMainWindow>
#include "mainwindow.h"
#include "carmanager.h"
#include "carwindow.h"
#include "car.h"
#include <QDebug>
#include <QString>


namespace Ui {
class detailWindow;
}

class detailWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit detailWindow(QWidget *parent = nullptr);

    void backButtonClicked();
    void setCarDetails(QString plate, QString model, QString status, QString start, QString end, QString name, QString pho);
    void setCarDetails(Car* car);

    void editButtonClicked();
    void deleteButtonClicked();
    void okDeletion();
    void cancelDeletion();

    Car* transferCarData();

    QString capitalizeWords(const QString& s);

    ~detailWindow();

private:
    Ui::detailWindow *ui;
    Car * currentCar;
};

#endif // DETAILWINDOW_H
