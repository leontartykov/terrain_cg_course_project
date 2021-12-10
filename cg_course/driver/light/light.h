#ifndef _LIGHT_H_
#define _LIGHT_H_

#include <QColor>
#include "driver/geometry/vector/vector.h"
//#include "driver/invisible/zbuffer.h"

class Light
{
private:
    double _kd;
    double _ks;
    double _ka;

    double _id;
    double _is;
    double _ia;

    Vector3D<int> _position;
    Vector3D<int> _direction;
public:
    Light();
    ~Light();

    void adjust_illumination();
    Vector3D<int> get_position();
    void set_position(int x, int y, int z);

    void output_light_position();
};

#endif
