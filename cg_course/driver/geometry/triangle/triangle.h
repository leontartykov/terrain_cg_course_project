#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <vector>

#include "driver/geometry/point/point.h"

template <typename T>
class Triangle
{
private:
    Point<T> _point_1;
    Point<T> _point_2;
    Point<T> _point_3;
public:
    Triangle(Point<T> point_1, Point<T> point_2, Point<T> point_3);
    ~Triangle();

    void output();
};

#endif
