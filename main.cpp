#include "carwindow.h"

#include <QApplication>

#include <QCoreApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QStandardPaths>
#include <QDir>




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Application started";  // 写入一条日志消息

    carWindow w;
    w.show();



    return a.exec();
}
