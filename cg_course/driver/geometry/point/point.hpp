#ifndef _POINT_HPP_
#define _POINT_HPP_

#include "driver/geometry/point/point.h"

template <typename T>
Point<T>::Point(): _x{0}, _y{0}, _z{0} {
}

template <typename T>
Point<T>::Point(T x, T y, T z) noexcept: _x(x), _y(y), _z(z){
}

template <typename T>
Point<T>::~Point() {
}

template <typename T>
void Point<T>::set_point(const T data_x, const T data_y, const T data_z)
{
    _x = data_x;
    _y = data_y;
    _z = data_z;
}

template <typename T>
T Point<T>::get_x() const{
    return _x;
}

template <typename T>
T Point<T>::get_y() const{
    return _y;
}

template <typename T>
T Point<T>::get_z() const{
    return _z;
}

template <typename T>
void Point<T>::set_x(T x){
    _x = x;
}

template <typename T>
void Point<T>::set_y(T y){
    _y = y;
}

template <typename T>
void Point<T>::set_z(T z){
    _z = z;
}

template <typename T>
void Point<T>::output_point(){
    std::cout << "(" << _x << ", " << _y << ", " << _z << ")";// << std::endl;
}

template <typename T>
Point<T> &Point<T>::operator *= (double scale)
{
    _x *= scale;
    _y *= scale;
    _z *= scale;
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator += (double scale)
{
    _x += scale;
    _y += scale;
    _z += scale;
    return *this;
}

template <typename T>
Point<T> &Point<T>::operator -= (double scale)
{
    _x -= scale;
    _y -= scale;
    _z -= scale;
    return *this;
}

#endif
