#ifndef _LANDSCAPE_HPP_
#define _LANDSCAPE_HPP_

#include "driver/geometry/point/point.h"
#include "driver/landscape/landscape.h"
#include "driver/perlin/perlin.hpp"
#include "driver/transform/transform.h"

#define WIDTH_LANDSCAPE 10
#define HEIGHT_LANDSCAPE 10

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
            _points[x][y].set_point(x * 10, y * 10, map.accumulatedNoise2D(x / fx, y / fy, 8, 2.0f, 0.25f));
        }
    }

}

void Landscape::output_landscape()
{
    for (int i = 0; i < _points.size(); i++){
        for (int j = 0; j < 10; j++){
        _screen_points[i][j].output_point();
        }
        std::cout << std::endl;
    }
}

void Landscape::draw_landscape()
{
    for (int i = 0; i < _points.size(); i++){
        for (int j = 0; j < _points.size(); j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
        }
    }
}

#endif
