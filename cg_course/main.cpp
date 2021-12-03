#include <QApplication>
#include <iostream>

#include "interface/mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/polygon/polygon.hpp"
#include "driver/geometry/matrix/matrix.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
