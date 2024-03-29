#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <iostream>

#include "driver/geometry/figure/figure.h"
#include "driver/geometry/point/point.h"

class Polygon: public Figure
{
private:
    std::vector<Point<double>> _points;

public:
    Polygon();
    explicit Polygon(std::initializer_list<Point<double>> items);
    ~Polygon();

    int get_amount();
    Point<double> operator[] (int index);
    void output_polygon();
    virtual void rotate(rotate_t &rotate_angles) override;

    //void rotate_polygon(int angle_x, int angle_y, int angle_z);
};

class Rectangle: public Polygon{
};

#endif
