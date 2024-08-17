#include "carwindow.h"
#include "ui_carwindow.h"
#include <QDateTimeEdit>
#include "mainwindow.h"
#include "detailwindow.h"
#include <iostream>
#include <QDir>
using namespace std;


carWindow::carWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::carWindow)
{
    ui->setupUi(this);

    ui->noCarFoundLabel->hide();
    setUpComboBox();
    displayMainWindow();
    qDebug() << "Current working directory:" << QDir::currentPath();


    connect(ui->addCarButton, &QPushButton::clicked, this, &carWindow::addCarButtonClicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &carWindow::searchButtonClicked);
    connect(ui->carTableWidget, &QTableWidget::cellClicked, this, &carWindow::carTableWidgetClicked);
}

carWindow::~carWindow()
{
    delete ui;
}


void carWindow::displayMainWindow() {
    ui->noCarFoundLabel->hide();

    carManager.readCarFile("cars.txt");
    // 设置表格行数和列数
    int totalCars = carManager.getCarList().size(); // 假设 getCars() 返回所有车辆的列表
    ui->carTableWidget->setRowCount(totalCars);
    ui->carTableWidget->setColumnCount(3);

    // 设置表头
    QStringList headers;
    headers << "Model" <<"Plate Number"<< "Status";
    ui->carTableWidget->setHorizontalHeaderLabels(headers);

    // 设置行不可编辑和调整行高
    ui->carTableWidget->verticalHeader()->setDefaultSectionSize(50); // 示例行高设置
    ui->carTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // 设置表格内容
    int row = 0;
    for (const Car &car : carManager.getCarList()) {
        QTableWidgetItem *modelItem = new QTableWidgetItem(car.getModel());
        QTableWidgetItem *plateItem = new QTableWidgetItem(car.getLicensePlate());
        QString status = car.isAvailable() ? "🟢 Available" : "🔴 Rented"; // 根据可用性设置状态
        QTableWidgetItem *statusItem = new QTableWidgetItem(status);

        ui->carTableWidget->setItem(row, 0, modelItem);
        ui->carTableWidget->setItem(row, 1, plateItem);
        ui->carTableWidget->setItem(row, 2, statusItem);
        row++;
    }

    // 调整列宽以适应内容
    ui->carTableWidget->resizeColumnsToContents();
}


void carWindow::addCarButtonClicked(){
    carManager.printAllCars();


    MainWindow *mainWindow = new MainWindow();  // 创建MainWindow的实例
    mainWindow->show();  // 显示MainWindow
    this->close();  // 关闭当前窗口
}

void carWindow::setUpComboBox(){
    ui->searchCombo->addItem("By Plate");
    ui->searchCombo->addItem("By Renter's Name");
    // ui->searchCombo->addItem("By Model");
}

void carWindow::searchButtonClicked(){
    detailWindow* d = new detailWindow();

    if(ui->searchCombo->currentIndex()==0){
        QString plate = ui->searchBar->text().toUpper();
        Car * car = carManager.getCar(plate);
        if(!car){
            ui->noCarFoundLabel->show();
            return;
        }
        d->setCarDetails(car);
    }else if(ui->searchCombo->currentIndex()==1){
        QString name = carManager.capitalizeWords(ui->searchBar->text());
        Car * car = carManager.getCarByRentersName(name);
        if(!car){
            ui->noCarFoundLabel->show();
            return;
        }
        d->setCarDetails(car);

    }
    d->show();
    this->close();
}

void carWindow::carTableWidgetClicked(int row, int col){
    if (col == 0) {  // 确保是第一列

        QString plate = ui->carTableWidget->item(row, 1)->text();   // Plate Number
        Car* car = carManager.getCar(plate);
        detailWindow *detailWin = new detailWindow();

        if (!car) {
            return;  // 如果车辆未找到，直接返回，不打开详情窗口
        }
        detailWin->setCarDetails(car);
        detailWin->setAttribute(Qt::WA_DeleteOnClose);  // 确保窗口关闭时释放资源



        this->close();
        detailWin->show();
    }
}

CarManager carWindow::getCarManager(){
    return carManager;
}
