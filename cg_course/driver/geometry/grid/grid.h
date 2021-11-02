#ifndef _GRID_H_
#define _GRID_H_

#include <QGraphicsScene>

#include "driver/geometry/point/point.h"
#include "driver/geometry/line/line.h"

class Grid3D
{
private:
    Line _line_start;
    Line _line_end;
public:
    Grid3D();
    ~Grid3D() {}

    Line get_start_line_grid();
    Line get_end_line_grid();

    void set_start_line_grid(Line &old_line);
    void set_end_line_grid(Line &old_line);

    void rotate_grid(rotate_t &rotate_angles);
    void draw_grid(QGraphicsScene *scene);

    double **create_z_grid(int size_grid);
};

void fill_z_grid(double ***z_grid, int size_grid);
void draw_new_z_grid(double **new_z_grid, QGraphicsScene *scene);

#endif
