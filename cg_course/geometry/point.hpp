#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "point.h"

template <typename T>
Point<T>::Point(): x{0}, y{0}, z{0} {
}

template <typename T>
Point<T>::~Point() {
}

template <typename T>
void Point<T>::set_data_point(const T data_x, const T data_y, const T data_z)
{
    this->x = data_x;
    this->y = data_y;
    this->z = data_z;
}

template <typename T>
T Point<T>::get_x() const{
    return this->x;
}

template <typename T>
T Point<T>::get_y() const{
    return this->y;
}

template <typename T>
T Point<T>::get_z() const{
    return this->z;
}

#endif
