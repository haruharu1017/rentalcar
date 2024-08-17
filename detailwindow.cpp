#include "detailwindow.h"
#include "ui_detailwindow.h"
#include "carmanager.h"
#include <QString>
#include <QTextStream>

detailWindow::detailWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::detailWindow)
{
    ui->setupUi(this);

    ui->deleteConfirm->hide();

    connect(ui->backButton, &QPushButton::clicked, this, &detailWindow::backButtonClicked);
    connect(ui->editButton, &QPushButton::clicked, this, &detailWindow::editButtonClicked);
    connect(ui->deleteButton, &QPushButton::clicked, this, &detailWindow::deleteButtonClicked);
    connect(ui->delConfButton, &QDialogButtonBox::accepted, this, &detailWindow::okDeletion);
    connect(ui->delConfButton, &QDialogButtonBox::rejected, this, &detailWindow::cancelDeletion);
}

detailWindow::~detailWindow()
{
    delete ui;
}

void detailWindow::backButtonClicked(){
    carWindow *carWin = new carWindow();
    carWin->show();
    this->hide();
}

void detailWindow::setCarDetails(Car* car){
    if (!car) {
        return;  // 如果 car 是 nullptr，则直接返回
    }

    currentCar = car;
    ui->plateNumberLabel->setText(currentCar->getLicensePlate());
    ui->modelLabel->setText(currentCar->getModel());
    if(currentCar->isAvailable()) ui->avaLabel->setText("🟢 Available");
    else ui->avaLabel->setText("🔴 Rented");

    QString start = currentCar->getRenter().getStartTime().toString("yyyy/MM/dd");
    QString end = currentCar->getRenter().getEndTime().toString("yyyy/MM/dd");

    if(currentCar->isAvailable()){
        ui->renterLabel->setText("");
        ui->dateLabel->setText("");
    }else{
        QString tempName =  currentCar->getRenter().getName();
        ui->renterLabel->setText(capitalizeWords(tempName)+" ("+currentCar->getRenter().getPhoNum()+")");
        ui->dateLabel->setText(start+" ➡︎ "+end);
    }

}

void detailWindow::editButtonClicked(){
    QString currentPlate = ui->plateNumberLabel->text();

    CarManager::getInstance().readCarFile("cars.txt");
    Car* car=CarManager::getInstance().getCar(currentPlate);

    MainWindow * mainwindow = new MainWindow();
    mainwindow->editContentDisplay(car);
    mainwindow->show();
    this->close();
}

void detailWindow::deleteButtonClicked() {
    ui->deleteConfirm->show();
    ui->backButton->setEnabled(false);
    ui->editButton->setEnabled(false);
    ui->deleteButton->setEnabled(false);

}

QString detailWindow::capitalizeWords(const QString& s) {
    QStringList parts = s.split(' ', Qt::SkipEmptyParts);
    for (int i = 0; i < parts.size(); ++i) {
        QString part = parts[i];
        if (!part.isEmpty()) {
            parts[i][0] = parts[i][0].toUpper();  // 首字母大写
            if (part.length() > 1) {
                QString rest = part.mid(1).toLower();  // 余下的字母小写
                parts[i].replace(1, part.length() - 1, rest);
            }
        }
    }

    return parts.join(" ");
}

void detailWindow::okDeletion(){
    ui->deleteConfirm->hide();
    QString plate = ui->plateNumberLabel->text();
    qDebug() << "if we got the plate: " <<plate;

    CarManager::getInstance().readCarFile("cars.txt");

    auto carList = CarManager::getInstance().getCarList();
    for (const Car &c : carList) {
        qDebug() << "Listed plate:" << c.getLicensePlate();
    }

    Car* car = CarManager::getInstance().getCar(plate);
    if (!car) {  // 先检查 car 是否有效
        qDebug() << "Invalid car";
        return;
    }

    qDebug() << "Car's plate: " << car->getLicensePlate();
    if (CarManager::getInstance().removeCar(*car) == 0) {
        CarManager::getInstance().writeCarFile("cars.txt");
        carWindow * carwin = new carWindow();
        carwin->displayMainWindow();
        carwin->show();
        this->close();
    } else {
        qDebug() << "Failed to remove car";
    }

    ui->backButton->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);
}

void detailWindow::cancelDeletion(){
    ui->deleteConfirm->hide();
    ui->backButton->setEnabled(true);
    ui->editButton->setEnabled(true);
    ui->deleteButton->setEnabled(true);

}

Car* detailWindow::transferCarData(){
    return currentCar;
}
