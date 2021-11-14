#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include <array>
#include <vector>
#include "driver/geometry/point/point.h"
#include "driver/geometry/figure/figure.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 754

void transform_3d_into_2d(Point<double> &screen_points, Point<double> &point);

void shift_point_by_center(Point<double> &point, Point<double> &center_figure_point);
void shift_point_back_by_center(Point<double> &point, Point<double> &center_figure_point);

void rotate_point(Point<double> &point, rotate_t &rotate_angles);
void rotate_x(Point<double> &point, double angle_x);
void rotate_y(Point<double> &point,  double angle_y);
void rotate_z(Point<double> &point,  double angle_z);

#endif
