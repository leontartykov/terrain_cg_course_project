#ifndef _GRID_HPP_
#define _GRID_HPP_

#include "driver/geometry/grid.h"

Grid3D::Grid3D()
{
    _line_start = Line(Point<double>(100, 100, 0), Point<double>(500, 100, 0.0));
    _line_end = Line(Point<double>(500, 700, 0.0), Point<double>(100, 700, 0.0));
}

Line Grid3D::get_start_line_grid(){
    return _line_start;
}

Line Grid3D::get_end_line_grid(){
    return _line_end;
}

#endif
