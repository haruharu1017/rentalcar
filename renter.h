#ifndef RENTER_H
#define RENTER_H

#include <QString>
#include <QDebug>
#include <QDateTime>


class Renter {
public:
    Renter() : name(""), phoNum("") {}
    Renter(const QString& name_, const QString& pho,const QDateTime& start, const QDateTime& end);

    QString getName() const;
    QString getPhoNum() const;
    QDateTime getStartTime() const;
    QDateTime getEndTime() const;

private:
    QString name;
    QString phoNum;
    QDateTime startTime;
    QDateTime endTime;
};

#endif // RENTER_H
