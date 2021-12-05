#ifndef _VECTOR_H_
#define _VECTOR_H_

#include <iostream>
#include <cmath>

#include "driver/geometry/point/point.h"

class Vector2D
{
private:
    double _x, _y;
public:
    Vector2D();
    Vector2D(double x, double y);
    ~Vector2D();

    double X();
    double Y();

    void set_vector(double x, double y);
    void output();
};

template <typename T>
class Vector3D
{
private:
    T _x, _y, _z;
public:
    Vector3D();
    Vector3D(T x, T y, T z);
    ~Vector3D();

    T X();
    T Y();
    T Z();
    void set_vector(T x, T y, T z);
    void reset();

    void normalize();

    Vector3D<T> &operator += (Vector3D &vector);
    Vector3D<T> operator - (Vector3D &vector_2);
    Vector3D<T> operator + (Vector3D<T> &vector_2);
    Vector3D<T> operator / (double length);
    Vector3D<T> &operator /= (double length);

    void output();
};

template <typename T1, typename T2>
Vector3D<T1> find_normal(Point<T2> point_1, Point<T2> point_2, Point<T2> point_3);

template <typename T1, typename T2>
double dot_product(Vector3D<T1> &vector_1, Vector3D<T2> &vector_2);

#endif
