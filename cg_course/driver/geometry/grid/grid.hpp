#ifndef _GRID_HPP_
#define _GRID_HPP_

#include "driver/geometry/grid/grid.h"
#include "driver/transform/transform.h"

Grid3D::Grid3D()
{
    _line_start = Line(Point<double>(100, 100, 0), Point<double>(500, 100, 0.0));
    _line_end = Line(Point<double>(500, 700, 0.0), Point<double>(100, 700, 0.0));
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

void Grid3D::draw_grid()
{
    double start_x = _line_start.get_line()[0].get_x(),
            end_x = _line_start.get_line()[1].get_x(),
            start_y = _line_end.get_line()[0].get_y(),
            end_y = _line_end.get_line()[0].get_y();
    /*std::cout << "Start x = " << start_x << std::endl;
    std::cout << "End x = " << end_x << std::endl;
    std::cout << "Start y = " << start_y << std::endl;
    std::cout << "End y = " << end_y << std::endl;*/

    /*for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x, start_y, start_x, end_y);
        start_x += part;
    }*/
}

#endif
