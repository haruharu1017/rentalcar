#include "car.h"
#include "renter.h"

Car::Car()
    : licensePlate(""), model(""), available(false) {}

Car::Car(const QString& licensePlate, const QString& model)
    : licensePlate(licensePlate), model(model), available(true), renter(){}

Car::Car(const QString &Plate, const QString &Model, bool isAva, const Renter& renterName)
    : licensePlate(Plate), model(Model), available(isAva), renter(renterName) {}


QString Car::getLicensePlate() const {
    return licensePlate;
}

QString Car::getModel() const {
    return model;
}

bool Car::isAvailable() const {
    return available;
}

Renter Car::getRenter() const {
    return renter;
}

bool Car::operator==(const Car &other) const
{
    return this->licensePlate == other.licensePlate;
}

void Car::setStatus(bool ava){
    available=ava;
}
