#ifndef _TRIANGLE_H_
#define _TRIANGLE_H_

#include <array>
#include <vector>

#include "driver/geometry/point/point.h"
#include "driver/geometry/vector/vector.h"

template <typename T>
class Triangle
{
private:
    std::array<Vector3D<T>, 3> _triangle;
public:
    Triangle();
    Triangle(Vector3D<T> point_1, Vector3D<T> point_2, Vector3D<T> point_3);
    ~Triangle();

    void set_triangle(Vector3D<T> point_1, Vector3D<T> point_2, Vector3D<T> point_3);
    //void &get_point();
    void swap_points(int index_first, int index_second);

    Vector3D<T> operator[] (int index);

    void output();
};

#endif
