#ifndef _GRID_HPP_
#define _GRID_HPP_

#include <cmath>
#include "driver/geometry/grid/grid.h"
#include "driver/transform/transform.h"
#include "driver/geometry/matrix/matrix.h"

Grid3D::Grid3D()
{
    _line_start = Line(Point<double>(100, 100, 0), Point<double>(500, 100, 0.0));
    _line_end = Line(Point<double>(100, 700, 0.0), Point<double>(500, 700, 0.0));
}

Line Grid3D::get_start_line_grid(){
    return _line_start;
}

Line Grid3D::get_end_line_grid(){
    return _line_end;
}

void Grid3D::set_start_line_grid(Line &old_line){
    _line_start.set_line(old_line);
}

void Grid3D::set_end_line_grid(Line &old_line){
    _line_end.set_line(old_line);
}

void Grid3D::draw_grid(QGraphicsScene *scene)
{
    Line screen_line_start(_line_start.get_start_point(), _line_start.get_end_point());
    Line screen_line_end(_line_end.get_start_point(), _line_end.get_end_point());

    transform_3d_into_2d(screen_line_start.get_start_point(), _line_start.get_start_point());
    transform_3d_into_2d(screen_line_start.get_end_point(), _line_start.get_end_point());

    transform_3d_into_2d(screen_line_end.get_start_point(), _line_end.get_start_point());
    transform_3d_into_2d(screen_line_end.get_end_point(), _line_end.get_end_point());

    double start_x_start_line = screen_line_start.get_start_point().get_x(),
                end_x_start_line = screen_line_start.get_end_point().get_x(),
                start_x_end_line = screen_line_end.get_start_point().get_x(),
                end_x_end_line = screen_line_end.get_end_point().get_x();

    double start_y_start_line = screen_line_start.get_start_point().get_y(),
                end_y_start_line = screen_line_start.get_end_point().get_y(),
                start_y_end_line = screen_line_end.get_start_point().get_y(),
                end_y_end_line = screen_line_end.get_end_point().get_y();

    double part_x_start_ver = (end_x_start_line - start_x_start_line) / 7,
                part_y_start_ver = (end_y_start_line - start_y_start_line) / 7,
                part_x_end_ver = (end_x_end_line - start_x_end_line) / 7,
                part_y_end_ver = (end_y_end_line - start_y_end_line) / 7;

    double part_x_start_hor = (start_x_start_line - start_x_end_line) / 7,
                part_y_start_hor = (start_y_start_line - start_y_end_line) / 7,
                part_x_end_hor = (end_x_start_line - end_x_end_line) / 7,
                part_y_end_hor = (end_y_start_line - end_y_end_line) / 7;

    screen_line_start.output_line();
    screen_line_end.output_line();

    scene->addLine(start_x_start_line, start_y_start_line, end_x_start_line, end_y_start_line);
    scene->addLine(start_x_end_line, start_y_end_line, end_x_end_line, end_y_end_line);

    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x_start_line, start_y_start_line, start_x_end_line, start_y_end_line);
        start_x_start_line += part_x_start_ver;
        start_x_end_line += part_x_end_ver;
        start_y_start_line += part_y_start_ver;
        start_y_end_line += part_y_end_ver;
    }

    start_x_end_line = screen_line_end.get_start_point().get_x();
    start_y_end_line = screen_line_end.get_start_point().get_y();
    end_x_end_line = screen_line_end.get_end_point().get_x();
    end_y_end_line = screen_line_end.get_end_point().get_y();

    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x_end_line, start_y_end_line, end_x_end_line, end_y_end_line);

        start_x_end_line += part_x_start_hor;
        start_y_end_line += part_y_start_hor;
        end_x_end_line += part_x_end_hor;
        end_y_end_line += part_y_end_hor;
    }
}

double **Grid3D::create_z_grid(int size_grid)
{
    double **z_grid = nullptr;
    z_grid = form_matrix_double(4);
    return z_grid;
}

/*
void Grid3D::draw_z_grid(QGraphicsScene *scene)
{
    Line screen_line_start(_line_start.get_start_point(), _line_start.get_end_point());
    Line screen_line_end(_line_end.get_start_point(), _line_end.get_end_point());

    transform_3d_into_2d(screen_line_start.get_start_point(), _line_start.get_start_point());
    transform_3d_into_2d(screen_line_start.get_end_point(), _line_start.get_end_point());

    transform_3d_into_2d(screen_line_end.get_start_point(), _line_end.get_start_point());
    transform_3d_into_2d(screen_line_end.get_end_point(), _line_end.get_end_point());

    for (int i = 0; i < )
}*/

#endif
