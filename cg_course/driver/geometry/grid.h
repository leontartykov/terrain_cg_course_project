#ifndef _GRID_H_
#define _GRID_H_

#include "driver/geometry/point.h"
#include "driver/geometry/line.h"

class Grid3D
{
private:
    Line _line_start;
    Line _line_end;
public:
    Grid3D();
    ~Grid3D() {}

    Line get_start_line_grid();
    Line get_end_line_grid();
};

#endif
