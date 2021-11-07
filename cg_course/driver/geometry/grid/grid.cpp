#include "driver/geometry/grid/grid.h"
#include "driver/geometry/point/point.hpp"
#include "driver/transform/transform.h"

void Grid3D::rotate(rotate_t &rotate_angles)
{
    Point<double> center_line_point;
    Line line_start = (*this).get_start_line_grid();
    Line line_end = (*this).get_end_line_grid();

    center_line_point.set_point((line_start.get_start_point().get_x() + line_end.get_end_point().get_x()) / 2,
                                                (line_start.get_start_point().get_y() + line_end.get_end_point().get_y()) / 2,
                                                (line_start.get_start_point().get_z() + line_end.get_end_point().get_z()) / 2);

    /*std::cout << "Центр сетки равен = ";
    center_line_point.output_point();*/

    for (int i = 0; i < line_start.get_line().size(); i++){
        shift_point_by_center(line_start.get_line()[i], center_line_point);
        shift_point_by_center(line_end.get_line()[i], center_line_point);

        rotate_point(line_start.get_line()[i], rotate_angles);
        rotate_point(line_end.get_line()[i], rotate_angles);

        shift_point_back_by_center(line_start.get_line()[i], center_line_point);
        shift_point_back_by_center(line_end.get_line()[i], center_line_point);
    }

    (*this).set_start_line_grid(line_start);
    (*this).set_end_line_grid(line_end);
}

void fill_z_grid(double ***z_grid, int size_grid)
{
    for (int i = 0; i < size_grid; i++){
        for (int j = 0; j < size_grid; j++){
            (*z_grid)[i][j] = i + j;
        }
    }
}

void draw_new_z_grid(double **new_z_grid, QGraphicsScene *scene)
{/*
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            scene->addLine(100 * (i + 1), 100 * (i + 1), )
        }
    }*/
}
