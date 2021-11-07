#ifndef _LINE_HPP_
#define _LINE_HPP_

#include "driver/geometry/line/line.h"

Line::Line(Point<double> point_1, Point<double> point_2)
{
    _line.push_back(point_1);
    _line.push_back(point_2);
}

std::vector<Point<double>> &Line::get_line(){
    return _line;
}

void Line::output_line()
{
    for (int i = 0; i < 2; i++){
        std::cout << "(" << _line[i].get_x() << ", " << _line[i].get_y() << ", " << _line[i].get_z() << "), ";
    }
    std::cout << std::endl;
}

Point<double> &Line::get_start_point(){
    return _line[0];
}

Point<double> &Line::get_end_point(){
    return _line[1];
}

void Line::set_line(Line &old_line)
{
    _line[0].set_x(old_line.get_start_point().get_x());
    (*this).get_start_point().set_y(old_line.get_start_point().get_y());
    (*this).get_start_point().set_z(old_line.get_start_point().get_z());

    (*this).get_end_point().set_x(old_line.get_end_point().get_x());
    (*this).get_end_point().set_y(old_line.get_end_point().get_y());
    (*this).get_end_point().set_z(old_line.get_end_point().get_z());

    (*this).get_start_point().output_point();
    (*this).get_end_point().output_point();
}

void Line::rotate(rotate_t &rotate_angles)
{

}

#endif
