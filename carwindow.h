#ifndef CARWINDOW_H
#define CARWINDOW_H

#include <QMainWindow>
#include "car.h"
#include "carmanager.h"
#include "renter.h"
#include <QDebug>
#include <QString>
#include <QComboBox>


QT_BEGIN_NAMESPACE
namespace Ui {
class carWindow;
}
QT_END_NAMESPACE

class carWindow : public QMainWindow
{
    Q_OBJECT

public:
    carWindow(QWidget *parent = nullptr);
    ~carWindow();

    void addCarButtonClicked();
    void searchButtonClicked();
    void carTableWidgetClicked(int row, int col);
    void setUpComboBox();

    void displayMainWindow();

    CarManager getCarManager();


private:
    Ui::carWindow *ui;
    CarManager carManager;
};
#endif // CARWINDOW_H
