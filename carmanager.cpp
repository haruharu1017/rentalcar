#include "carmanager.h"
#include <iostream>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QStandardPaths>
#include <QDir>


QString CarManager::capitalizeWords(const QString& s) const {
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

int CarManager::addCar(const Car &car) {
    for (const auto& existingCar : cars) {
        if (existingCar.getLicensePlate().trimmed().toUpper() == car.getLicensePlate().trimmed().toUpper()) {
            return -1;
        }
    }
    cars.append(car);
    return 0;
}


int CarManager::removeCar(const Car &car) {
    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if (*it == car) {
            cars.erase(it);
            return 0;
        }
    }
    return -1;
}



QList<Car> CarManager::getCarList() const
{
    return cars;
}

Car* CarManager::getCar(const QString &licensePlate) {
    QString normalizedPlate = licensePlate.trimmed().toUpper();  // 标准化输入，去空格，转大写

    for (Car &car : cars) {
        qDebug()<<"getCar() plate: "<<car.getLicensePlate();
        if (car.getLicensePlate().trimmed().toUpper() == normalizedPlate) {
            return &car;  // 找到匹配的车牌，返回指针
        }
    }

    return nullptr;  // 未找到匹配的车牌，返回 nullptr
}

Car* CarManager::getCarByRentersName(const QString &name){
    QString normalizedName = capitalizeWords(name.trimmed());
    for (Car &car : cars) {
        if (capitalizeWords(car.getRenter().getName().trimmed())== normalizedName) {
            return &car;  // 找到匹配的车牌，返回指针
        }
    }

    return nullptr;  // 未找到匹配的车牌，返回 nullptr
}




void CarManager::readCarFile(const QString &fileName)
{
    cars.clear();
    QString dataPath = QCoreApplication::applicationDirPath()+"/"+fileName;
    qDebug()<<"app dir path: "<<QCoreApplication::applicationDirPath();
    QFile file(dataPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {

        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString plateNumber = in.readLine().trimmed();
        QString model = in.readLine().trimmed();
        bool isAvailable = in.readLine().trimmed() == "1";

        QString startTimeStr = in.readLine().trimmed();
        QString endTimeStr = in.readLine().trimmed();
        QString renterName = in.readLine().trimmed();
        QString renterContact = in.readLine().trimmed();

        QDateTime startTime;
        QDateTime endTime;
        if (!startTimeStr.isEmpty()) {
            startTime = QDateTime::fromString(startTimeStr, "yyyy-MM-dd");
        }
        if (!endTimeStr.isEmpty()) {
            endTime = QDateTime::fromString(endTimeStr, "yyyy-MM-dd");
        }

        Renter renter(renterName, renterContact, startTime, endTime);

        Car car(plateNumber, model, isAvailable, renter);
        cars.append(car);
    }

    file.close();
}

void CarManager::writeCarFile(const QString &fileName) const {
    QString dataPath = QCoreApplication::applicationDirPath() +"/"+fileName;
    QFile file(dataPath);

    // QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);

    for (const Car &car : cars) {
        out << car.getLicensePlate().toUpper() << "\n";
        out << car.getModel() << "\n";
        out << (car.isAvailable() ? "1" : "0") << "\n";

        if (!car.isAvailable()) {
            out << car.getRenter().getStartTime().toString("yyyy-MM-dd") << "\n";
            out << car.getRenter().getEndTime().toString("yyyy-MM-dd") << "\n";
            out <<capitalizeWords(car.getRenter().getName())<< "\n";
            out << car.getRenter().getPhoNum() << "\n";
        } else {
            out << "\n\n\n\n"; // 确保即使车辆可用也保持格式一致
        }
    }

    file.close();
}

void CarManager::updateOrAddCar(const Car &updatedCar) {
    for (Car &car : cars) {
        if (car.getLicensePlate() == updatedCar.getLicensePlate()) {
            car = updatedCar;  // 直接更新车辆信息
            return;
        }
    }
    // 如果没有找到，就添加新车
    cars.append(updatedCar);
}


