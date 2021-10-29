#ifndef _LINE_H_
#define _LINE_H_

#include <array>
#include "driver/geometry/point.h"
#include "driver/geometry/figure.h"

class Line: public Figure
{
private:
    std::array<Point<double>, 2> _line;

public:
    Line() {}
    explicit Line(Point<double> point_1, Point<double> point_2);
    ~Line() {}

    std::array<Point<double>, 2> &get_line();
};

#endif
