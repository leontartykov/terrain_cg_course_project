#include <cmath>

#include "driver/geometry/line/line.h"
#include "driver/geometry/point/point.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/figure/figure.h"

void shift_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point);
void shift_back_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point);

void rotate_points(std::array<Point<double>, 2> &line, rotate_t &rotate_angles);
void rotate_x(Point<double> &point, double angle_x);
void rotate_y(Point<double> &point,  double angle_y);
void rotate_z(Point<double> &point,  double angle_z);

Line &Line::rotate_line(rotate_t &rotate_angles)
{
    Line line = (*this);
    Point<double> center_line_point;
    center_line_point.set_x((line.get_start_point().get_x() + line.get_end_point().get_x()) / 2);
    center_line_point.set_y((line.get_start_point().get_y() + line.get_end_point().get_y()) / 2);
    center_line_point.set_z((line.get_start_point().get_z() + line.get_end_point().get_z()) / 2);

    std::cout << "Исходный отрезок" << std::endl;
    (*this).output_line();
    std::cout << "Серединная точка отрезка" << std::endl;
    center_line_point.output_point();

    shift_by_center((*this).get_line(), center_line_point);
    std::cout << "Исходный отрезок после сдвига относительно серединной точки" << std::endl;
    (*this).output_line();

    rotate_points((*this).get_line(), rotate_angles);
    std::cout << "Исходный отрезок после поворота" << std::endl;
    (*this).output_line();

    shift_back_by_center((*this).get_line(), center_line_point);
    std::cout << "Исходный отрезок после обратного сдвига" << std::endl;
    (*this).output_line();
    return (*this);
}

void shift_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point)
{
    for (int i = 0; i < 2; i++)
    {
        line[i].set_x(line[i].get_x() - center_line_point.get_x());
        line[i].set_y(line[i].get_y() - center_line_point.get_y());
        line[i].set_z(line[i].get_z() - center_line_point.get_z());
    }
}

void shift_back_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point)
{
    for (int i = 0; i < 2; i++)
    {
        line[i].set_x(line[i].get_x() + center_line_point.get_x());
        line[i].set_y(line[i].get_y() + center_line_point.get_y());
        line[i].set_z(line[i].get_z() + center_line_point.get_z());
    }
}

void rotate_points(std::array<Point<double>, 2> &line, rotate_t &rotate_angles)
{
    for (int i = 0; i < 2; i++)
    {
        if (rotate_angles.angle_x != 0)
            rotate_x(line[i], rotate_angles.angle_x);
        if (rotate_angles.angle_y != 0)
            rotate_y(line[i], rotate_angles.angle_y);
        if (rotate_angles.angle_z != 0)
            rotate_z(line[i], rotate_angles.angle_z);
    }
}

void rotate_x(Point<double> &point, double angle_x)
{
    std::cout << "Изначальная точка (поворот х)" << std::endl;
    point.output_point();

    double temp_y = point.get_y(), temp_z = point.get_z();
    double angle = angle_x * M_PI / 180;
    double a_cos = cos(angle);
    double a_sin = sin(angle);

    point.set_y(temp_y * a_cos - temp_z * a_sin);
    point.set_z(temp_y * a_sin + temp_z * a_cos);

    std::cout << "Измененная точка (поворот х)" << std::endl;
    point.output_point();
}

void rotate_y(Point<double> &point,  double angle_y)
{
    std::cout << "Изначальная точка (поворот у)" << std::endl;
    point.output_point();
    double temp_x = point.get_x(), temp_z = point.get_z();
    double angle = angle_y * M_PI / 180;
    double a_cos = cos(angle);
    double  a_sin = sin(angle);

    point.set_x(temp_x * a_cos - temp_z * a_sin);
    point.set_z(temp_x * a_sin + temp_z * a_cos);
    std::cout << "Измененная точка (поворот у)" << std::endl;
    point.output_point();
}

void rotate_z(Point<double> &point,  double angle_z)
{
    double temp_x = point.get_x(), temp_y = point.get_y();
    double angle = angle_z * M_PI / 180;
    double a_cos = cos(angle);
    double a_sin = sin(angle);

    point.set_x(temp_x * a_cos - temp_y * a_sin);
    point.set_y(temp_x * a_sin + temp_y * a_cos);
}
