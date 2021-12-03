#ifndef _LANDSCAPE_HPP_
#define _LANDSCAPE_HPP_

#include "driver/geometry/point/point.h"
#include "driver/landscape/landscape.h"
#include "driver/perlin/perlin.hpp"
#include "driver/transform/transform.h"
#include "driver/invisible/zbuffer.h"
#include "driver/light/light.hpp"

#define WIDTH_LANDSCAPE 25
#define HEIGHT_LANDSCAPE 25

Landscape::Landscape()
{
    for (int i = 0; i < WIDTH_LANDSCAPE; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < HEIGHT_LANDSCAPE; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _points.push_back(temp);
    }

    for (int i = 0; i < WIDTH_LANDSCAPE; i++)
    {
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
            _points[x][y].set_point((x+10) * 20, (y+5) * 20, map.accumulatedNoise2D(x / fx, y / fy, 8, 2.0f, 0.25f) * 300);
        }
    }

    std::cout << "begin =";
    _points[0][0].output_point();
    std::cout << "end =";
    _points[WIDTH_LANDSCAPE - 1][HEIGHT_LANDSCAPE - 1].output_point();

    //(*this).output_landscape();
}

void Landscape::output_screen_landscape()
{
    for (int i = 0; i < _screen_points.size(); i++){
        for (int j = 0; j < _screen_points[i].size(); j++){
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

void Landscape::transform_points_to_screen()
{
    int row_size = _points.size();
    int column_size = _points[0].size();

    std::cout << "point_1_x = " << _points[0][0].get_x() << std::endl;
    std::cout << "point_1_y = " << _points[0][0].get_y() << std::endl;
    std::cout << "point_1_z = " << _points[0][0].get_z() << std::endl;
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
        }
    }

    std::cout << "screen_point_1_x = " << _screen_points[0][0].get_x() << std::endl;
    std::cout << "screen_point_1_y = " << _screen_points[0][0].get_y() << std::endl;
    //(*this).output_screen_landscape();
}

void Landscape::draw_landscape(ZBuffer &zbuffer, QGraphicsScene *scene, QImage *image)
{
    //zbuffer.output();

    // обычный вывод сетки
    /*
    int x = 0, y = 0;
    double z = 0;
    int row_size = _points.size();
    for (int i = 0; i < row_size; i++)
    {
        int column_size = _points[i].size();
        for (int j = 0; j < column_size; j++)
        {
            if (i <= 5 && j==0/*i < row_size - 1 && j < column_size - 1*//*)
            {
                    scene->addLine(_screen_points[i+1][j].get_x(), _screen_points[i+1][j].get_y(),
                                               _screen_points[i + 1][j+1].get_x(), _screen_points[i+1][j+1].get_y());
                    scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                                _screen_points[i+1][j].get_x(), _screen_points[i+1][j].get_y());
                    scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                               _screen_points[i+1][j+1].get_x(), _screen_points[i+1][j+1].get_y());
                    scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                               _screen_points[i][j+1].get_x(), _screen_points[i][j+1].get_y());
                    scene->addLine(_screen_points[i][j+1].get_x(), _screen_points[i][j+1].get_y(),
                                               _screen_points[i+1][j+1].get_x(), _screen_points[i+1][j+1].get_y());
                    scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                               _screen_points[i+1][j+1].get_x(), _screen_points[i+1][j+1].get_y());
            }
        }
    }*/

    /*row_size = zbuffer.get_color_matrix().size(), column_size  = zbuffer.get_color_matrix()[0].size();
    std::cout << "row_size = " << row_size << std::endl;
    std::cout << "column_size = " << column_size << std::endl;*/

    /*
    for (int i = 0; i < WIDTH_LANDSCAPE; i++){
        for (int j = 0; j < HEIGHT_LANDSCAPE; j++){
            scene->addLine(_screen_points[i][j].get_x(), _screen_points[i][j].get_y(),
                                       _screen_points[i][j].get_x(), _screen_points[i][j].get_y());
        }
    }*/



    QPixmap pixmap;
    QPainter painter;
    painter.begin(image);

    std::vector<std::vector<QColor>> colors = zbuffer.get_color_matrix();
    int r = 0, g = 0, b = 0;
    colors[0][0].getRgb(&r, &g, &b);
    //std::cout << "r = " << r << " g = " << g << " b = " << b;
    //colors[0][0].setRgb(50, 50, 50);
    //std::cout << "r = " << r << " g = " << g << " b = " << b;

    for (int i = 0; i < 1024; i++){
        for (int j = 0; j < 756; j++)
        {
            colors[i][j].getRgb(&r, &g, &b);
            //std::cout << "r = " << r << "g = " << g << "b = " << b << std::endl;
            painter.setPen(QColor(r, g, b));
            painter.drawLine(i, j, i, j);
        }
    }

    pixmap.convertFromImage(*image);
    scene->addPixmap(pixmap);
    painter.end();
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
    begin_landscape_point.output_point();
    end_landscape_point.output_point();

    for (int i = 0; i < WIDTH_LANDSCAPE; i++){
        for (int j = 0; j < HEIGHT_LANDSCAPE; j++){
            shift_point_by_center(_points[i][j], center_figure_point);
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

int Landscape::get_height(){
    return _points.size();
}

int Landscape::get_width(){
    return _points[0].size();
}

void Landscape::remove_invisible_lines(ZBuffer &zbuffer, QGraphicsScene *scene, Vector3D light_position)
{
    plane_koeffs_t plane_koeffs_up, plane_koeffs_down;
    //std::cout << "light_position = ";
    //light_position.output();
    int height_landscape = (*this).get_height(), width_landscape = (*this).get_width();
    //std::cout << "height_landscape = " << height_landscape << std::endl;
    for (int i = 0; i < width_landscape; i++){
        for (int j = 0; j < height_landscape; j++)
        {
            if (/*i <= 5 && j<=1*/i < height_landscape - 1 && j < width_landscape - 1)
            {
                 std::vector<std::vector<Vector2D>> rasterized_points_up;
                 std::vector<std::vector<Vector2D>> rasterized_points_down;
                 rasterize_triangle(rasterized_points_up, (*this).get_screen_point(i, j),
                                                                                 (*this).get_screen_point(i, j + 1),
                                                                                 (*this).get_screen_point(i + 1, j + 1), scene,
                                              zbuffer.get_color_matrix());
                 rasterize_triangle(rasterized_points_down, (*this).get_screen_point(i, j),
                                                                                 (*this).get_screen_point(i + 1, j),
                                                                                 (*this).get_screen_point(i + 1, j + 1), scene,
                                                zbuffer.get_color_matrix());
                //std::cout << "End_rasterize!" << std::endl;
                 /*std::cout << "rasterized_points_up";
                 for (int i = 0; i < rasterized_points_up.size(); i++){
                     for (int j = 0; j < rasterized_points_up[i].size(); j++){
                         rasterized_points_up[i][j].output_point();
                     }
                     std::cout << std::endl;
                 }*/

                 /*std::cout << "rasterized_points_down";
                 for (int i = 0; i < rasterized_points_up.size(); i++){
                     for (int j = 0; j < rasterized_points_up[i].size(); j++){
                         rasterized_points_up[i][j].output_point();
                     }
                     std::cout << std::endl;
                 }*/
                //std::cout << "rasterized_points_up.size() = " << rasterized_points_up.size() << std::endl;
                //QPen *pen = new QPen(Qt::red);
                //scene->addLine(302, 349, 302, 349, *pen);
                /*scene->addLine(331, 359, 331, 359, *pen);
                scene->addLine(290, 361, 290, 361, *pen);*/


                calculate_equation_plane(plane_koeffs_up,
                                                         (*this).get_point(i, j),
                                                         (*this).get_point(i, j + 1),
                                                         (*this).get_point(i + 1, j + 1));
                calculate_equation_plane(plane_koeffs_down,
                                                         (*this).get_point(i, j),
                                                         (*this).get_point(i + 1, j),
                                                         (*this).get_point(i + 1, j + 1));
                Vector3D normal_up(plane_koeffs_up.a, plane_koeffs_up.b, plane_koeffs_up.c);
                Vector3D normal_down(plane_koeffs_down.a, plane_koeffs_down.b, plane_koeffs_down.c);
                normal_up.normalize();
                normal_down.normalize();

                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_up, plane_koeffs_up, light_position, normal_up);
                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_down, plane_koeffs_down, light_position, normal_down);
            }
        }
    }
    //std::cout << "END!";*/
}


#endif
