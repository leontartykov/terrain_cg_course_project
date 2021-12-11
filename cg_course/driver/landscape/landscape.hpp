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
#include "driver/geometry/figure/figure.h"

#define WIDTH_LANDSCAPE 20
#define HEIGHT_LANDSCAPE 20

Landscape::Landscape()
{
    //считаем размер ландшафта - количество тругольников в рядах и столбцах
    _width = HEIGHT_LANDSCAPE + 1, _height = WIDTH_LANDSCAPE + 1;
    //qDebug() << "Landscape_constructor.";
    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _points.push_back(temp);
    }

    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _screen_points.push_back(temp);
    }

    _meta_config.amplitude = 0, _meta_config.exponent = 0, _meta_config.frequency = 0;
    _meta_config.frequency_x = 0, _meta_config.frequency_y = 0, _meta_config.gain = 0;
    _meta_config.lacunarity = 0, _meta_config.octaves = 0;

    for (int i = 0; i < 4; i++){
        _base_screen.push_back(Point<int>(0, 0, 0));
    }
}

Landscape::Landscape(int width, int height)
{
    _width = height + 1, _height = width + 1;
    //qDebug() << "Landscape_constructor.";
    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _points.push_back(temp);
    }

    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _screen_points.push_back(temp);
    }

    _meta_config.amplitude = 0, _meta_config.exponent = 0, _meta_config.frequency = 0;
    _meta_config.frequency_x = 0, _meta_config.frequency_y = 0, _meta_config.gain = 0;
    _meta_config.lacunarity = 0, _meta_config.octaves = 0;
}

Landscape::~Landscape(){
}

void Landscape::form_landscape()
{
    perlin::Perlin map(1532512342);
    double frequency = _meta_config.frequency;
    double frequency_x = _meta_config.frequency_x, frequency_y = _meta_config.frequency_y;
    double fx = _width / frequency;
    double fy = _height / frequency;

    for (int x = 0; x < _width; x++){
        for (int y = 0; y < _height; y++){
            _points[x][y].set_point((x+1) * 10, (y+1) * 10, map.accumulatedNoise2D(x / fx, y / fy, _meta_config)*1000);
        }
    }

    //std::cout << "Угловые точки шума:" << std::endl;
    _base_points.push_back(Point<double>(_points[0][0].get_x(), _points[0][0].get_y(), _points[0][0].get_z() * 2));
    _base_points.push_back(Point<double>(_points[_width - 1][0].get_x(), _points[_width - 1][0].get_y(), _points[_width - 1][0].get_z() * 2));
    _base_points.push_back(Point<double>(_points[_width - 1][_height - 1].get_x(), _points[_width - 1][_height - 1].get_y(), _points[_width - 1][_height - 1].get_z() * 2));
    _base_points.push_back(Point<double>(_points[0][_height - 1].get_x(), _points[0][_height - 1].get_y(), _points[0][_height - 1].get_z() * 2));
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
    std::cout << "Размер шума (row): " << _width << std::endl;
    std::cout << "Размер шума (column): " << _height << std::endl;
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
        _points[i][j].output_point();
        }
        std::cout << std::endl;
    }
}

void Landscape::transform_points_to_screen()
{
    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++){
            transform_3d_into_2d(_screen_points[i][j], _points[i][j]);
            _screen_points[i][j].set_z(_points[i][j].get_z());
        }
    }

    /*for (int i = 0; i < _base_points.size(); i++){
        transform_3d_into_2d(_base_screen[i], _base_points[i]);
    }*/

    _base_screen[0].set_point(_screen_points[0][0].get_x(), _screen_points[0][0].get_y() + 50, 0);
    _base_screen[1].set_point(_screen_points[_width - 1][0].get_x(), _screen_points[_width - 1][0].get_y() + 50, 0);
    _base_screen[2].set_point(_screen_points[_width - 1][_height - 1].get_x(), _screen_points[_width - 1][_height - 1].get_y() + 50, 0);
    _base_screen[3].set_point(_screen_points[0][_height - 1].get_x(), _screen_points[0][_height - 1].get_y() + 50, 0);
}

void Landscape::draw_landscape(ZBuffer &zbuffer, QGraphicsScene *scene, QImage *image)
{
    //scene->addLine(0,0,0,0);
    //qDebug() << "width = " << width;
    //zbuffer.output();

    // обычный вывод сетки

    /*scene->clear();
    int x = 0, y = 0;
    double z = 0;
    int row_size = _width;
    for (int i = 0; i < row_size; i++)
    {
        int column_size = _height;
        for (int j = 0; j < column_size; j++)
        {
            if (i < row_size - 1 && j < column_size - 1)
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



    //image.get()->setPixel();
    QPixmap pixmap(SCREEN_WIDTH, SCREEN_HEIGHT);
    pixmap.fill(Qt::white);
    QPainter painter(&pixmap);

    std::vector<std::vector<QColor>> colors = zbuffer.get_color_matrix();
    int r = 0, g = 0, b = 0;
    colors[0][0].getRgb(&r, &g, &b);

    for (int i = 0; i < SCREEN_WIDTH; i++){
        for (int j = 0; j < SCREEN_HEIGHT; j++)
        {
            colors[i][j].getRgb(&r, &g, &b);

            painter.setPen(QColor(r, g, b));
            painter.drawLine(i, j, i, j);
        }
    }

    //pixmap.convertFromImage();
    scene->clear();
    scene->addPixmap(pixmap.scaled(QSize(SCREEN_WIDTH, SCREEN_HEIGHT)));
}

void Landscape::rotate_landscape(rotate_t &diff_rotate_angles)
{
    //qDebug() << "ROTATE_LANDSCAPE\n";
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
    /*begin_landscape_point.output_point();
    end_landscape_point.output_point();*/

    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            shift_point_by_center(_points[i][j], center_figure_point);
            rotate_point(_points[i][j], diff_rotate_angles);
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
    return _height;
}

int Landscape::get_width(){
    return _width;
}

void Landscape::remove_invisible_lines(ZBuffer &zbuffer, QGraphicsScene *scene, Vector3D<int> light_position)
{
    plane_koeffs_t plane_koeffs_up, plane_koeffs_down;

    //все точки экранных треугольников (верхние, нижние)
    //берем тройную матрицу для того, чтобы поделить на верхнюю часть треугольника
    //и нижнюю
    std::vector<std::vector<rasterised_points_t>> rasterized_points_up, rasterized_points_down;

    //нормали для треугольников (верхние, нижние)
    Vector3D<double> normal_up, normal_down;

    //нормали вершин для каждого треугольника (верхние, нижние)
    Triangle<double>triangle_up_normals, triangle_down_normals;

    //вершины треугольников (верхний и нижний) в 3д
    Triangle<double>triangle_up_3d, triangle_down_3d;

    Point<int> middle_point_up, middle_point_down;

    for (int i = 0; i < _width - 1; i++){
        for (int j = 0; j < _height - 1; j++)
        {
            //std::cout << "i = " << i << " j = " << j << std::endl;
            //qDebug() << "i = " << i << " j = " << j;
            calculate_equation_plane(plane_koeffs_up, _points[i][j], _points[i][j+1], _points[i + 1][j + 1]);
            calculate_equation_plane(plane_koeffs_down, _points[i][j], _points[i+1][j], _points[i + 1][j + 1]);

            triangle_up_normals.set_triangle(_shading_normals[i][j], _shading_normals[i][j+1], _shading_normals[i+1][j+1]);
            triangle_down_normals.set_triangle(_shading_normals[i][j], _shading_normals[i+1][j], _shading_normals[i+1][j+1]);

            /*std::cout << "triangles_up_shadinag_normals";
            triangle_up_normals.output();

            std::cout << "triangles_down_shadinag_normals";
            triangle_down_normals.output();*/

            middle_point_up = rasterize_triangle(rasterized_points_up, triangle_up_normals, light_position,
                                         _screen_points[i][j], _screen_points[i][j+1], _screen_points[i + 1][j + 1],
                                         scene, zbuffer.get_color_matrix(), plane_koeffs_up);

            middle_point_down = rasterize_triangle(rasterized_points_down, triangle_down_normals, light_position,
                                         _screen_points[i][j], _screen_points[i+1][j], _screen_points[i + 1][j + 1],
                                        scene, zbuffer.get_color_matrix(), plane_koeffs_down);

            calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                 rasterized_points_up, plane_koeffs_up, light_position, triangle_up_normals,
                                                 triangle_up_3d);
            calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                 rasterized_points_down, plane_koeffs_down, light_position, triangle_down_normals,
                                                 triangle_down_3d);

            rasterized_points_up.clear(), rasterized_points_down.clear();
        }
    }
}

void Landscape::find_all_landscape_normals()
{
    std::vector<Vector3D<int>> row_normals_up_triangles;
    std::vector<Vector3D<int>> row_normals_down_triangles;
    for (int i = 0; i < _width - 1; i++)
    {
        for (int j = 0; j < _height - 1; j++)
        {
             //qDebug() << "i = " << i << " j = " << j;
             //std::cout << "Верхний треугольник: ";
             Vector3D<int> normal_up_triangle = find_normal<int, double>(_points[i][j],
                                                                                            _points[i][j+1],
                                                                                            _points[i+1][j+1]);

             //std::cout << "Нижний треугольник: ";
             Vector3D<int> normal_down_triangle = find_normal<int, double>(_points[i][j],
                                                                                            _points[i+1][j],
                                                                                            _points[i+1][j+1]);
             //std::cout << std::endl;
             row_normals_up_triangles.push_back(normal_up_triangle);
             row_normals_down_triangles.push_back(normal_down_triangle);
        }
        _normals_up_triangles.push_back(row_normals_up_triangles);
        _normals_down_triangles.push_back(row_normals_down_triangles);
        row_normals_up_triangles.clear();
        row_normals_down_triangles.clear();
    }
}

/*void Landscape::find_base_normals()
{

}*/

void Landscape::find_average_normals_of_each_node()
{
    //расчет нормалей в вершинах полигонов
    //случаи:
    //1случай: угловые узлы карты высот (левый верхний и нижний правый - усреднять 2 нормали)
    //2 случай: угловые узлы карты высот (правый верхний и нижний левый - усреднять 1 нормаль)
    //3 случай: все боковые узлы по горизонтали (кроме угловых) - усреднение 3 нормалей
    //4 случай: все боковые узлы по вертикали (кроме угловых) - усреднение 3 нормалей
    //5 случай: все остальные - усреднение 6 нормалей

    //qDebug() << "width = " << width << " height = " << height;
    //qDebug() << "_normals_up_triangles = " << _normals_up_triangles.size() << " _normals_down_triangles = " << _normals_down_triangles.size();

    //усредненный вектор
    Vector3D<double> average_vector;

    //все усредненные векторы для каждого ряда узлов
    std::vector<Vector3D<double>> row_shading_normals;

    //векторы нормалей для каждого из случаев
    std::vector<Vector3D<int>> normals;

    //std::cout << "width = " << _width << " height = " << _height << std::endl;

    for (int i = 0; i < _width; i++)
    {
        for (int j = 0; j < _height; j++)
        {
            //1 случай
            if ((i == 0 && j == 0) || (i == _width - 1 && j == _height - 1))
            {
                //qDebug()<< "Случай 1: " << "i = " << i << " j = " << j;
                if (i == 0){

                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                    normals.push_back(_normals_down_triangles[i - 1][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //2 случай
            else if ((i == 0 && j == _height - 1) || (j == 0 && i == _width- 1))
            {
                //qDebug()<< "Случай 2: " << "i = " << i << " j = " << j;
                if (i == 0){
                    normals.push_back(_normals_up_triangles[i][j - 1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else{
                    normals.push_back(_normals_down_triangles[i - 1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //3 случай
            else if((i == 0 && j > 0 && j < _height - 1) || (i == _width - 1 && j > 0 && j < _height - 1))
            {
                //qDebug()<< "Случай 3: " << "i = " << i << " j = " << j;
                if (i == 0)
                {
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_up_triangles[i][j - 1]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i - 1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            //4 случай
            else if((j == 0 && i > 0 && i < _width - 1) || (j == _height - 1 && i > 0 && i < _width - 1))
            {
                //qDebug()<< "Случай 4: " << "i = " << i << " j = " << j;
                if (j == 0)
                {
                    normals.push_back(_normals_down_triangles[i-1][j]);
                    normals.push_back(_normals_up_triangles[i][j]);
                    normals.push_back(_normals_down_triangles[i][j]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
                else
                {
                    normals.push_back(_normals_up_triangles[i-1][j - 1]);
                    normals.push_back(_normals_up_triangles[i][j-1]);
                    normals.push_back(_normals_down_triangles[i-1][j-1]);

                    average_vector = find_shading_normals(normals, i, j);
                    average_vector.normalize();
                    row_shading_normals.push_back(average_vector);
                }
            }
            else
            {
                //qDebug()<< "Случай 5: " << "i = " << i << " j = " << j;
                normals.push_back(_normals_up_triangles[i - 1][j - 1]);
                normals.push_back(_normals_up_triangles[i][j]);
                normals.push_back(_normals_up_triangles[i][j-1]);

                normals.push_back(_normals_down_triangles[i - 1][j - 1]);
                normals.push_back(_normals_down_triangles[i-1][j]);
                normals.push_back(_normals_down_triangles[i][j]);

                average_vector = find_shading_normals(normals, i, j);
                average_vector.normalize();
                row_shading_normals.push_back(average_vector);
            }
            normals.clear();
        }
        _shading_normals.push_back(row_shading_normals);
        row_shading_normals.clear();
    }
}

void Landscape::output_normals()
{
    std::cout << "Нормаль верхнего треугольника:\n";
    for (int i = 0; i < _width - 1; i++){
        for (int j = 0; j < _height - 1; j++){
            _normals_up_triangles[i][j].output();
        }
        std::cout << std::endl;
    }

    std::cout << "Нормаль нижнего треугольника:\n";
    for (int i = 0; i < _width - 1; i++){
        for (int j = 0; j < _height - 1; j++){
            _normals_down_triangles[i][j].output();
        }
        std::cout << std::endl;
    }
}

void Landscape::output_shading_normals()
{
    for (int i = 0; i < _width; i++){
        for (int j = 0; j < _height; j++){
            _shading_normals[i][j].output();
        }
        std::cout << std::endl;
    }
}

Vector3D<double> Landscape::find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j)
{
    //std::cout << "Случай: i = " << i << " j = " << j << std::endl;
    //qDebug() << "Количество нормалей: " << normals.size();
    //std::cout << "Входные нормали: ";
    int count_normals = normals.size();
    /*for (int i = 0; i < count_normals; i++){
        normals[i].output();
        std::cout << " ";
    }
    std::cout << std::endl << std::endl;*/

    Vector3D<int> sum_normal;

    for (int i = 0; i < count_normals; i++){
        sum_normal = sum_normal + normals[i];
    }
    Vector3D<double>average_normal(sum_normal.X(), sum_normal.Y(), sum_normal.Z());

    average_normal /= count_normals;
    return average_normal;
}

rotate_t Landscape::get_rotate_angles(){
    return _rotate_landscape_angles;
}

void Landscape::set_rotate_angles(int angle_x, int angle_y, int angle_z)
{
    _rotate_landscape_angles.angle_x = angle_x;
    _rotate_landscape_angles.angle_y = angle_y;
    _rotate_landscape_angles.angle_z = angle_z;
}

void Landscape::set_meta_config(int octaves, double amplitude, double frequency,
                                  double exponent, int frequency_x, int frequency_y,
                                  double gain, double lacunarity)
{
    _meta_config.octaves = octaves;
    _meta_config.amplitude = amplitude;
    _meta_config.frequency = frequency;
    _meta_config.exponent = exponent;
    _meta_config.frequency_x = frequency_x;
    _meta_config.frequency_y = frequency_y;
    _meta_config.gain = gain;
    _meta_config.lacunarity = lacunarity;
}

void Landscape::output_rotate_angles()
{
    qDebug() << "x :" << _rotate_landscape_angles.angle_x;
    qDebug() << " y :" << _rotate_landscape_angles.angle_y;
    qDebug() << " z :" << _rotate_landscape_angles.angle_z;
}

int Landscape::get_rotate_x(){
    return _rotate_landscape_angles.angle_x;
}

int Landscape::get_rotate_y(){
    return _rotate_landscape_angles.angle_y;
}

int Landscape::get_rotate_z(){
    return _rotate_landscape_angles.angle_z;
}

void Landscape::set_meta_data(meta_data_t meta_data){
    _meta_config = meta_data;
}

void Landscape::clear()
{
    for (int i = 0; i < _width; i++){
         _points[i].clear();
    }
    _points.clear();

    for (int i = 0; i < _width; i++){
        _screen_points[i].clear();
    }
    _screen_points.clear();

    _meta_config.amplitude = 0, _meta_config.exponent = 0, _meta_config.frequency = 0;
    _meta_config.frequency_x = 0, _meta_config.frequency_y = 0, _meta_config.gain = 0;
    _meta_config.lacunarity = 0, _meta_config.octaves = 0;

    int width_landscape = (*this).get_width(), height_landscape = (*this).get_height();
    for (int i = 0; i < width_landscape - 1; i++)
    {
        _normals_up_triangles[i].clear();
        _normals_down_triangles[i].clear();
        _shading_normals[i].clear();
    }
    _normals_up_triangles.clear();
    _normals_down_triangles.clear();
    _shading_normals.clear();
}

void Landscape::change_size(int width, int height)
{
    //qDebug() << "change_size";
    //qDebug() << "width = " << width << " height = " << height;
    //qDebug() << "_points.size() = " << _points.size();
    _width = height + 1; _height = width + 1;
    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _points.push_back(temp);
    }

    for (int i = 0; i < _width; i++)
    {
        std::vector<Point<double>> temp;
        for (int j = 0; j < _height; j++){
            temp.push_back(Point<double>(0, 0, 0));
        }
        _screen_points.push_back(temp);
    }

    _meta_config.amplitude = 0, _meta_config.exponent = 0, _meta_config.frequency = 0;
    _meta_config.frequency_x = 0, _meta_config.frequency_y = 0, _meta_config.gain = 0;
    _meta_config.lacunarity = 0, _meta_config.octaves = 0;
}

void Landscape::resize(int width, int height){
}

void Landscape::find_base_normals()
{
     //Vector3D<int> normal_edge_1 = find_normal(_base);
}

void Landscape::make_base(ZBuffer &zbuffer, QGraphicsScene *scene)
{
    std::vector<rasterised_points_t> edge_1, edge_2, edge_3, edge_4;
    Point<int> point_1, point_2, point_3, point_4;
    point_1.set_point(_base_screen[0].get_x(), _base_screen[0].get_y(), _base_screen[0].get_z());
    point_2.set_point(_base_screen[1].get_x(), _base_screen[1].get_y(), _base_screen[1].get_z());
    point_3.set_point(_base_screen[2].get_x(), _base_screen[2].get_y(), _base_screen[2].get_z());
    point_4.set_point(_base_screen[3].get_x(), _base_screen[3].get_y(), _base_screen[3].get_z());

    create_line_by_int_brezenhem(edge_1, point_1, point_2, scene);
    create_line_by_int_brezenhem(edge_2, point_2, point_3, scene);
    create_line_by_int_brezenhem(edge_3, point_3, point_4, scene);
    create_line_by_int_brezenhem(edge_4, point_4, point_1, scene);

    (this)->fill_base(zbuffer, edge_1);
    (this)->fill_base(zbuffer, edge_2);
    (this)->fill_base(zbuffer, edge_3);
    (this)->fill_base(zbuffer, edge_4);
}

void Landscape::fill_base(ZBuffer &zbuffer, std::vector<rasterised_points_t> &edge)
{
    int rasterize_x = 0, rasterize_y = 0;
    for (int i = 0; i < edge.size(); i++){
        rasterize_x = edge[i].point.X();
        rasterize_y = edge[i].point.Y();
        if (zbuffer.is_background(rasterize_x, rasterize_y) == true){
            zbuffer.set_color(rasterize_x, rasterize_y, qRgb(0, 0, 0));
        }

        for (int y = rasterize_y - 1; zbuffer.is_background(rasterize_x, y) == true; y--){
            zbuffer.set_color(rasterize_x, y, qRgb(128, 128, 128));
        }
    }
}

void Landscape::clear_normals()
{
    int width_landscape = (*this).get_width(), height_landscape = (*this).get_height();
    for (int i = 0; i < width_landscape - 1; i++)
    {
        _normals_up_triangles[i].clear();
        _normals_down_triangles[i].clear();
        _shading_normals[i].clear();
    }
    _normals_up_triangles.clear();
    _normals_down_triangles.clear();
    _shading_normals.clear();
}

#endif
