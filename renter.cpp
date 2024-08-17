#include "renter.h"



Renter::Renter(const QString& name_, const QString& pho, const QDateTime& start, const QDateTime& end)
    : name(name_), phoNum(pho), startTime(start), endTime(end){
}

QString Renter::getName() const {
    return name;
}

QString Renter::getPhoNum() const {
    return phoNum;
}

QDateTime Renter::getStartTime() const {
    return startTime;
}

QDateTime Renter::getEndTime() const {
    return endTime;
}
