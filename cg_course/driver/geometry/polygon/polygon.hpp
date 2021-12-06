#ifndef _POLYGON_HPP_
#define _POLYGON_HPP_

#include "driver/geometry/polygon/polygon.h"

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
     return _points[index];
}

void Polygon::output_polygon(){
    for (int i = 0; i < _points.size(); i++){
        std::cout << "(" << _points[i].get_x() << ", " << _points[i].get_y() << ", " << _points[i].get_z() << "), ";
    }
    std::cout << std::endl;
}

void Polygon::rotate(rotate_t &rotate_angles)
{

}

#endif
