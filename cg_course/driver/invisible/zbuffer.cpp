#include <math.h>
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/figure/figure.h"
#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.hpp"
#include "driver/transform/transform.h"
#include "driver/geometry/vector/vector.h"
#include "driver/geometry/vector/vector_2.hpp"
//#include "driver/geometry/vector/vector_3.hpp"
//#include "driver/light/light.hpp"



double find_max_point(double value_1, double value_2, double value_3);
void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<int> &min_point);
void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<int> &max_point);
void find_middle_point(Point<int> &middle_point, Point<int> &min_point, Point<int> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3);

double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double z_zbuffer);
int sign(int x);
void create_line_by_int_brezenhem(std::vector<std::vector<Vector2D>> &edge,
                                                         Point<int> start_point, Point <int> end_point, QGraphicsScene *scene);
void output_edge(std::vector<edge_t> &edge);

void swap_values(int &value_1, int &value_2);
void swap_points(Point<int> &point_triangle_1, Point<int> &point_triangle_2);



void rasterize_triangle(std::vector<std::vector<Vector2D>> &rasterized_points, Point<double> &point_1,
                                    Point<double> &point_2, Point<double> &point_3, QGraphicsScene *scene,
                                    std::vector<std::vector<QColor>> colors)
{
    /*std::cout << std::endl << "Треугольник: point_1: ";
    point_1.output_point();
    std::cout << " " << "point_2: ";
    point_2.output_point();
    std::cout << " " << "point_3: ";
    point_3.output_point();*/

    //преобразование в целочисленные точки
    Point<int> point_triangle_1, point_triangle_2, point_triangle_3;
    point_triangle_1.set_point(point_1.get_x(), point_1.get_y(), point_1.get_z());
    point_triangle_2.set_point(point_2.get_x(), point_2.get_y(), point_2.get_z());
    point_triangle_3.set_point(point_3.get_x(), point_3.get_y(), point_3.get_z());

    //определение целочисленным брезенхемом границ треугольника
    int min_mode = 1, max_mode = 2;
    std::vector<std::vector<Vector2D>> edge_1, edge_2, edge_3;

    //вычисление вектора нормали для плоскости
    //Vector3D normal = normal(point_triangle_1, point_triangle_2, point_triangle_3);

    //вычисление min, middle, max точек треугольника
    Point<int> min_point, max_point, middle_point;
    if (point_triangle_2.get_y() < point_triangle_1.get_y()){
        swap_points(point_triangle_1, point_triangle_2);
    }

    if (point_triangle_3.get_y() < point_triangle_1.get_y()){
        swap_points(point_triangle_1, point_triangle_3);
    }

    if (point_triangle_2.get_y() > point_triangle_3.get_y()){
        swap_points(point_triangle_2, point_triangle_3);
    }

    min_point.set_point(point_triangle_1.get_x(), point_triangle_1.get_y(), 0);
    middle_point.set_point(point_triangle_2.get_x(), point_triangle_2.get_y(), 0);
    max_point.set_point(point_triangle_3.get_x(), point_triangle_3.get_y(), 0);

    //вычисление координат пикселей ребер треугольника
    create_line_by_int_brezenhem(edge_1, min_point, middle_point, scene);
    create_line_by_int_brezenhem(edge_2, min_point, max_point, scene);
    create_line_by_int_brezenhem(edge_3, middle_point, max_point, scene);

    /*std::cout << std::endl << "New: point_1: ";
    point_triangle_1.output_point();
    std::cout << " " << "point_2: ";
    point_triangle_2.output_point();
    std::cout << " " << "point_3: ";
    point_triangle_3.output_point();*/

    /*std::cout << std::endl << "min_point: ";
    min_point.output_point();
    std::cout << std::endl << "middle_point: ";
    middle_point.output_point();
    std::cout << std::endl << "max_point: ";
    max_point.output_point();*/

    int edge_1_size = edge_1.size(), edge_2_size = edge_2.size(), edge_3_size = edge_3.size();
    /*std::cout << "Точки ребра 1:" << std::endl;
    for (int i = 0; i < edge_1_size; i++){
        for (int j = 0; j < edge_1[i].size(); j++){
            edge_1[i][j].output();
        }
        std::cout << std::endl;
    }*/

    /*std::cout << "Точки ребра 2:" << std::endl;
    for (int i = 0; i < edge_2_size; i++){
        for (int j = 0; j < edge_2[i].size(); j++){
            edge_2[i][j].output();
        }
        std::cout << std::endl;
    }*/

    /*std::cout << "Точки ребра 3:" << std::endl;
    for (int i = 0; i < edge_3_size; i++){
        for (int j = 0; j < edge_3[i].size(); j++){
            edge_3[i][j].output();
        }
        std::cout << std::endl;
    }*/

    //std::cout << "edge_1_size = " << edge_1_size << std::endl;
    //std::cout << "edge_2_size = " << edge_2_size << std::endl;


    //int edge_1_i_size = edge_1[0].size();


    if (middle_point.get_x() < max_point.get_x())
    {
        int edge_1_i_size, edge_2_i_size, edge_3_i_size;
        for (int i = 0; i < edge_1_size; i++)
        {
            edge_1_i_size = edge_1[i].size();
            edge_2_i_size = edge_2[i].size();
            int x_left = edge_1[i][edge_1_i_size - 1].X(), x_right = edge_2[i][edge_2_i_size - 1].X();
            if (x_left > x_right){
                swap_values(x_left, x_right);
            }
            std::vector<Vector2D> temp_points;
            for (int y = edge_1[i][0].Y(); x_left <= x_right; x_left++){
                //Vector3D light_direction();
                temp_points.push_back(Vector2D(x_left, y));
                //scene->addLine(x_left, y, x_left, y);
            }
            rasterized_points.push_back(temp_points);
        }

        for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
        {
            edge_2_i_size = edge_2[edge_2_size - 1 - j].size();
            //std::cout << "new_edge_2_i_size = " << edge_2_i_size << std::endl;

            int x_left = edge_3[i][0].X(), x_right = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1].X();
            if (x_left > x_right){
                swap_values(x_left, x_right);
            }
            std::vector<Vector2D> temp_points;
            for (int y = edge_3[i][0].Y(); x_left <= x_right; x_left++){
                temp_points.push_back(Vector2D(x_left, y));
                //scene->addLine(x_left, y, x_left, y);
            }
            rasterized_points.push_back(temp_points);
        }
    }
    else{
        //std::cout << "here_2\n";
        int edge_1_i_size, edge_2_i_size, edge_3_i_size;
        for (int i = 0; i < edge_1_size; i++)
        {
            edge_1_i_size = edge_1[i].size();
            edge_2_i_size = edge_2[i].size();
            //std::cout << "x_left = " << edge_1[i][edge_1_i_size - 1].X() << std::endl;
            //std::cout << "x_right = " << edge_2[i][edge_2_i_size-1].X() << std::endl;
            std::vector<Vector2D> temp_points;
            for (int x_left = edge_2[i][0].X(), x_right = edge_1[i][edge_1_i_size - 1].X(), y = edge_2[i][0].Y();
                        x_left <= x_right; x_left++){
                temp_points.push_back(Vector2D(x_left, y));
                //scene->addLine(x_left, y, x_left, y);
            }
            rasterized_points.push_back(temp_points);
        }

        for (int i = edge_3_size - 1, j = 0; i >=0; i--, j++)
        {
            edge_3_i_size = edge_3[i].size();
            edge_2_i_size = edge_2[edge_2_size - 1 - j].size();
            //std::cout << "new_edge_2_i_size = " << edge_2_i_size << std::endl;
            //std::cout << "x_left = " << edge_2[edge_2_size - 1 - j][edge_2_i_size - 1].X() << std::endl;
            //std::cout << "x_right = " << edge_3[i][edge_3_i_size - 1].X() << std::endl;
            std::vector<Vector2D> temp_points;
            for (int x_left = edge_2[edge_2_size - 1 - j][edge_2_i_size - 1].X(), x_right = edge_3[i][0].X(), y = edge_3[i][0].Y();
                        x_left <= x_right; x_left++){
                temp_points.push_back(Vector2D(x_left, y));
                //scene->addLine(x_left, y, x_left, y);
            }
            rasterized_points.push_back(temp_points);
        }
    }
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

void create_line_by_int_brezenhem(std::vector<std::vector<Vector2D>> &edge,
                                                         Point<int> start_point, Point <int> end_point, QGraphicsScene *scene)
{ 
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
    std::vector<Vector2D> edge_board;
    while (i <= dx)
    {
        if (is_add_points == true){
            edge.push_back(edge_board);
            edge_board.clear();
            is_add_points = false;
        }

        edge_board.push_back(Vector2D(x_temp, y_temp));
        //std::cout << "x_temp = " << x_temp << " y_temp = " << y_temp << std::endl;
        scene->addLine(x_temp, y_temp, x_temp, y_temp, *pen);


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
    std::cout << "input points: ";
    point_1_plane.output_point();
    point_2_plane.output_point();
    point_3_plane.output_point();
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

    std::cout << "Got equation: "  << plane_koeffs.a << "x, " << plane_koeffs.b << "y, " << plane_koeffs.c << "z, " << plane_koeffs.d << std::endl;
}

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                           std::vector<std::vector<Vector2D>> &rasterized_points,
                                           plane_koeffs_t &plane_koeffs, Vector3D &light_position,
                                            Vector3D &normal)
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
                std::cout << "z = " << z << std::endl;
                std::cout << "rasterize_X = " << rasterize_x << std::endl;
                std::cout << "rasterize_y = " << rasterize_y << std::endl;
                x_3d = (rasterize_x - SCREEN_WIDTH / 4)*(z + 1000)/1000;
                y_3d = (rasterize_y - SCREEN_HEIGHT / 4)*(z + 1000)/1000;
                std::cout << "x_3d = " << x_3d << " y_3d = " << y_3d << std::endl;;
                Vector3D light_direction(light_position.X() - x_3d, light_position.Y() - y_3d, light_position.Z() - z);

                light_direction.output();
                light_direction.normalize();
                light_direction.output();
                normal.output();

                scalar = fabs(dot_product(normal, light_direction));
                std::cout << "scalar = " << scalar << std::endl;
                zbuffer_matrix[rasterize_x][rasterize_y] = z;

                r_in = r * scalar * 0.8 * 1;
                g_in = g * scalar * 0.8 * 1;
                b_in = b * scalar * 0.8 * 1;
                color_matrix[rasterize_x][rasterize_y].setRgb(r_in, g_in, b_in);
            }
        }
    }
}

double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double z_zbuffer)
{
    double z = z_zbuffer;
    if (plane_koeffs.c != 0){
        z = -(plane_koeffs.a * rasterize_x + plane_koeffs.b * rasterize_y + plane_koeffs.d) / plane_koeffs.c;
    }
    return z;
}

void swap_values(int &value_1, int &value_2){
    double temp_value = value_1;
    value_1 = value_2;
    value_2 = temp_value;
}
