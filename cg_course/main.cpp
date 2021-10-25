#include <QApplication>
#include <iostream>

#include "interface/mainwindow.h"
#include "geometry/point.hpp"


int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //return a.exec();

    Point<int> point;
    std::cout << "Координата х точки:" << point.get_x() << std::endl;
    return 0;
}
