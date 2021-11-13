#include <math.h>
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/figure/figure.h"
#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.hpp"

void rasterize_triangle(Point<double> &point_1, Point<double> &point_2, Point<double> &point_3, int number);

double find_max_point(double value_1, double value_2, double value_3);
void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<double> &min_point);
void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<double> &max_point);
void find_middle_point(Point<double> &middle_point, Point<double> &min_point, Point<double> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3);

void remove_invisible_lines(ZBuffer &zbuffer, Landscape &landscape)
{
    std::cout << "landscape.get_height() = " << landscape.get_height() << std::endl;
    std::cout << "landscape.get_width() = " << landscape.get_width() << std::endl;

    for (int i = 0; i < landscape.get_height(); i++){
        std::cout << "i = " << i << std::endl;
        for (int j = 0; j < landscape.get_width(); j++){
            if (i == 0 && j <= 1 )/*i < landscape.get_height() - 1 && j < landscape.get_width() - 1)*/{
                rasterize_triangle(landscape.get_screen_point(i, j), landscape.get_screen_point(i, j + 1), landscape.get_screen_point(i + 1, j + 1), i+j);
                rasterize_triangle(landscape.get_screen_point(i, j), landscape.get_screen_point(i + 1, j), landscape.get_screen_point(i + 1, j + 1), i+j);
            }
        }
    }

    /*
    int size_row = landscape.get_height(),
         size_column = landscape.get_width();

    int x = 0, y = 0;
    double z = 0;

    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < size_column; j++)
        {
            x = landscape.get_screen_point(i, j).get_x();
            y = landscape.get_screen_point(i, j).get_y();
            z = landscape.get_point(i, j).get_z();
            //std::cout << "landscape.get_point_z (z) = " << z << " zbuffer.get_z_point(x, y) = " << zbuffer.get_z_point(x, y) << std::endl;
            if (z < zbuffer.get_z_point(x, y)){
                zbuffer.set_z_point(z, x, y);
                //std::cout << "new_zbuffer.get_z_point = " << zbuffer.get_z_point(x, y) << std::endl;
            }
        }
    }*/

}

void rasterize_triangle(Point<double> &point_1, Point<double> &point_2, Point<double> &point_3, int number)
{
    /*std::cout << number << " :";
    std::cout << "point_1: ";
    point_1.output_point();
    std::cout << "point_2: ";
    point_2.output_point();
    std::cout << "point_3: ";
    point_3.output_point();
    std::cout << std::endl;*/

    Point<double> min_point, max_point, middle_point;
    find_min_point(point_1, point_2, point_3, min_point);

    find_max_point(point_1, point_2, point_3, max_point);
    find_middle_point(middle_point, min_point, max_point,
                                 point_1, point_2, point_3);
    //double y_max = find_max_point(point_1.get_y(), point_2.get_y(), point_3.get_y());
    //double y_middle = find_middle_point(point_1, point_2, point_3, min_point, y_max);

    /*std::cout << " min_point: ";
    min_point.output_point();
    std::cout << std::endl;

    std::cout << " max_point: ";
    max_point.output_point();
    std::cout << std::endl;

    std::cout << " middle_point: ";
    middle_point.output_point();
    std::cout << std::endl;*/

    //std::cout << " y_max: " << y_max << std::endl;
    //std::cout << " y_middle: " << y_middle << std::endl;

    double dx_12 = 0, dx_23 = 0, dx_13 = 0;

    //std::cout << "(int)(middle_point.get_x() = " << (int)middle_point.get_x() << std::endl;

    if ((int)middle_point.get_y() - (int)min_point.get_y() != 0){
            dx_12 = (min_point.get_x() - middle_point.get_x()) / ((int)min_point.get_y() - (int)middle_point.get_y());
    }

    if ((int)max_point.get_y() - (int)middle_point.get_y() != 0){
            dx_23 = (middle_point.get_x() - max_point.get_x()) / ((int)middle_point.get_y() - (int)max_point.get_y());
    }

    if ((int)max_point.get_y() - (int)min_point.get_y() != 0){
            dx_13 = (min_point.get_x() - max_point.get_x()) / ((int)min_point.get_y() - (int)max_point.get_y());
    }

    //std::cout << "dx_12 = " << dx_12 << std::endl;
    //std::cout << "dx_23 = " << dx_23 << std::endl;
    //std::cout << "dx_13 = " << dx_13 << std::endl;

    double fixed_point_x_12 = min_point.get_x();
    double fixed_point_x_13 = min_point.get_x();

    double min_fixed_x = 0, max_fixed_x = 0;
    double min_dx = 0, max_dx = 0;
    int exchanged = 0;

    if (fixed_point_x_12 + dx_12 < fixed_point_x_13 + dx_13)
    {
        min_fixed_x = fixed_point_x_12;
        max_fixed_x = fixed_point_x_13;
        min_dx = dx_12;
        max_dx = dx_13;
    }
    else
    {
        min_fixed_x = fixed_point_x_13;
        max_fixed_x = fixed_point_x_12;
        min_dx = dx_13;
        max_dx = dx_12;
        exchanged = 1;
    }

    //std::cout << "min_fixed_x =" << min_fixed_x << std::endl;
    //std::cout << "max_fixed_x =" << max_fixed_x << std::endl;

    //std::cout << "min_dx =" << min_dx << std::endl;
    //std::cout << "max_dx =" << max_dx << std::endl;


    //std::cout << "Верхний треугольник: " << std::endl;
    for (int y = min_point.get_y(); y <= middle_point.get_y(); y++){
        for (int x = min_fixed_x; x <= max_fixed_x; x++){
            //std::cout << "(" << x << " " << y << ") ";
        }
        //std::cout << std::endl;


        min_fixed_x += min_dx;
        max_fixed_x += max_dx;
    }

    min_fixed_x -= min_dx;
    //std::cout << "min_fixed_x =" << min_fixed_x << std::endl;
    min_fixed_x = std::round(min_fixed_x);
    //std::cout << "min_fixed_x =" << min_fixed_x << std::endl;
    //max_fixed_x = std::round(max_fixed_x);
    //std::cout << "max_fixed_x =" << max_fixed_x << std::endl;

    if (exchanged == 0)
    {
        min_dx = dx_23;
        max_dx = dx_13;
    }
    else
    {
        min_dx = dx_13;
        max_dx = dx_23;
    }

    //std::cout << "Нижний треугольник: " << std::endl;
    for (int y = middle_point.get_y() + 1; y <= max_point.get_y(); y++){
        for (int x = min_fixed_x; x < max_fixed_x; x += 1){
            //std::cout << "(" << (int)x << " " << y << ") ";
        }
        //std::cout << std::endl;

        min_fixed_x += min_dx;
        max_fixed_x += max_dx;
    }

    //std::cout << "min_fixed_x =" << min_fixed_x << std::endl;
    //std::cout << "max_fixed_x =" << max_fixed_x << std::endl;
}

void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<double> &min_point)
{
    min_point.set_point(point_1.get_x(), point_1.get_y(), 0);

    if (point_2.get_y() < min_point.get_y()){
        min_point.set_y(point_2.get_y());
        min_point.set_x(point_2.get_x());
    }

    if (point_3.get_y() < min_point.get_y()){
        min_point.set_y(point_3.get_y());
        min_point.set_x(point_3.get_x());
    }
}

void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<double> &max_point)
{
    max_point.set_point(point_1.get_x(), point_1.get_y(), 0);
    if (point_2.get_y() > max_point.get_y()){
        max_point.set_y(point_2.get_y());
        max_point.set_x(point_2.get_x());
    }

    if (point_3.get_y() > max_point.get_y()){
        max_point.set_y(point_3.get_y());
        max_point.set_x(point_3.get_x());
    }
}

void find_middle_point(Point<double> &middle_point, Point<double> &min_point, Point<double> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3)
{
    double y_middle = 0;
    int is_middle = 0; //если сторона || оси Оу
    if (point_1.get_y() != min_point.get_y()){
        if(point_1.get_y() != max_point.get_y()){
            middle_point.set_point(point_1.get_x(), point_1.get_y(), 0);
            is_middle = 1;
        }
    }

    if (point_2.get_y() != min_point.get_y()){
        if(point_2.get_y() != max_point.get_y()){
             middle_point.set_point(point_2.get_x(), point_2.get_y(), 0);
             is_middle = 1;
        }
    }

    if (point_3.get_y() != min_point.get_y()){
        if(point_3.get_y() != max_point.get_y()){
            middle_point.set_point(point_3.get_x(), point_3.get_y(), 0);
            is_middle = 1;
        }
    }

    if (is_middle == 0){
        double x_min = point_1.get_x();
        if (point_2.get_x() < x_min)
            x_min = point_2.get_x();

        if (point_3.get_x() < x_min)
            x_min = point_3.get_x();

        middle_point.set_point(x_min, max_point.get_y(), 0);
    }
}

