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

    double ka() {return _ka;}
    double ia() {return _ia;}
    double kd() {return _kd;}
    double id() {return _id;}
    double is() {return _is;}
    double ks() {return _ks;}

    void set_ka(double ka) {_ka = ka;}
    void set_ia(double ia) {_ia = ia;}

    void set_kd(double kd) {_kd = kd;}
    void set_id(double id) {_id = id;}

    void set_is(double is) {_is = is;}
    void set_ks(double ks) {_ks = ks;}

    void adjust_illumination();
    Vector3D<int> get_position();
};

#endif
