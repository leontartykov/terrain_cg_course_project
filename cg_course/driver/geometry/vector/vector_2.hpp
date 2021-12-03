#include "vector.h"

Vector2D::Vector2D(): _x{0}, _y{0}{
}

Vector2D::Vector2D(double x, double y)
{
    _x = x;
    _y = y;
}

Vector2D::~Vector2D(){

}

double Vector2D::X(){
    return _x;
}

double Vector2D::Y(){
    return _y;
}

void Vector2D::set_vector(double x, double y)
{
    _x = x;
    _y = y;
}

void Vector2D::output(){
    std::cout << "(" << _x << ", " << _y << ") ";
}
