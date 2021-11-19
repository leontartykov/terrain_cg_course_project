#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>
#include <QGraphicsScene>
#include "driver/geometry/point/point.h"
#include "driver/geometry/figure/figure.h"
#include "driver/geometry/line/line.h"

class Landscape
{
private:
    std::vector<std::vector<Point<double>>> _points;
    std::vector<std::vector<Point<double>>> _screen_points;

public:
    Landscape();
    ~Landscape();

    void form_landscape();
    void draw_landscape(QGraphicsScene *scene, QImage *image);

    void output_landscape();
    void output_screen_landscape();

    void rotate_landscape(rotate_t &rotate_angles);

    Point<double> &get_point(int index_i, int index_j);
    Point<double> &get_screen_point(int index_i, int index_j);
    int get_width();
    int get_height();
};

#endif
