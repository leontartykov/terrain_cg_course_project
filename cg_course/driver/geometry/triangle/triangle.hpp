#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "triangle.h"

template <typename T>
Triangle<T>::Triangle(Point<T> point_1, Point<T> point_2, Point<T> point_3)
{
    _point_1 = point_1;
    _point_2 = point_2;
    _point_3 = point_3;
}

template <typename T>
Triangle<T>::~Triangle(){

}

template <typename T>
void Triangle<T>::output(){
    std::cout << "[";
    _point_1.output_point();
    _point_2.output_point();
    _point_3.output_point();
    std::cout << "]";
}

#endif
