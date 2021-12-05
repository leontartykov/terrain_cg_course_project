#include <QApplication>
#include <iostream>

#include "interface/mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/polygon/polygon.hpp"
#include "driver/geometry/matrix/matrix.h"
#include "driver/geometry/triangle/triangle.hpp"
#include "driver/geometry/vector/vector_3.hpp"

int main(int argc, char *argv[])
{
    Vector3D<double> vector_1;
    Vector3D<double> vector_2(1, 2, 3);
    Vector3D<double> vector_3(4, 5, 6);

    vector_1 = vector_1 + vector_2;
    std::cout << "Вектор_1:";
    vector_1.output();

    vector_1 = vector_1 / 5;
    std::cout << "Вектор_1_new:";
    vector_1.output();

    std::vector<Vector3D<double>> vectors;
    vectors.clear();
    vectors.push_back(Vector3D<double>(1.0, 2.0, 3.0));
    vectors.push_back(Vector3D<double>(4.0, 5.0, 6.0));

    std::cout << "Вектор заполненный: ";
    for (int i = 0; i < vectors.size(); i++){
        vectors[i].output();
    }

    std::cout << "Вектор после очистки и заполнения: ";
    vectors.clear();
    vectors.push_back(Vector3D<double>(-1.0, -2.0, -3.0));
    vectors.push_back(Vector3D<double>(-4.0, -5.0, -6.0));
    for (int i = 0; i < vectors.size(); i++){
        vectors[i].output();
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
