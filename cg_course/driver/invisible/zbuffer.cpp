#include <math.h>
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/figure/figure.h"
#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.hpp"
#include "driver/transform/transform.h"

void rasterize_triangle(std::vector<std::vector<Point<int>>> &rasterized_points, Point<double> &point_1,
                                                                                           Point<double> &point_2, Point<double> &point_3, QGraphicsScene *scene);

double find_max_point(double value_1, double value_2, double value_3);
void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<int> &min_point);
void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<int> &max_point);
void find_middle_point(Point<int> &middle_point, Point<int> &min_point, Point<int> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3);
void calculate_equation_plane(plane_koeffs_t &plane_koeffs,
                                                 Point<double> point_1, Point<double> point_2,
                                                 Point<double>point_3);

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix, std::vector<std::vector<QColor>> &color_matrix,
                                           std::vector<std::vector<Point<int>>> &rasterized_points, plane_koeffs_t &plane_koeffs);
double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double z_zbuffer);
int sign(int x);
void create_line_by_int_brezenhem(std::vector<edge_t> &edge, Point<int> start_point, Point <int> end_point, QGraphicsScene *scene);
void output_edge(std::vector<edge_t> &edge);

void swap_values(int &value_1, int &value_2);

void remove_invisible_lines(ZBuffer &zbuffer, Landscape &landscape, QGraphicsScene *scene)
{
    /*int size_row = landscape.get_width(), size_column = landscape.get_height();
    for (int i = 0; i < size_row; i++){
        for (int j = 0; j < size_column; j++){
            int index_i = landscape.get_screen_point(i,j).get_x(),
                 index_j = landscape.get_screen_point(i,j).get_y();
            double z = landscape.get_screen_point(i, j).get_z();
            if (z > zbuffer.get_zbuffer_matrix()[index_i][index_j]){
                //std::cout << "here\n";
                zbuffer.get_zbuffer_matrix()[index_i][index_j] = z;
                zbuffer.get_color_matrix()[index_i][index_j].setRgb(0, 0, 0);
            }
        }
    }*/

    plane_koeffs_t plane_koeffs_up, plane_koeffs_down;

    int height_landscape = landscape.get_height(), width_landscape = landscape.get_width();
    for (int i = 0; i < height_landscape; i++){
        for (int j = 0; j < width_landscape; j++)
        {
            //std::cout << "i = " << i << " j = " << j << std::endl;
            if (/*i == 0 && j == 0*/i < landscape.get_height() - 1 && j < landscape.get_width() - 1)
            {
                 std::vector<std::vector<Point<int>>> rasterized_points_up;
                 std::vector<std::vector<Point<int>>> rasterized_points_down;
                 rasterize_triangle(rasterized_points_up, landscape.get_screen_point(i, j),
                                                                                 landscape.get_screen_point(i, j + 1),
                                                                                 landscape.get_screen_point(i + 1, j + 1), scene);
                 rasterize_triangle(rasterized_points_down, landscape.get_screen_point(i, j),
                                                                                 landscape.get_screen_point(i + 1, j),
                                                                                 landscape.get_screen_point(i + 1, j + 1), scene);
                //std::cout << "End_rasterize!" << std::endl;
                 std::cout << "rasterized_points_up";
                 for (int i = 0; i < rasterized_points_up.size(); i++){
                     for (int j = 0; j < rasterized_points_up[i].size(); j++){
                         rasterized_points_up[i][j].output_point();
                     }
                     std::cout << std::endl;
                 }

                 std::cout << "rasterized_points_down";
                 for (int i = 0; i < rasterized_points_up.size(); i++){
                     for (int j = 0; j < rasterized_points_up[i].size(); j++){
                         rasterized_points_up[i][j].output_point();
                     }
                     std::cout << std::endl;
                 }
                std::cout << "rasterized_points_up.size() = " << rasterized_points_up.size() << std::endl;
                //QPen *pen = new QPen(Qt::red);
                //scene->addLine(302, 349, 302, 349, *pen);
                /*scene->addLine(331, 359, 331, 359, *pen);
                scene->addLine(290, 361, 290, 361, *pen);*/

                calculate_equation_plane(plane_koeffs_up,
                                                         landscape.get_point(i, j),
                                                         landscape.get_point(i, j + 1),
                                                         landscape.get_point(i + 1, j + 1));
                calculate_equation_plane(plane_koeffs_down,
                                                         landscape.get_point(i, j),
                                                         landscape.get_point(i + 1, j),
                                                         landscape.get_point(i + 1, j + 1));
                //std::cout << "End_equation!" << std::endl;
                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_up, plane_koeffs_up);
                //std::cout << "End_depth1!" << std::endl;
                calculate_depth_pixels(zbuffer.get_zbuffer_matrix(), zbuffer.get_color_matrix(),
                                                     rasterized_points_down, plane_koeffs_down);
                //std::cout << "End_depth2!" << std::endl;*/
            }
        }
    }
    //std::cout << "END!";*/
}

void rasterize_triangle(std::vector<std::vector<Point<int>>> &rasterized_points, Point<double> &point_1,
                                    Point<double> &point_2, Point<double> &point_3, QGraphicsScene *scene)
{
    std::cout << std::endl << "point_1: ";
    point_1.output_point();
    std::cout << std::endl << "point_2: ";
    point_2.output_point();
    std::cout << std::endl << "point_3: ";
    point_3.output_point();

    //нахождение минимальной, средней и макимальной точек
    Point<int> min_point, max_point, middle_point;
    find_min_point(point_1, point_2, point_3, min_point);
    find_max_point(point_1, point_2, point_3, max_point);
    find_middle_point(middle_point, min_point, max_point, point_1, point_2, point_3);
    std::cout << std::endl << "min_point: ";
    min_point.output_point();
    std::cout << std::endl << "middle_point: ";
    middle_point.output_point();
    std::cout << std::endl << "max_point: ";
    max_point.output_point();
    //определение целочисленным брезенхемом границ треугольника
    std::vector<edge_t> edge_1, edge_2, edge_3;
    create_line_by_int_brezenhem(edge_1, min_point, middle_point, scene);
    create_line_by_int_brezenhem(edge_2, min_point, max_point, scene);
    create_line_by_int_brezenhem(edge_3, middle_point, max_point, scene);

    //растеризация верхнего треугольника
    //edge_1 - x1, x2; edge_2 - x1, x3, edge_3 - x2, x3
    int edge_1_size = edge_1.size(), edge_2_size = edge_2.size(), edge_3_size = edge_3.size();

    //for (int i = 0; i < edge_3_size; i++){
     //   std::cout << "(x, y) = " << "(" << edge_3[i].x << ", " << edge_3[i].y << ")" << std::endl;
    //}

    QPen *pen = new QPen(Qt::black);


    //std::cout << "edge_1[edge_1 - 1] = " << edge_1[edge_1_size - 1].y << std::endl;
    int last_i_left = 0, last_i_right = 0;
    //растеризация верхнего треугольника
    for (int y = edge_1[0].y, y_last = edge_1[edge_1_size - 1].y; y < y_last; y++)
    {
            //std::cout << "y_current = " << y << std::endl;
            int x_left = 0, x_right = 0;
            bool x_left_find = false, x_right_find = false;

            for (int i = last_i_left; i < edge_1_size - 1 && x_left_find == false; i++){
                if (edge_1[i + 1].y != y){
                    x_left = edge_1[i+1].x;
                    x_left_find = true;
                    last_i_left = i + 1;
                }
            }

            for (int i = last_i_right; i < edge_2_size - 1 && x_right_find == false; i++){
                if (edge_2[i + 1].y != y){
                    x_right = edge_2[i].x;
                    x_right_find = true;
                    last_i_right = i + 1;
                }
            }

            if (x_left > x_right){
                swap_values(x_left, x_right);
            }
            std::vector<Point<int>> temp_points;
            for(int x = x_left; x < x_right; x++){
                //scene->addLine(x, y, x, y, *pen);
                temp_points.push_back(Point<int>(x, y, 0));
            }
            rasterized_points.push_back(temp_points);

            //std::cout << "last_i_left" << last_i_left << "; last_i_right = " << last_i_right << std::endl;
            //std::cout << "x_left" << x_left << "; x_right = " << x_right << std::endl;
    }

    //std::cout << "DOWN" << std::endl;
    last_i_left = edge_2_size - 1, last_i_right = edge_3_size - 1;
    //std::cout << "edge_3[edge_3 - 1] = " << edge_3[edge_3_size - 1].y << std::endl;
    int x_left = 0, x_right = 0;
    for (int y = edge_3[edge_3_size - 1].y, y_last = edge_3[0].y; y > y_last; y--)
    {
            //std::cout << "y_current = " << y << std::endl;

            bool x_left_find = false, x_right_find = false;

            for (int i = last_i_left; i >= 0 && x_left_find == false; i--){
                if (edge_2[i - 1].y != y){
                    x_left = edge_2[i - 1].x;
                    x_left_find = true;
                    last_i_left = i - 1;
                }
            }

            for (int i = last_i_right; i >= 0 && x_right_find == false; i--){
                if (edge_3[i - 1].y != y){
                    x_right = edge_3[i - 1].x;
                    x_right_find = true;
                    last_i_right = i - 1;
                }
            }

            //std::cout << "before: x_left" << x_left << "; x_right = " << x_right << std::endl;
            if (x_left > x_right){
                swap_values(x_left, x_right);
            }
            std::vector<Point<int>> temp_points;
            for(int x = x_left; x < x_right; x++){
                //scene->addLine(x, y, x, y, *pen);
                temp_points.push_back(Point<int>(x, y, 0));
            }
            rasterized_points.push_back(temp_points);

            //std::cout << "last_i_left" << last_i_left << "; last_i_right = " << last_i_right << std::endl;
            //std::cout << "x_left" << x_left << "; x_right = " << x_right << std::endl;
    }

    //отображение средней линии
    std::cout << "x_left" << x_left << "; x_right = " << x_right << std::endl;
    //x_right = x_left;
    //x_left = edge_1[edge_1_size-1].x;
    std::cout << "x_left" << x_left << "; x_right = " << x_right << std::endl;

    if (x_left > x_right){
        swap_values(x_left, x_right);
    }

    std::vector<Point<int>> temp_points;
    for(int x = x_left, y = middle_point.get_y(); x <= x_right; x++){
        //scene->addLine(x, y, x, y, *pen);
        temp_points.push_back(Point<int>(x, y, 0));
    }
    rasterized_points.push_back(temp_points);
}

void output_edge(std::vector<edge_t> &edge)
{
    for (int i = 0; i < edge.size(); i++){
        std::cout << "x = " << edge[i].x << " y = " << edge[i].y << std::endl;
    }
}

void create_line_by_int_brezenhem(std::vector<edge_t> &edge, Point<int> start_point, Point <int> end_point, QGraphicsScene *scene)
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

    int x_temp = x_start, y_temp = y_start;
    int i = 0;
    while (i <= dx)
    {
        edge_t dop_edge = {x_temp, y_temp};
        edge.push_back(dop_edge);
        scene->addLine(x_temp, y_temp, x_temp, y_temp, *pen);

        if (f >= 0){
            if (flag_exchange == 1){
                x_temp += sx;
            }
            else{
                y_temp += sy;
            }
            f -= 2 * dx;
        }

        if (f < 0){
            if (flag_exchange == 1){
                y_temp += sy;
            }
            else{
                x_temp += sx;
            }
        }

        f += 2 * dy;
        i++;
    }
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
    if ((int)point_1.get_y() != min_point.get_y() && (int)point_1.get_x() != min_point.get_x()){
        if((int)point_1.get_y() != max_point.get_y() && (int)point_1.get_x() != max_point.get_x()){
            middle_point.set_point(point_1.get_x(), point_1.get_y(), 0);
            is_middle = 1;
        }
    }

    if ((int)point_2.get_y() != min_point.get_y() && (int)point_2.get_x() != min_point.get_x()){
        if((int)point_2.get_y() != max_point.get_y() && (int)point_2.get_x() != max_point.get_x()){
             middle_point.set_point(point_2.get_x(), point_2.get_y(), 0);
             is_middle = 1;
        }
    }

    if ((int)point_3.get_y() != min_point.get_y() && (int)point_3.get_x() != min_point.get_x()){
        if((int)point_3.get_y() != max_point.get_y() && (int)point_3.get_x() != max_point.get_x()){
            middle_point.set_point(point_3.get_x(), point_3.get_y(), 0);
            is_middle = 1;
        }
    }

    if (is_middle == 0){
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
    std::cout << "input points: ";
    point_1.output_point();
    point_2.output_point();
    point_3.output_point();
    double vector_1_x = 0, vector_1_y = 0, vector_1_z = 0;
    double vector_2_x = 0, vector_2_y = 0, vector_2_z = 0;
    plane_koeffs.a = 0, plane_koeffs.b = 0, plane_koeffs.c = 0, plane_koeffs.d = 0;
    double d = 0;

    vector_1_x = (int)point_2.get_x() - (int)point_1.get_x();
    vector_1_y = (int)point_2.get_y() - (int)point_1.get_y();
    vector_1_z = (int)point_2.get_z() - (int)point_1.get_z();

    vector_2_x = (int)point_3.get_x() - (int)point_1.get_x();
    vector_2_y = (int)point_3.get_y() - (int)point_1.get_y();
    vector_2_z = (int)point_3.get_z() - (int)point_1.get_z();

    plane_koeffs.a = vector_1_y * vector_2_z - vector_1_z * vector_2_y;
    plane_koeffs.b = vector_2_x * vector_1_z - vector_2_z * vector_1_x;
    plane_koeffs.c = vector_1_x * vector_2_y - vector_1_y * vector_2_x;
    plane_koeffs.d = (-plane_koeffs.a *  (int)point_1.get_x() - plane_koeffs.b * (int)point_1.get_y() - plane_koeffs.c * (int)point_1.get_z());

    std::cout << "Got equation: "  << plane_koeffs.a << "x, " << plane_koeffs.b << "y, " << plane_koeffs.c << "z, " << plane_koeffs.d << std::endl;
}

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                           std::vector<std::vector<Point<int>>> &rasterized_points,
                                           plane_koeffs_t &plane_koeffs)
{
    double z = 0;
    int rasterize_x = 0, rasterize_y = 0;
    int size_row = rasterized_points.size(), size_column = 0;
    std::cout << "size_row = " << size_row << std::endl;
    std::cout << "size_column = " << size_column << std::endl;
    std::cout << "CALCULATE\n";
    std::cout << "plane_koeffs:";
    //std::cout << "a = " << plane_koeffs.a << " b = " << plane_koeffs.b << " c = " << plane_koeffs.c << " d = " << plane_koeffs.d << std::endl;
    for (int i = 0; i < size_row; i++)
    {
        size_column = rasterized_points[i].size();
        for (int j = 0; j < size_column; j++)
        {
            rasterize_x = rasterized_points[i][j].get_x();
            rasterize_y = rasterized_points[i][j].get_y();
            //std::cout << "rasterize_x = " << rasterize_x;
            //std::cout << " rasterize_y = " << rasterize_y << std::endl;
            z = calculate_depth(rasterize_x, rasterize_y, plane_koeffs, zbuffer_matrix[rasterize_x][rasterize_y]);
            std::cout << "z = " << z << std::endl;
            //std::cout << "z = " << z << std::endl;
            std::cout << "rasterize_x = " << rasterize_x << " rasterize_y = " << rasterize_y << std::endl;
            //std::cout << "zbuffer_matrix[rasterize_x][rasterize_y] = " << zbuffer_matrix[rasterize_x][rasterize_y] << std::endl;
            if (z >= zbuffer_matrix[rasterize_x][rasterize_y])
            {
                zbuffer_matrix[rasterize_x][rasterize_y] = z;
                //std::cout << "here" << std::endl;
                //std::cout << "zbuffer_matrix[rasterize_x][rasterize_y] = " << zbuffer_matrix[rasterize_x][rasterize_y] << std::endl;

                //std::cout << "color.\n";
                //color_matrix[rasterize_x][rasterize_y].setRgb(0, 0, 0);
                //std::cout << "end_if_color.\n";
                //if (j == 0 || j == size_column - 1){
                    //std::cout << "here_color" << std::endl;
                color_matrix[rasterize_x][rasterize_y].setRgb(0, 0, 0);
                    //std::cout << "color_matrix[rasterize_x][rasterize_y] =" << color_matrix[rasterize_x][rasterize_y].name() << std::endl;
                //}
                //std::cout << "zbuffer_matrix[" << rasterize_x << "][" << rasterize_y << "] = " << zbuffer_matrix[rasterize_x][rasterize_y] << std::endl;
             //std::cout << "end_iteration.\n";
            }
        }
        std::cout << std::endl;
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
