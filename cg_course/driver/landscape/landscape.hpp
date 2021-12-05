#ifndef _LANDSCAPE_HPP_
#define _LANDSCAPE_HPP_

#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.h"

#include "driver/perlin/perlin.hpp"
#include "driver/transform/transform.h"
#include "driver/invisible/zbuffer.h"
#include "driver/light/light.hpp"
#include "driver/geometry/triangle/triangle.hpp"
#include "driver/geometry/vector/vector_3.hpp"

#define WIDTH_LANDSCAPE 5
#define HEIGHT_LANDSCAPE 5

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

    /*std::cout << "point_1_x = " << _points[0][0].get_x() << std::endl;
    std::cout << "point_1_y = " << _points[0][0].get_y() << std::endl;
    std::cout << "point_1_z = " << _points[0][0].get_z() << std::endl;*/
    for (int i = 0; i < row_size; i++)
    {
        for (int j = 0; j < column_size; j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
        }
    }

    /*std::cout << "screen_point_1_x = " << _screen_points[0][0].get_x() << std::endl;
    std::cout << "screen_point_1_y = " << _screen_points[0][0].get_y() << std::endl;*/
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
    qDebug() << "ROTATE_LANDSCAPE\n";
    //std::cout << "ROTATE_LANDSCAPE\n";
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

void Landscape::remove_invisible_lines(ZBuffer &zbuffer, QGraphicsScene *scene, Vector3D<int> light_position)
{
    plane_koeffs_t plane_koeffs_up, plane_koeffs_down;
    std::cout << "light_position = ";
    light_position.output();
    int height_landscape = (*this).get_height(), width_landscape = (*this).get_width();
    //std::cout << "height_landscape = " << height_landscape << std::endl;
    for (int i = 0; i < width_landscape; i++){
        for (int j = 0; j < height_landscape; j++)
        {
            //убрать if в цикл
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
                calculate_equation_plane(plane_koeffs_up,
                                                         (*this).get_point(i, j),
                                                         (*this).get_point(i, j + 1),
                                                         (*this).get_point(i + 1, j + 1));
                calculate_equation_plane(plane_koeffs_down,
                                                         (*this).get_point(i, j),
                                                         (*this).get_point(i + 1, j),
                                                         (*this).get_point(i + 1, j + 1));

                Vector3D<double> normal_up(plane_koeffs_up.a, plane_koeffs_up.b, plane_koeffs_up.c);
                Vector3D<double> normal_down(plane_koeffs_down.a, plane_koeffs_down.b, plane_koeffs_down.c);
                //normal_up.output();
                //normal_down.output();
                normal_up.normalize();
                normal_down.normalize();
                //normal_down.output();

                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_up, plane_koeffs_up, light_position, normal_up);
                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_down, plane_koeffs_down, light_position, normal_down);
            }
        }
    }
    //std::cout << "END!";*/
}

void Landscape::find_all_landscape_normals()
{
    int width_landscape = (*this).get_width(), height_landscape = (*this).get_height();
    for (int i = 0; i < width_landscape - 1; i++)
    {
        std::vector<Vector3D<int>> row_normals_up_triangles;
        std::vector<Vector3D<int>> row_normals_down_triangles;
        for (int j = 0; j < height_landscape - 1; j++)
        {

             Vector3D<int> normal_up_triangle = find_normal<int, double>((*this).get_point(i, j),
                                                                                            (*this).get_point(i, j + 1),
                                                                                            (*this).get_point(i + 1, j + 1));
             Vector3D<int> normal_down_triangle = find_normal<int, double>((*this).get_point(i, j),
                                                                                            (*this).get_point(i + 1, j),
                                                                                            (*this).get_point(i + 1, j + 1));
             row_normals_down_triangles.push_back(normal_down_triangle);
             row_normals_up_triangles.push_back(normal_up_triangle);
        }
        _normals_up_triangles.push_back(row_normals_up_triangles);
        _normals_down_triangles.push_back(row_normals_down_triangles);
    }

}

void Landscape::find_average_normals_of_each_node()
{
    //расчет нормалей в вершинах полигонов
    //случаи:
    //1случай: угловые узлы карты высот (левый верхний и нижний правый - усреднять 2 нормали)
    //2 случай: угловые узлы карты высот (правый верхний и нижний левый - усреднять 1 нормаль)
    //3 случай: все боковые узлы по горизонтали (кроме угловых) - усреднение 3 нормалей
    //4 случай: все боковые узлы по вертикали (кроме угловых) - усреднение 3 нормалей
    //5 случай: все остальные - усреднение 6 нормалей
    qDebug()<< "УЧЕТ НОРМАЛЕЙ.\n";
    int width = (*this).get_width(), height = (*this).get_height();
    qDebug() << "width = " << width << " height = " << height;
    qDebug() << "_normals_up_triangles = " << _normals_up_triangles.size() << " _normals_down_triangles = " << _normals_down_triangles.size();

    //усредненный вектор
    Vector3D<double> average_vector;

    //все усредненные векторы для каждого ряда узлов
    std::vector<Vector3D<double>> row_shading_normals;

    //векторы нормалей для каждого из случаев
    std::vector<Vector3D<int>> normals;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            //1 случай
            if (i == 0 && j == 0 || i == width - 1 && j == height - 1)
            {
                qDebug()<< "Случай 1: " << "i = " << i << " j = " << j;
                if (i == 0){

                    normals.push_back(_normals_down_triangles[i][j]);
                    normals.push_back(_normals_up_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_down_triangles[i - 1][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                normals.clear();
            }
            //2 случай
            else if (i == 0 && j == height - 1 || j == 0 && i == width- 1)
            {
                qDebug()<< "Случай 2: " << "i = " << i << " j = " << j;
                if (i == 0){
                    normals.push_back(_normals_down_triangles[i][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_down_triangles[i - 1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                normals.clear();
            }
            //3 случай
            else if((i == 0 && (j > 0 && j < height - 1)) || (i == width - 1 && (j > 0 && j < height - 1)))
            {
                qDebug()<< "Случай 3: " << "i = " << i << " j = " << j;
                if (i == 0)
                {
                    normals.push_back(_normals_up_triangles[i][j - 1]);
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                normals.clear();
            }
            //4 случай
            else if((j == 0 && i > 0 && i < width - 1) || (j == height - 1 && i > 0 && i < width - 1))
            {
                qDebug()<< "Случай 4: " << "i = " << i << " j = " << j;
                if (j == 0)
                {
                    normals.push_back(_normals_down_triangles[i-1][j]);
                    normals.push_back(_normals_down_triangles[i][j]);
                    normals.push_back(_normals_up_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_down_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_up_triangles[i-1][j - 1]);
                    normals.push_back(_normals_up_triangles[i][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    row_shading_normals.push_back(average_vector);
                }
                normals.clear();
            }
            else
            {
                qDebug()<< "Случай 5: " << "i = " << i << " j = " << j;
                normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                normals.push_back(_normals_up_triangles[i][j]);
                normals.push_back(_normals_up_triangles[i][j-1]);

                normals.push_back(_normals_down_triangles[i - 1][j - 1]);
                normals.push_back(_normals_down_triangles[i - 1][j]);
                normals.push_back(_normals_down_triangles[i][j]);

                average_vector = find_shading_normals(normals, i, j);
                row_shading_normals.push_back(average_vector);
                normals.clear();
            }
        }
        _shading_normals.push_back(row_shading_normals);
        row_shading_normals.clear();
    }
}

void Landscape::output_normals()
{
    int width = _normals_up_triangles.size();
    int height = _normals_down_triangles.size();
    std::cout << "Нормаль верхнего треугольника:\n";
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            _normals_up_triangles[i][j].output();
        }
        std::cout << std::endl;
    }

    std::cout << "Нормаль нижнего треугольника:\n";
    for (int i = 0; i < width; i++){
        for (int j = 0; j < height; j++){
            _normals_down_triangles[i][j].output();
        }
        std::cout << std::endl;
    }
}

void Landscape::output_shading_normals()
{
    int width = _shading_normals.size(), height = 0;
    qDebug() << "width_shading = " << width << "\n";
    std::cout << "Нормали закраски Гуро:\n";
    for (int i = 0; i < width; i++){
        height = _shading_normals.size();
        for (int j = 0; j < height; j++){
            _shading_normals[i][j].output();
        }
        std::cout << std::endl;
    }
}

Vector3D<double> Landscape::find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j)
{
    std::cout << "Случай: i = " << i << " j = " << j << std::endl;
    qDebug() << "Количество нормалей: " << normals.size() << "\n";
    std::cout << "Входные нормали: ";
    int count_normals = normals.size();
    for (int i = 0; i < count_normals; i++){
        normals[i].output();
        std::cout << " ";
    }
    std::cout << std::endl << std::endl;

    Vector3D<int> sum_normal;

    for (int i = 0; i < count_normals; i++){
        sum_normal = sum_normal + normals[i];
    }
    Vector3D<double>average_normal(sum_normal.X(), sum_normal.Y(), sum_normal.Z());

    average_normal /= count_normals;
    return average_normal;
}

#endif
