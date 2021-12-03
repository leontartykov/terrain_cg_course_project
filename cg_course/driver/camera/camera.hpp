#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "camera.h"

Camera::Camera(){
    _position.set_vector(0, 0, 5);
    _target.set_vector(0, 0, 0);
    _direction.normalize(_position - _target);
}

Camera::~Camera(){

}

#endif
