#ifndef CAR_H
#define CAR_H

#include <QString>
#include <QDateTime>
#include <QDebug>


#include "renter.h"

class Car
{
public:
    Car();
    Car(const QString& licensePlate, const QString& model);
    Car(const QString &licensePlate, const QString &model, bool isAva, const Renter& renterName);

    QString getLicensePlate() const;
    QString getModel() const;
    bool isAvailable() const;
    Renter getRenter() const;
    bool operator==(const Car &other) const;
    void setStatus(bool ava);


protected:
    QString licensePlate;
    QString model;
    bool available;
    Renter renter;
};

#endif // CAR_H
