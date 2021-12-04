#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QDebug>

#include "driver/geometry/point/point.h"
#include "driver/geometry/figure/figure.h"
#include "driver/geometry/line/line.h"
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/vector/vector.h"

class Landscape
{
private:
    std::vector<std::vector<Point<double>>> _points;
    std::vector<std::vector<Point<double>>> _screen_points;
    std::vector<std::vector<Vector3D<int>>> _normals;
    std::vector<std::vector<Vector3D<double>> _shading_normals;

public:
    Landscape();
    ~Landscape();

    void form_landscape();
    void transform_points_to_screen();
    void draw_landscape(ZBuffer &zbuffer, QGraphicsScene *scene, QImage *image);
    void remove_invisible_lines(ZBuffer &zbuffer, QGraphicsScene *scene, Vector3D<int> light_position);

    void output_landscape();
    void output_screen_landscape();

    void rotate_landscape(rotate_t &rotate_angles);

    Point<double> &get_point(int index_i, int index_j);
    Point<double> &get_screen_point(int index_i, int index_j);

    void find_all_landscape_normals();
    void find_average_normals_of_each_node();
    int get_width();
    int get_height();

};

#endif
