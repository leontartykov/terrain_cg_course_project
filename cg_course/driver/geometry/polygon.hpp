#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include "driver/geometry/polygon.h"

Polygon::Polygon(): _points(){
}

Polygon::~Polygon(){
}

Polygon::Polygon(std::initializer_list<Point<double>> items): _points(items){
}

int Polygon::get_amount(){
  return _points.size();
}

Point<double> Polygon::operator [] (int index){
    if (index >= 0 && _points.size())
        return _points[index];
}



#endif
