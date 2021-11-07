#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include <limits>
#include <vector>

#include "driver/geometry/matrix/matrix.h"

class ZBuffer: Matrix
{
private:
    std::vector<std::vector<int>> _zbuffer_matrix;
public:
    ZBuffer();
    ZBuffer(int width, int height);
    ~ZBuffer();

    void output();
    double get_z_point(int index_i, int index_j);
};

#endif
