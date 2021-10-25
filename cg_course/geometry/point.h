#ifndef _POINT_H_
#define _POINT_H_

template <typename T>
class Point
{
private:
    T x;
    T y;
    T z;

public:
    Point();
    ~Point();

    void set_data_point(const T data_x, const T data_y, const T data_z);
    T get_x() const;
    T get_y() const;
    T get_z() const;
};

#endif
