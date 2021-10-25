#ifndef _POINT_H_
#define _POINT_H_

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

    void set_data_point(const T data_x, const T data_y, const T data_z);
    T get_x() const;
    T get_y() const;
    T get_z() const;
};

#endif