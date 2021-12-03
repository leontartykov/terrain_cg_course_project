#include "vector.h"

Vector3D::Vector3D(): _x{0}, _y{0}, _z{0}{
}

Vector3D::Vector3D(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

Vector3D::~Vector3D(){

}

double Vector3D::X(){
    return _x;
}

double Vector3D::Y(){
    return _y;
}

double Vector3D::Z(){
    return _z;
}

void Vector3D::set_vector(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

Vector3D Vector3D::operator- (Vector3D &vector_2)
{
    Vector3D vector;
    vector.set_vector(this->_x - vector_2._x, this->_y - vector_2._y, this->_z - vector_2._z);

    return vector;
}

Vector3D Vector3D::operator / (double length){
    Vector3D vector;
    vector.set_vector(this->_x / length, this->_y / length, this->_z / length);

    return vector;
}

void Vector3D::output(){
    std::cout << "(" << _x << ", " << _y << ", " << _z << ")" << std::endl;
}

void Vector3D::normalize(){
    double length = sqrt(_x * _x + _y * _y + _z * _z);
    double inverse_length = 1 / length;

    _x *= inverse_length;
    _y *= inverse_length;
    _z *= inverse_length;
}


