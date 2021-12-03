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


class Vector3D
{
private:
    double _x, _y, _z;
public:
    Vector3D();
    Vector3D(double x, double y, double z);
    ~Vector3D();

    double X();
    double Y();
    double Z();
    void set_vector(double x, double y, double z);

    void normalize();

    //Vector3D operator+ (Vector3D vector_1, Vector3D vec_2);
    Vector3D operator - (Vector3D &vector_2);
    Vector3D operator / (double length);

    void output();
};

Vector3D normal(Point<double> point_1, Point<double> point_2, Point<double> point_3);
double dot_product(Vector3D &vector_1, Vector3D &vector_2);

#endif
