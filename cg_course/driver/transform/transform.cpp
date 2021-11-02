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
    double x = ((coord * 1000) / (z + 1000));
    return x;
}

double transform_y_to_2d(const double coord, const double z)
{
    double y = ((coord * 1000) / (z + 1000));
    return y;
}
