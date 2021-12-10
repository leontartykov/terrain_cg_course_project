#include <math.h>
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/figure/figure.h"
#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.hpp"
#include "driver/transform/transform.h"
#include "driver/geometry/vector/vector.h"
#include "driver/geometry/vector/vector_2.hpp"
#include "driver/geometry/vector/vector_3.hpp"
#include "driver/geometry/triangle/triangle.hpp"


double find_max_point(double value_1, double value_2, double value_3);
void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<int> &min_point);
void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<int> &max_point);
void find_middle_point(Point<int> &middle_point, Point<int> &min_point, Point<int> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3);

double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double zbuffer_value);
int sign(int x);
void create_line_by_int_brezenhem(std::vector<std::vector<rasterised_points_t>> &edge,
                                                         Point<int> start_point, Point <int> end_point, QGraphicsScene *scene,
                                                        Vector3D<double> normal_start, Vector3D<double> normal_end,
                                                            Vector3D<int> &light_position, plane_koeffs_t &plane_koeffs);
void output_edge(std::vector<edge_t> &edge);

void swap_values(int &value_1, int &value_2);
void swap_points(Point<int> &point_triangle_1, Point<int> &point_triangle_2);
void swap_rasterised_points(rasterised_points_t &value_1, rasterised_points_t &value_2);



Point<int> rasterize_triangle(std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                    Triangle<double>&triangle_normals,
                                    Vector3D<int> &light_position, Point<double> &point_1, Point<double> &point_2, Point<double> &point_3,
                                    QGraphicsScene *scene, std::vector<std::vector<QColor>> &colors)
{
    /*std::cout << std::endl << "Треугольник: point_1: ";
    point_1.output_point();
    std::cout << " " << "point_2: ";
    point_2.output_point();
    std::cout << " " << "point_3: ";
    point_3.output_point();*/
    plane_koeffs_t plane_koeffs;
    calculate_equation_plane(plane_koeffs, point_1, point_2, point_3);
    std::vector<std::vector<rasterised_points_t>> rasterized_points_up, rasterized_points_down;

    //преобразование в целочисленные точки
    Point<int> point_triangle_1, point_triangle_2, point_triangle_3;
    point_triangle_1.set_point(point_1.get_x(), point_1.get_y(), point_1.get_z());
    point_triangle_2.set_point(point_2.get_x(), point_2.get_y(), point_2.get_z());
    point_triangle_3.set_point(point_3.get_x(), point_3.get_y(), point_3.get_z());

    //определение целочисленным брезенхемом границ треугольника
    int min_mode = 1, max_mode = 2;
    std::vector<std::vector<rasterised_points_t>> edge_1, edge_2, edge_3;

    //вычисление min, middle, max точек треугольника
    Point<int> min_point, max_point, middle_point;
    if (point_triangle_2.get_y() < point_triangle_1.get_y()){
        swap_points(point_triangle_1, point_triangle_2);
        triangle_normals.swap_points(1, 2);
    }

    if (point_triangle_3.get_y() < point_triangle_1.get_y()){
        swap_points(point_triangle_1, point_triangle_3);
        triangle_normals.swap_points(1, 3);
    }

    if (point_triangle_2.get_y() > point_triangle_3.get_y()){
        swap_points(point_triangle_2, point_triangle_3);
        triangle_normals.swap_points(2, 3);
    }

    min_point.set_point(point_triangle_1.get_x(), point_triangle_1.get_y(), 0);
    middle_point.set_point(point_triangle_2.get_x(), point_triangle_2.get_y(), 0);
    max_point.set_point(point_triangle_3.get_x(), point_triangle_3.get_y(), 0);

    /*std::cout << "min_point = "; min_point.output_point();
    std::cout << "middle_point = "; middle_point.output_point();
    std::cout << "max_point = "; max_point.output_point();*/

    //вычисление координат пикселей ребер треугольника
    //qDebug() << "edge_1";
    create_line_by_int_brezenhem(edge_1, min_point, middle_point, scene, triangle_normals[0], triangle_normals[1], light_position, plane_koeffs);
    //qDebug() << "edge_2";
    create_line_by_int_brezenhem(edge_2, min_point, max_point, scene, triangle_normals[0], triangle_normals[2], light_position, plane_koeffs);
    //qDebug() << "edge_3";
    create_line_by_int_brezenhem(edge_3, middle_point, max_point, scene, triangle_normals[1], triangle_normals[2], light_position, plane_koeffs);

    //qDebug() << "Растеризация треугольника.";
    //непосредственно растеризация - сканирующие строки
    int edge_1_size = edge_1.size(), edge_2_size = edge_2.size(), edge_3_size = edge_3.size();
    //растеризованные точки в ряду
    std::vector<rasterised_points_t> temp_points;
    //для интерполяции
    double t = 0, intensity = 0;
    //если серединная вершина треугольника лежит левее максимальной
    if (middle_point.get_x() <= max_point.get_x())
    {
        //qDebug() << "middle_point_x < max point_x";
        int edge_1_i_size, edge_2_i_size, edge_3_i_size;
        //нахождение min и max по "х" пикселя для одинакового "у"  (верхняя часть треугольника)
        for (int i = 0; i < edge_1_size; i++)
        {
            edge_1_i_size = edge_1[i].size();
            edge_2_i_size = edge_2[i].size();

            rasterised_points_t x_left = edge_1[i][edge_1_i_size - 1], x_right = edge_2[i][edge_2_i_size - 1];
            if (x_left.point.X() > x_right.point.X()){
                swap_rasterised_points(x_left, x_right);
            }

            //qDebug() << "x_left_intensity = " <<
            double x_left_value = x_left.point.X(), x_right_value = x_right.point.X();
            double I_left = x_left.intensity, I_right = x_right.intensity;
            for (int y = edge_1[i][0].point.Y(), x = x_left_value; x <= x_right_value; x++)
            {
                //qDebug() << "x_left_value - x = " << x_left_value - x;
                if (fabs(x_left_value - x) == 0){
                    t = 0;
                }
                else{
                    t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                }
                intensity = (1 - t) * I_left + t * I_right;
                //qDebug() << "xleft = " << x_left_value << " x = " << x << " x_right = " << x_right_value << "y = " << y << " t = " << t << " I_left = " << I_left << " I_right = " << I_right << " I_current = " << intensity;
                rasterised_points_t point;
                point.point = Vector2D(x, y);
                point.intensity = intensity;
                temp_points.push_back(point);
                //scene->addLine(x, y, x, y);
            }
            rasterized_points.push_back(temp_points);
            temp_points.clear();
        }

        //нахождение min и max по "х" пикселя для одинакового "у"  (нижняя часть треугольника)
        for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
        {
            edge_2_i_size = edge_2[edge_2_size - 1 - j].size();
            rasterised_points_t x_left = edge_3[i][0], x_right = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1];

            if (x_left.point.X() > x_right.point.X()){
                swap_rasterised_points(x_left, x_right);
            }

            double x_left_value = x_left.point.X(), x_right_value = x_right.point.X();
            double I_left = x_left.intensity, I_right = x_right.intensity;
            for (int y = edge_3[i][0].point.Y(), x = x_left_value; x <= x_right_value; x++)
            {
                //qDebug() << "x_left_value - x = " << x_left_value - x;
                if (fabs(x_left_value - x) == 0){
                    t = 0;
                }
                else{
                    t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                }
                intensity = (1 - t) * I_left + t * I_right;
                //qDebug() << "xleft = " << x_left_value << " x = " << x << " x_right = " << x_right_value << "y = " << y << " t = " << t << " I_left = " << I_left << " I_right = " << I_right << " I_current = " << intensity;
                rasterised_points_t point;
                point.point = Vector2D(x, y);
                point.intensity = intensity;
                temp_points.push_back(point);
                //scene->addLine(x, y, x, y);
            }
            rasterized_points.push_back(temp_points);
            temp_points.clear();
        }
    }
    else
    {
        //qDebug() << "middle_point_x > max point_x";
        int edge_1_i_size, edge_2_i_size, edge_3_i_size;
        for (int i = 0; i < edge_1_size; i++)
        {
            edge_1_i_size = edge_1[i].size();

            rasterised_points_t x_left = edge_2[i][0], x_right = edge_1[i][edge_1_i_size - 1];

            if (x_left.point.X() > x_right.point.X()){
                swap_rasterised_points(x_left, x_right);
            }
            double x_left_value = x_left.point.X(), x_right_value = x_right.point.X();
            double I_left = x_left.intensity, I_right = x_right.intensity;
            for (int x = x_left_value, y = edge_2[i][0].point.Y(); x <= x_right_value; x++)
            {
                //qDebug() << "x_left_value - x = " << x_left_value - x;
                if (fabs(x_left_value - x) == 0){
                    t = 0;
                }
                else{
                    t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                }
                intensity = (1 - t) * I_left + t * I_right;
                //qDebug() << "xleft = " << x_left_value << " x = " << x << " x_right = " << x_right_value << "y = " << y << " t = " << t << " I_left = " << I_left << " I_right = " << I_right << " I_current = " << intensity;
                rasterised_points_t point;
                point.point = Vector2D(x, y);
                point.intensity = intensity;
                temp_points.push_back(point);
                //scene->addLine(x, y, x, y);
            }
            rasterized_points.push_back(temp_points);
            temp_points.clear();
        }

        for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
        {
            edge_3_i_size = edge_3[i].size();
            edge_2_i_size = edge_2[edge_2_size - 1 - j].size();

            rasterised_points_t x_left = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1], x_right = edge_3[i][0];

            if (x_left.point.X() > x_right.point.X()){
                swap_rasterised_points(x_left, x_right);
            }
            double x_left_value = x_left.point.X(), x_right_value = x_right.point.X();
            double I_left = x_left.intensity, I_right = x_right.intensity;
            //qDebug() << "x_left_value = " << x_left_value << " x_right_value = " << x_right_value;
            for (int x = x_left_value, y = edge_3[i][0].point.Y(); x <= x_right_value; x++)
            {
                //qDebug() << "x_left_value - x = " << x_left_value - x;
                if (fabs(x_left_value - x) == 0){
                    t = 0;
                }
                else{
                    t = (fabs(x_left_value - x)) / (fabs(x_left_value - x_right_value));
                }
                intensity = (1 - t) * I_left + t * I_right;
                //qDebug() << "xleft = " << x_left_value << " x = " << x << " x_right = " << x_right_value << "y = " << y << " t = " << t << " I_left = " << I_left << " I_right = " << I_right << " I_current = " << intensity;
                rasterised_points_t point;
                point.point = Vector2D(x, y);
                point.intensity = intensity;
                temp_points.push_back(point);
                //scene->addLine(x, y, x, y);
            }
            rasterized_points.push_back(temp_points);
            temp_points.clear();
        }
    }

    //qDebug() << "rasterize_points.size =  " << rasterized_points.size();
    return middle_point;
}

void swap_points(Point<int> &point_triangle_1, Point<int> &point_triangle_2)
{
    Point<int> temp_point;
    temp_point.set_point(point_triangle_1.get_x(), point_triangle_1.get_y(), 0);
    point_triangle_1.set_point(point_triangle_2.get_x(), point_triangle_2.get_y(), 0);
    point_triangle_2.set_point(temp_point.get_x(), temp_point.get_y(), 0);
}

void output_edge(std::vector<edge_t> &edge)
{
    for (int i = 0; i < edge.size(); i++){
        std::cout << "x = " << edge[i].x << " y = " << edge[i].y << std::endl;
    }
}

void create_line_by_int_brezenhem(std::vector<std::vector<rasterised_points_t>> &edge,
                                                         Point<int> start_point, Point <int> end_point, QGraphicsScene *scene,
                                                        Vector3D<double> normal_start, Vector3D<double> normal_end,
                                                            Vector3D<int> &light_position, plane_koeffs_t &plane_koeffs)
{
    Vector3D<double> light_direction;
    QPen *pen = new QPen(Qt::red);
    int flag_exchange = 0;
    int x_start = start_point.get_x(), y_start = start_point.get_y();
    int x_end = end_point.get_x(), y_end = end_point.get_y();

    int dx = x_end - x_start, dy = y_end - y_start;
    int sx = sign(dx), sy = sign(dy);
    dx = abs(dx), dy = abs(dy);

    if (dx > dy)
        flag_exchange = 0;
    else
    {
        flag_exchange = 1;
        swap(dx, dy);
    }

    double f = 2 * dy - dx;

    //std::cout << "x_temp = " << x_temp << " y_temp = " << y_temp << std::endl;
    int x_temp = x_start, y_temp = y_start;
    int i = 0;
    /*Vector2D edge_board(x_temp, y_temp);
    edge.push_back(edge_board);*/
    bool is_add_points = false;
    std::vector<rasterised_points_t> edge_board;
    double z = 0, x_3d = 0, y_3d = 0;
    rasterised_points_t point;

    double Istart = 0, Iend = 0, scalar = 0, intensity = 0, t = 0;
    //длина векторов V1U и V1V2
    double length_x_xstart = 0, length_xstart_xend = 0;
    Vector3D<double>edge_current, edge_all;
    edge_all.set_vector(x_end - x_start, y_end - y_start, 0);
    //длина вектора Vstart Vend
    length_xstart_xend = edge_all.length();

    z = calculate_depth(x_start, y_start, plane_koeffs, (double)std::numeric_limits<int>::min());
    x_3d = (int)((x_start - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    y_3d = (int)((y_start - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    light_direction.set_vector(light_position.X() - x_3d, light_position.Y() - y_3d, light_position.Z() - z);
    light_direction.normalize();
    scalar = std::max(dot_product<double, double>(normal_start, light_direction), 0.0);
    Istart = scalar;


    z = calculate_depth(x_end, y_end, plane_koeffs, (double)std::numeric_limits<int>::min());
    x_3d = (int)((x_end - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    y_3d = (int)((y_end - SCREEN_HEIGHT / 4) * (z + 1000)/1000);
    light_direction.set_vector(light_position.X() - x_3d, light_position.Y() - y_3d, light_position.Z() - z);
    light_direction.normalize();
    scalar = std::max(dot_product<double, double>(normal_end, light_direction), 0.0);
    Iend = scalar;

    //qDebug() << "Istart = " << Istart << " Iend = " << Iend << "\n";
    //qDebug() << "start_point: " << x_start << " " << y_start;
    //qDebug() << "end_point: " << x_end << " " << y_end;

    while (i <= dx)
    {
        if (is_add_points == true){
            edge.push_back(edge_board);
            edge_board.clear();
            is_add_points = false;
        }
        if (i == 0){
            intensity = Istart;
        }
        else{
            //qDebug() << "x_temp = " << x_temp  << " y_temp = " << y_temp;
            //qDebug() << "x_start = " << x_start  << " y_start = " << y_start;
            edge_current.set_vector(x_temp - x_start, y_temp - y_start, 0);
            length_x_xstart = edge_current.length();
            //qDebug() << "length_x_start = " << length_x_xstart << " length_xstart_xend = " << length_xstart_xend;
            t = length_x_xstart / length_xstart_xend;
            //qDebug() << "t = " << t;
            intensity = (1 - t) * Istart + t * Iend;
            //qDebug() << "x_start = " << x_start << "y_start = " << y_start << " x_temp = " << x_temp  << " y_temp = " << y_temp << "x_end = " << x_end  << " y_end = " << y_end  << "t = " << t << " intensity = " << intensity;
        }

        point.point = Vector2D(x_temp, y_temp);
        point.intensity = intensity;
        edge_board.push_back(point);
        //std::cout << "x_temp = " << x_temp << " y_temp = " << y_temp << std::endl;
        //scene->addLine(x_temp, y_temp, x_temp, y_temp, *pen);


        if (f >= 0){
            if (flag_exchange == 1){
                x_temp += sx;
            }
            else
            {
                y_temp += sy;
                is_add_points = true;
            }
            f -= 2 * dx;
        }

        if (f < 0){
            if (flag_exchange == 1)
            {
                y_temp += sy;
                is_add_points = true;
            }
            else{
                x_temp += sx;
            }
        }

        f += 2 * dy;
        i++;
    }
    /*Vector2D edge_board_last(x_temp, y_temp);
    edge.push_back(edge_board_last);*/
    edge.push_back(edge_board);
    edge_board.clear();

    //std::cout << "x_temp = " << x_temp << " y_temp = " << y_temp << std::endl;
}

int sign(int x)
{
    int value = 0;
    if (x > 0)
        value = 1;
    else if (x == 0)
        value = 0;
    else
        value = -1;

    return value;
}

void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<int> &min_point)
{
    min_point.set_point(point_1.get_x(), point_1.get_y(), 0);

    if (point_2.get_y() < min_point.get_y()){
        min_point.set_y(point_2.get_y());
        min_point.set_x(point_2.get_x());
    }

    if (point_3.get_y() < min_point.get_y()){
        min_point.set_y(point_3.get_y());
        min_point.set_x(point_3.get_x());
    }
}

void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<int> &max_point)
{
    max_point.set_point(point_1.get_x(), point_1.get_y(), 0);
    if (point_2.get_y() > max_point.get_y()){
        max_point.set_y(point_2.get_y());
        max_point.set_x(point_2.get_x());
    }

    if (point_3.get_y() > max_point.get_y()){
        max_point.set_y(point_3.get_y());
        max_point.set_x(point_3.get_x());
    }
}

void find_middle_point(Point<int> &middle_point, Point<int> &min_point, Point<int> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3)
{
    double y_middle = 0;
    int is_middle = 0; //если сторона || оси Оу
    /*std::cout << "point_1.x() = " << point_1.get_x() << " point_1.y() = " << point_1.get_y() << std::endl;
    std::cout << "point_2.x() = " << point_2.get_x() << " point_2.y() = " << point_2.get_y() << std::endl;
    std::cout << "point_3.x() = " << point_3.get_x() << " point_3.y() = " << point_3.get_y() << std::endl;*/
    if ((int)point_1.get_y() != min_point.get_y() && (int)point_1.get_x() != min_point.get_x()){
        if((int)point_1.get_y() != max_point.get_y() && (int)point_1.get_x() != max_point.get_x()){
            middle_point.set_point(point_1.get_x(), point_1.get_y(), 0);
            //std::cout << "is_middle_1\n";
            is_middle = 1;
        }
    }

    if ((int)point_2.get_y() != min_point.get_y() && (int)point_2.get_x() != min_point.get_x()){
        if((int)point_2.get_y() != max_point.get_y() && (int)point_2.get_x() != max_point.get_x()){
             middle_point.set_point(point_2.get_x(), point_2.get_y(), 0);
             //std::cout << "is_middle_2\n";
             is_middle = 1;
        }
    }

    if ((int)point_3.get_y() != min_point.get_y() && (int)point_3.get_x() != min_point.get_x()){
        if((int)point_3.get_y() != max_point.get_y() && (int)point_3.get_x() != max_point.get_x()){
            middle_point.set_point(point_3.get_x(), point_3.get_y(), 0);
            //std::cout << "is_middle_3\n";
            is_middle = 1;
        }
    }

    if (is_middle == 0){
        //std::cout << "is_middle_4\n";
        double x_min = point_1.get_x();
        if (point_2.get_x() < x_min)
            x_min = point_2.get_x();

        if (point_3.get_x() < x_min)
            x_min = point_3.get_x();

        middle_point.set_point(x_min, max_point.get_y(), 0);
    }
}


void calculate_equation_plane(plane_koeffs_t &plane_koeffs,
                                                  Point<double> point_1, Point<double> point_2, Point<double>point_3)
{
    Point<int> point_1_plane, point_2_plane, point_3_plane;
    point_1_plane.set_point(point_1.get_x(), point_1.get_y(), point_1.get_z());
    point_2_plane.set_point(point_2.get_x(), point_2.get_y(), point_2.get_z());
    point_3_plane.set_point(point_3.get_x(), point_3.get_y(), point_3.get_z());
    /*std::cout << "input points: ";
    point_1_plane.output_point();
    point_2_plane.output_point();
    point_3_plane.output_point();*/
    int vector_1_x = 0, vector_1_y = 0, vector_1_z = 0;
    int vector_2_x = 0, vector_2_y = 0, vector_2_z = 0;
    plane_koeffs.a = 0, plane_koeffs.b = 0, plane_koeffs.c = 0, plane_koeffs.d = 0;
    double d = 0;

    vector_1_x = point_2_plane.get_x() - point_1_plane.get_x();
    vector_1_y = point_2_plane.get_y() - point_1_plane.get_y();
    vector_1_z = point_2_plane.get_z() - point_1_plane.get_z();

    vector_2_x = point_3_plane.get_x() - point_1_plane.get_x();
    vector_2_y = point_3_plane.get_y() - point_1_plane.get_y();
    vector_2_z = point_3_plane.get_z() - point_1_plane.get_z();

    plane_koeffs.a = vector_1_y * vector_2_z - vector_1_z * vector_2_y;
    plane_koeffs.b = vector_2_x * vector_1_z - vector_2_z * vector_1_x;
    plane_koeffs.c = vector_1_x * vector_2_y - vector_1_y * vector_2_x;
    plane_koeffs.d = (-plane_koeffs.a *  (int)point_1.get_x() - plane_koeffs.b * (int)point_1.get_y() - plane_koeffs.c * (int)point_1.get_z());

    //std::cout << "Got equation: "  << plane_koeffs.a << "x, " << plane_koeffs.b << "y, " << plane_koeffs.c << "z, " << plane_koeffs.d << std::endl;
}

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                            std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                            plane_koeffs_t &plane_koeffs, Vector3D<int> &light_position,
                                            Triangle<double>&triangle_normals, Triangle<double>points_3d)
{
    //qDebug() << "CALCULATE DEPTH PIXELS.";
    //qDebug() << "rasterized_points = " << rasterized_points.size();
    //направление света
    Vector3D<double> light_direction;

    //глубина пикселя
    double z = 0;

    rasterised_points_t rasterize_point;
    int rasterize_x_value = 0, rasterize_y_value = 0;
    int size_row = rasterized_points.size(), size_column = 0;

    //исходный цвет
    int r = 119, g =221, b = 119;
    //выходной цвет
    int r_in = 0, g_in = 0, b_in = 0;

    int x_3d = 0, y_3d = 0;
    double scalar = 0;

    //qDebug() << "size_row_zbuffer = " << size_row;
    for (int i = 0; i < size_row; i++)
    {
        size_column = rasterized_points[i].size();
        //qDebug() << "size_column_buffer = " << size_column;
        for (int j = 0; j < size_column; j++)
        {
            rasterize_point = rasterized_points[i][j];
            rasterize_x_value = rasterize_point.point.X();
            rasterize_y_value = rasterize_point.point.Y();

            z = calculate_depth(rasterize_x_value, rasterize_y_value, plane_koeffs, zbuffer_matrix[rasterize_x_value][rasterize_y_value]);
            //qDebug() << "x_rasterize = " << rasterize_x_value << " y_rasterize = " << rasterize_y_value << " intensity = " << rasterized_points[i][j].intensity;
            //qDebug() << "z = " << z << " zbuffer_value = " << zbuffer_matrix[rasterize_x_value][rasterize_y_value];

            if (z > zbuffer_matrix[rasterize_x_value][rasterize_y_value])
            {
                zbuffer_matrix[rasterize_x_value][rasterize_y_value] = z;

                r_in = r * rasterize_point.intensity;
                g_in = g * rasterize_point.intensity;
                b_in = b * rasterize_point.intensity;

                color_matrix[rasterize_x_value][rasterize_y_value].setRgb(r_in, g_in, b_in);
            }
        }
    }



}

/*void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                            std::vector<std::vector<Vector2D>> &rasterized_points,
                                            plane_koeffs_t &plane_koeffs, Vector3D<int> &light_position,
                                            Vector3D<double> &normal)
{
    double z = 0;
    int rasterize_x = 0, rasterize_y = 0;
    int size_row = rasterized_points.size(), size_column = 0;

    int r = 119, g =221, b = 119;
    int r_in = 0, g_in = 0, b_in = 0;
    int x_3d = 0, y_3d = 0;
    double scalar = 0;
    for (int i = 0; i < size_row; i++)
    {
        size_column = rasterized_points[i].size();
        for (int j = 0; j < size_column; j++)
        {
            rasterize_x = rasterized_points[i][j].X();
            rasterize_y = rasterized_points[i][j].Y();

            z = calculate_depth(rasterize_x, rasterize_y, plane_koeffs, zbuffer_matrix[rasterize_x][rasterize_y]);

            if (z > zbuffer_matrix[rasterize_x][rasterize_y])
            {
                //std::cout << "z = " << z << std::endl;
                //std::cout << "rasterize_X = " << rasterize_x << std::endl;
                //std::cout << "rasterize_y = " << rasterize_y << std::endl;
                x_3d = (int)((rasterize_x - SCREEN_WIDTH / 4)*(z + 1000)/1000);
                y_3d = (int)((rasterize_y - SCREEN_HEIGHT / 4)*(z + 1000)/1000);
                //std::cout << "x_3d = " << x_3d << " y_3d = " << y_3d << std::endl;;
                Vector3D<double> light_direction(light_position.X() - x_3d, light_position.Y() - y_3d, light_position.Z() - z);

                //light_direction.output();
                light_direction.normalize();
                //light_direction.output();
                //normal.output();

                scalar = std::max(dot_product<double, double>(normal, light_direction), 0.0);
                //std::cout << "scalar = " << scalar << std::endl;
                zbuffer_matrix[rasterize_x][rasterize_y] = z;

                r_in = r * scalar * 0.8 * 1;
                g_in = g * scalar * 0.8 * 1;
                b_in = b * scalar * 0.8 * 1;
                color_matrix[rasterize_x][rasterize_y].setRgb(r_in, g_in, b_in);
            }
        }
    }
}*/

double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double zbuffer_value)
{
    double z = zbuffer_value;
    if (plane_koeffs.c != 0){
        z = -(plane_koeffs.a * rasterize_x + plane_koeffs.b * rasterize_y + plane_koeffs.d) / plane_koeffs.c;
    }
    else{
        //qDebug() << "Деление на ноль.\n";
        //qDebug() << "rasterize_x = " << rasterize_x << " rasterize_y = " << rasterize_y;
    }
    return z;
}

void swap_values(int &value_1, int &value_2){
    double temp_value = value_1;
    value_1 = value_2;
    value_2 = temp_value;
}

void swap_rasterised_points(rasterised_points_t &value_1, rasterised_points_t &value_2){
    rasterised_points_t temp_value = value_1;
    value_1 = value_2;
    value_2 = temp_value;
}
