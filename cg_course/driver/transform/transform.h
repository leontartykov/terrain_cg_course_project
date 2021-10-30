#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "driver/geometry/point/point.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 754

void transform_3d_into_2d(Point<double> &screen_points, Point<double> &point);

#endif
