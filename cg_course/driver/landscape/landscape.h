#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>
#include "driver/geometry/point/point.h"

class Landscape
{
private:
    std::vector<std::vector<Point<double>>> _points;
    std::vector<std::vector<Point<double>>> _screen_points;

public:
    Landscape();
    ~Landscape();

    void form_landscape();
    void draw_landscape();
    void output_landscape();
};

#endif
