#ifndef CARMANAGER_H
#define CARMANAGER_H

#include <QList>
#include "car.h"
#include <QString>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>


class CarManager
{
public:
    static CarManager& getInstance() {
        static CarManager instance;
        return instance;
    }

    CarManager(){}
    int addCar(const Car &car);
    int removeCar(const Car &car);
    QList<Car> getCarList() const;

    Car *getCar(const QString &licensePlate);
    Car *getCarByRentersName(const QString &name);

    void readCarFile(const QString &fileName);
    void writeCarFile(const QString &fileName) const;
    void updateOrAddCar(const Car &updatedCar);

    QString capitalizeWords(const QString& s) const;

    void printAllCars() const {
        qDebug() << "Current cars in the system:";
        for (const Car& car : cars) {
            qDebug() << "Plate:" << car.getLicensePlate()<<"\n\n";
        }
    }


private:
    QList<Car> cars;
};

#endif // CARMANAGER_H
