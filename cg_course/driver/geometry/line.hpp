#ifndef _LINE_HPP_
#define _LINE_HPP_

#include "driver/geometry/line.h"

Line::Line(Point<double> point_1, Point<double> point_2)
{
    _line[0] = point_1;
    _line[1] = point_2;
}

std::array<Point<double>, 2> &Line::get_line(){
    return _line;
}

#endif
