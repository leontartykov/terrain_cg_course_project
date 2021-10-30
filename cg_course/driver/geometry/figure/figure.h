#ifndef _FIGURE_H_
#define _FIGURE_H_

#include <iostream>

class Figure
{
public:
    Figure() {}
    virtual ~Figure() = default;
};

typedef struct rotate rotate_t;
struct rotate
{
    double angle_x;
    double angle_y;
    double angle_z;
};

#endif
