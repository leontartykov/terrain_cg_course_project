#include <QApplication>
#include <iostream>

#include "interface/mainwindow.h"
#include "driver/geometry/point.hpp"
#include "driver/geometry/polygon.hpp"


int main(int argc, char *argv[])
{
    Point<int> point(3, 4, 5);
    std::cout << "Координата х точки:" << point.get_x() << std::endl;

    Polygon polygon({Point<double>(0.0, 0.0, 0.0), Point<double>(0.0, 100.0, 0.0)});

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}
