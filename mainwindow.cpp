#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    currentEditCar = CarManager::getInstance().getCar(ui->plateInput->text());
    hideItems();

    connect(ui->cancelButton, &QPushButton::clicked, this, &MainWindow::cancelButtonClicked);
    connect(ui->submitButton, &QPushButton::clicked, this, &MainWindow::submitButtonClicked);
    connect(ui->statusButton, &QRadioButton::toggled, this, &MainWindow::renterDisplay);

}



void MainWindow::cancelButtonClicked(){
    carWindow* carwindow = new carWindow();

    ui->modelInput->clear();
    ui->phoInput->clear();
    ui->renterNameInput->clear();
    ui->startDateEdit->clear();
    ui->endDateEdit->clear();
    ui->plateInput->clear();
    ui->statusButton->setChecked(false);

    carwindow->show();
    this->close();
}

void MainWindow::submitButtonClicked(){
    CarManager::getInstance().readCarFile("cars.txt");

    CarManager::getInstance().printAllCars();

    auto carWin = new carWindow();

    if (ui->modelInput->text().isEmpty() || ui->plateInput->text().isEmpty()) {
        // QMessageBox::warning(this, "Input Error", "Model and plate number are required.");
        return;
    }

    QString model = ui->modelInput->text();
    QString plate = ui->plateInput->text();
    bool status = ui->statusButton->isChecked();
    QString name = ui->renterNameInput->text();
    QString pho = ui->phoInput->text();
    QDateTime start = ui->startDateEdit->dateTime();
    QDateTime end = ui->endDateEdit->dateTime();

    if (start > end) {
        // QMessageBox::warning(this, "Date Error", "End date must be later than start date.");
        return;
    }

    Renter renter(name, pho, start, end);
    if(status){
        if (ui->renterNameInput->text().isEmpty() || ui->phoInput->text().isEmpty()) {
            // QMessageBox::warning(this, "Input Error", "Model and plate number are required.");
            return;
        }
        Car car(plate, model, false, renter);
         CarManager::getInstance().updateOrAddCar(car);
    }else{
        Car car(plate, model, true, renter);
        CarManager::getInstance().updateOrAddCar(car);
    }


    carWin->setAttribute(Qt::WA_DeleteOnClose);  // 确保窗口关闭时自动释放资源


    CarManager::getInstance().writeCarFile("cars.txt");
    carWin->displayMainWindow();
    carWin->show();

    this->close();
}


void MainWindow::renterDisplay(bool checked) {
    // currentEditCar = CarManager::getInstance().getCar(ui->plateInput->text());

    ui->renterNameInput->setVisible(checked);
    ui->nameLabel->setVisible(checked);
    ui->startDateEdit->setVisible(checked);
    ui->startLabel->setVisible(checked);
    ui->endDateEdit->setVisible(checked);
    ui->endLabel->setVisible(checked);
    ui->phoInput->setVisible(checked);
    ui->phoLabel->setVisible(checked);

    if(checked==0){
        ui->renterNameInput->clear();
        ui->startDateEdit->setDateTime(QDateTime());  // 设置为无效状态
        ui->endDateEdit->setDateTime(QDateTime());
        ui->phoInput->clear();
        if (currentEditCar) {
            currentEditCar->setStatus(true);  // 只在car不为null时调用

        }
    }
}

void MainWindow::hideItems(){
    ui->renterNameInput->hide();
    ui->nameLabel->hide();
    ui->startDateEdit->hide();
    ui->startLabel->hide();
    ui->endDateEdit->hide();
    ui->endLabel->hide();
    ui->phoInput->hide();
    ui->phoLabel->hide();
}

void MainWindow::editContentDisplay(Car* displayedCar){
    if (!displayedCar) {
        return;
    }

    // qDebug() << "------we do have displayed car for edit content to display------";

    ui->plateInput->setText(displayedCar->getLicensePlate());

    ui->modelInput->setText(displayedCar->getModel());

    bool ava = displayedCar->isAvailable();

    if(!ava){
        ui->statusButton->setChecked(true);
        ui->renterNameInput->setText(displayedCar->getRenter().getName());
        ui->phoInput->setText(displayedCar->getRenter().getPhoNum());
        ui->startDateEdit->setDateTime(displayedCar->getRenter().getStartTime());
        ui->endDateEdit->setDateTime(displayedCar->getRenter().getEndTime());
        renterDisplay(true);
    }else{
        hideItems();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
