#include <QApplication>
#include <iostream>

#include "interface/mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/polygon/polygon.hpp"
#include "driver/perlin/perlin.hpp"
#include "driver/geometry/matrix/matrix.h"

double **form_matrix_double(int size_matrix);

int main(int argc, char *argv[])
{
    Point<int> point(3, 4, 5);
    //std::cout << "Координата х точки:" << point.get_x() << std::endl;

    Polygon polygon({Point<double>(10, 10.0, 10.0), Point<double>(50.0, 50.0, 0.0)});

    //std::cout << "Количество точек полигона: " << polygon.get_amount() << std::endl;
    //std::cout << polygon[0].get_x() << std::endl;
    polygon.output_polygon();

    perlin::Perlin map(1532512342);
    int size_matrix = 512;

    std::cout << "MATRIX";
    double **matrix = nullptr;
    matrix = form_matrix_double(size_matrix);

    /*double frequency = 8;
    double fx = size_matrix / frequency;
    double fy = size_matrix / frequency;

    std::cout << "PERLIN";

    for (int y = 50; y < 55; ++y){
        for (int x = 50; x < 55; ++x){
            matrix[y][x] = map.accumulatedNoise2D(x / fx, y / fy, 8, 2.0f, 0.25f);
        }
    }

    output_matrix(matrix, 55);*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
    //return 0;
}
