#include <cmath>

#include "driver/geometry/grid/grid.h"
#include "driver/geometry/point/point.hpp"

void shift_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point);
void shift_back_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point);

void rotate_points(std::array<Point<double>, 2> &line, rotate_t &rotate_angles);
void rotate_x(Point<double> &point, double angle_x);
void rotate_y(Point<double> &point,  double angle_y);
void rotate_z(Point<double> &point,  double angle_z);

void Grid3D::rotate_grid(rotate_t &rotate_angles)
{
    Point<double> center_line_point;
    Line line_start = (*this).get_start_line_grid();
    Line line_end = (*this).get_end_line_grid();
    center_line_point.set_x((line_start.get_start_point().get_x() + line_end.get_end_point().get_x()) / 2);
    center_line_point.set_y((line_start.get_start_point().get_y() + line_end.get_end_point().get_y()) / 2);
    center_line_point.set_z((line_start.get_start_point().get_z() + line_end.get_end_point().get_z()) / 2);

    std::cout << "Центр сетки равен = ";
    center_line_point.output_point();

    shift_by_center(line_start.get_line(), center_line_point);
    shift_by_center(line_end.get_line(), center_line_point);

    rotate_points(line_start.get_line(), rotate_angles);
    rotate_points(line_end.get_line(), rotate_angles);

    shift_back_by_center(line_start.get_line(), center_line_point);
    shift_back_by_center(line_end.get_line(), center_line_point);

    (*this).set_start_line_grid(line_start);
    (*this).set_end_line_grid(line_end);
}

void shift_by_center(std::array<Point<double>, 2> &line, Point<double> center_line_point)
{
    std::cout << "Точка до перемещения" << std::endl;
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
    double temp_y = point.get_y(), temp_z = point.get_z();
    double angle = angle_x * M_PI / 180;
    double a_cos = cos(angle);
    double a_sin = sin(angle);

    point.set_y(temp_y * a_cos + temp_z * a_sin);
    point.set_z(-temp_y * a_sin + temp_z * a_cos);
}

void rotate_y(Point<double> &point,  double angle_y)
{
    double temp_x = point.get_x(), temp_z = point.get_z();
    double angle = angle_y * M_PI / 180;
    double a_cos = cos(angle);
    double  a_sin = sin(angle);

    point.set_x(temp_x * a_cos + temp_z * a_sin);
    point.set_z(-temp_x * a_sin + temp_z * a_cos);
}

void rotate_z(Point<double> &point,  double angle_z)
{
    double temp_x = point.get_x(), temp_y = point.get_y();
    double angle = angle_z * M_PI / 180;
    double a_cos = cos(angle);
    double a_sin = sin(angle);

    point.set_x(temp_x * a_cos + temp_y * a_sin);
    point.set_y(-temp_x * a_sin + temp_y * a_cos);
}

void fill_z_grid(double ***z_grid, int size_grid)
{
    for (int i = 0; i < size_grid; i++){
        for (int j = 0; j < size_grid; j++){
            (*z_grid)[i][j] = i + j;
        }
    }
}

void draw_new_z_grid(double **new_z_grid, QGraphicsScene *scene)
{/*
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            scene->addLine(100 * (i + 1), 100 * (i + 1), )
        }
    }*/
}
