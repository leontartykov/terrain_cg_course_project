#ifndef _LINE_H_
#define _LINE_H_

#include <vector>
#include "driver/geometry/point/point.h"
#include "driver/geometry/figure/figure.h"

class Line: public Figure
{
private:
    std::vector<Point<double>> _line;

public:
    Line() {}
    explicit Line(Point<double> point_1, Point<double> point_2);
    ~Line() {}

    std::vector<Point<double>> &get_line();
    Line &rotate_line(rotate_t &rotate_angles);
    void output_line();

    Point<double> &get_start_point();
    Point<double> &get_end_point();

    void set_line(Line &old_line);
    virtual void rotate(rotate_t &rotate_angles) override;
};

#endif
