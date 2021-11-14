#include <cmath>

#include "driver/transform/transform.h"
#include "driver/geometry/point/point.hpp"

double transform_x_to_2d(const double coord, const double z);
double transform_y_to_2d(const double coord, const double z);

void transform_3d_into_2d(Point<double> &screen_points, Point<double> &point)
{
    screen_points.set_x(transform_x_to_2d(point.get_x(), point.get_z()));
    screen_points.set_y(transform_y_to_2d(point.get_y(), point.get_z()));
}

double transform_x_to_2d(const double coord, const double z)
{
    double x = (SCREEN_WIDTH / 4) + (coord * 1000) / (z + 1000);
    return x;
}

double transform_y_to_2d(const double coord, const double z)
{
    double y = (SCREEN_HEIGHT / 4) +  (coord * 1000) / (z + 1000);
    return y;
}

void shift_point_by_center(Point<double> &point, Point<double> &center_figure_point)
{
    double x = point.get_x() - center_figure_point.get_x();
    double y = point.get_y() - center_figure_point.get_y();
    double z = point.get_z() - center_figure_point.get_z();
    point.set_point(x, y, z);
}

void shift_point_back_by_center(Point<double> &point, Point<double> &center_figure_point)
{
    double x = point.get_x() + center_figure_point.get_x();
    double y = point.get_y() + center_figure_point.get_y();
    double z = point.get_z() + center_figure_point.get_z();
    point.set_point(x, y, z);
}

void rotate_point(Point<double> &point, rotate_t &rotate_angles)
{
    if (rotate_angles.angle_x != 0)
        rotate_x(point, rotate_angles.angle_x);
    if (rotate_angles.angle_y != 0)
        rotate_y(point, rotate_angles.angle_y);
    if (rotate_angles.angle_z != 0)
        rotate_z(point, rotate_angles.angle_z);
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
