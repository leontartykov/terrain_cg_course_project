#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>

#include "driver/geometry/point.h"

class Polygon
{
private:
    std::vector<Point<double>> _points;

public:
    Polygon();
    explicit Polygon(std::initializer_list<Point<double>> items);
    ~Polygon();

    std::vector<Point<double>> &points();
};

#endif
