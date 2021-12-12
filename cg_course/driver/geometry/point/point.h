#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include <QDebug>

template <typename T>
class Point
{
private:
    T _x;
    T _y;
    T _z;

public:
    Point();
    Point(T x, T y, T z) noexcept;
    ~Point();

    void set_point(const T data_x, const T data_y, const T data_z);
    T get_x() const;
    T get_y() const;
    T get_z() const;

    void set_x(T x);
    void set_y(T y);
    void set_z(T z);
    Point<T> &operator *= (double scale);
    Point<T> &operator += (double scale);
    Point<T> &operator -= (double scale);

    void output_point();
};

#endif
