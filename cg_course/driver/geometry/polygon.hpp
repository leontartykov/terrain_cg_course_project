#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include "driver/geometry/polygon.h"

Polygon::Polygon(): _points(){
}

Polygon::~Polygon(){
}

Polygon::Polygon(std::initializer_list<Point<double>> items): _points(items){
}

std::vector<Point<double>>&Polygon::points(){
    return _points;
}

#endif
