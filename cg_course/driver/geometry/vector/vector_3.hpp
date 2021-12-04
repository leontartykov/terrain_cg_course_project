#include "vector.h"

template <typename T>
Vector3D<T>::Vector3D(): _x{0}, _y{0}, _z{0}{
}

template <typename T>
Vector3D<T>::Vector3D(T x, T y, T z)
{
    _x = x;
    _y = y;
    _z = z;
}

template <typename T>
Vector3D<T>::~Vector3D(){

}

template <typename T>
 T Vector3D<T>::X(){
    return _x;
}

 template <typename T>
T Vector3D<T>::Y(){
    return _y;
}

template <typename T>
T Vector3D<T>::Z(){
    return _z;
}

template <typename T>
void Vector3D<T>::set_vector(T x, T y, T z)
{
    _x = x;
    _y = y;
    _z = z;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator- (Vector3D &vector_2)
{
    Vector3D<T> vector;
    vector.set_vector(this->_x - vector_2._x, this->_y - vector_2._y, this->_z - vector_2._z);

    return vector;
}

template <typename T>
Vector3D<T> Vector3D<T>::operator / (double length){
    Vector3D<T> vector;
    vector.set_vector(this->_x / length, this->_y / length, this->_z / length);

    return vector;
}

template <typename T>
void Vector3D<T>::output(){
    std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
}

template <typename T>
void Vector3D<T>::normalize(){
    double length = sqrt(_x * _x + _y * _y + _z * _z);
    double inverse_length = 1 / length;

    _x *= inverse_length;
    _y *= inverse_length;
    _z *= inverse_length;
}

template <typename T1, typename T2>
double dot_product(Vector3D<T1> &vector_1, Vector3D<T2> &vector_2){
    return vector_1.X() * vector_2.X() + vector_1.Y() * vector_2.Y() + vector_1.Z() * vector_2.Z();
}

template <typename T1, typename T2>
Vector3D<T1> find_normal(Point<T2> point_1, Point<T2> point_2, Point<T2> point_3)
{
    Vector3D<T1> normal_vector;
    Point<T1> int_point_1(point_1.get_x(), point_1.get_y(), point_1.get_z());
    Point<T1> int_point_2(point_3.get_x(), point_2.get_y(), point_2.get_z());
    Point<T1> int_point_3(point_2.get_x(), point_3.get_y(), point_3.get_z());

    double vector_1_x = 0, vector_1_y = 0, vector_1_z = 0;
    double vector_2_x = 0, vector_2_y = 0, vector_2_z = 0;

    vector_1_x = int_point_2.get_x() - int_point_1.get_x();
    vector_1_y = int_point_2.get_y() - int_point_1.get_y();
    vector_1_z = int_point_2.get_z() - int_point_1.get_z();

    vector_2_x = int_point_3.get_x() - int_point_1.get_x();
    vector_2_y = int_point_3.get_y() - int_point_1.get_y();
    vector_2_z = int_point_3.get_z() - int_point_1.get_z();

    double a = vector_1_y * vector_2_z - vector_1_z * vector_2_y;
    double b = vector_2_x * vector_1_z - vector_2_z * vector_1_x;
    double c = vector_1_x * vector_2_y - vector_1_y * vector_2_x;

    normal_vector.set_vector(a, b, c);

    return normal_vector;
}

template <typename T1, typename T2>
ind_average_normals_of_each_node()