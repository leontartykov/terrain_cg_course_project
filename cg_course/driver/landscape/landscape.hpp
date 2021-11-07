#ifndef _LANDSCAPE_HPP_
#define _LANDSCAPE_HPP_

#include "driver/geometry/point/point.h"
#include "driver/landscape/landscape.h"
#include "driver/perlin/perlin.hpp"
#include "driver/transform/transform.h"

#define WIDTH_LANDSCAPE 20
#define HEIGHT_LANDSCAPE 20

Landscape::Landscape()
{
    for (int i = 0; i < WIDTH_LANDSCAPE; i++){
        std::vector<Point<double>> temp;
        for (int j = 0; j < HEIGHT_LANDSCAPE; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _points.push_back(temp);
    }

    for (int i = 0; i < WIDTH_LANDSCAPE; i++){
        std::vector<Point<double>> temp;
        for (int j = 0; j < HEIGHT_LANDSCAPE; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _screen_points.push_back(temp);
    }
}

Landscape::~Landscape(){
}

void Landscape::form_landscape()
{
    perlin::Perlin map(1532512342);
    double frequency = 8;
    double fx = WIDTH_LANDSCAPE / frequency;
    double fy = HEIGHT_LANDSCAPE / frequency;

    for (int x = 0; x < WIDTH_LANDSCAPE; x++){
        for (int y = 0; y < HEIGHT_LANDSCAPE; y++){
            _points[x][y].set_point(x * 10, y * 10, map.accumulatedNoise2D(x / fx, y / fy, 8, 2.0f, 0.25f) * 100);
        }
    }
}

void Landscape::output_screen_landscape()
{
    for (int i = 0; i < _points.size(); i++){
        for (int j = 0; j < _points[i].size(); j++){
        _screen_points[i][j].output_point();
        }
        std::cout << std::endl;
    }
}

void Landscape::output_landscape()
{
    std::cout << "Размер шума (row): " << _points.size() << std::endl;
    std::cout << "Размер шума (column): " << _points[0].size() << std::endl;
    for (int i = 0; i < _points.size(); i++){
        for (int j = 0; j < _points[i].size(); j++){
        _points[i][j].output_point();
        }
        std::cout << std::endl;
    }
}

void Landscape::draw_landscape(QGraphicsScene *scene)
{
    int row_size = _points.size();
    int column_size = _points[0].size();

    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size ; j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
        }
    }

    row_size = _screen_points.size();
    for (int i = 0; i < row_size; i++)
    {
        int column_size = _screen_points[i].size();
        for (int j = 0; j < column_size; j++)
        {
            if (i < row_size - 1 && j < column_size - 1)
            {
                scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                           _screen_points[i][j+1].get_x(), _screen_points[i][j+1].get_y());
                scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                            _screen_points[i+1][j].get_x(), _screen_points[i+1][j].get_y());
            }
        }
    }
}

void Landscape::rotate_landscape(rotate_t &rotate_angles)
{
    Point<double> center_figure_point;
    Point<double> begin_landscape_point, end_landscape_point;

    begin_landscape_point.set_point(_points[0][0].get_x(),
                                                        _points[0][0].get_y(),
                                                        _points[0][0].get_z());
    end_landscape_point.set_point(_points[_points.size() - 1][_points[0].size() - 1].get_x(),
                                                        _points[_points.size() - 1][_points[0].size() - 1].get_y(),
                                                        _points[_points.size() - 1][_points[0].size() - 1].get_z());

    center_figure_point.set_point((begin_landscape_point.get_x() + end_landscape_point.get_x()) / 2,
                                                (begin_landscape_point.get_y() + end_landscape_point.get_y()) / 2,
                                                (begin_landscape_point.get_z() + end_landscape_point.get_z()) / 2);

    for (int i = 0; i < _points.size(); i++){
        for (int j = 0; j < _points[i].size(); j++){
            shift_point_back_by_center(_points[i][j], center_figure_point);
            rotate_point(_points[i][j], rotate_angles);
            shift_point_back_by_center(_points[i][j], center_figure_point);
        }
    }
}

Point<double> &Landscape::get_point(int index_i, int index_j){
    return _points[index_i][index_j];
}

Point<double> &Landscape::get_screen_point(int index_i, int index_j){
    return _screen_points[index_i][index_j];
}

#endif
