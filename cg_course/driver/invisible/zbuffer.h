#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include <limits>
#include <vector>

#include "driver/geometry/matrix/matrix.h"
#include "driver/landscape/landscape.h"

typedef struct plane_koeffs_polygon plane_koeffs_t;
struct plane_koeffs_polygon
{
    double a;
    double b;
    double c;
    double d;
};

class ZBuffer: Matrix
{
private:
    std::vector<std::vector<double>> _zbuffer_matrix;
    std::vector<std::vector<QColor>> _color_matrix;
public:
    ZBuffer();
    ZBuffer(int width, int height);
    ~ZBuffer();

    void output();
    double get_z_point(int index_i, int index_j) const;
    void set_z_point(double value, int index_i, int index_j);

    std::vector<std::vector<double>> &get_zbuffer_matrix();
    std::vector<std::vector<QColor>> &get_color_matrix();

};

 void remove_invisible_lines(ZBuffer &zbuffer, Landscape &landscape);

#endif
