#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "driver/geometry/vector/vector.h"

class Camera
{
private:
    Vector3D _position; //позиция камеры
    Vector3D _target; //в какую точку смотрит
    Vector3D _direction; //вектор направления камеры
    Vector3D _up; //вектор вверх
    Vector3D _right;
public:
    Camera();
    ~Camera();
};

#endif
