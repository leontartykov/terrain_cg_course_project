#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream>

typedef struct rotate rotate_t;
struct rotate
{
    double angle_x;
    double angle_y;
    double angle_z;
};

class Figure
{
public:
    Figure() {}
    virtual ~Figure() = default;

protected:
    virtual void rotate(rotate_t &rotate_angles) = 0;
};

#endif
