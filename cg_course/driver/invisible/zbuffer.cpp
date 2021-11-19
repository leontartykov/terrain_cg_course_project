#include <math.h>
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/figure/figure.h"
#include "driver/landscape/landscape.h"
#include "driver/geometry/point/point.hpp"

std::vector<std::vector<Point<int>>> rasterize_triangle(Point<double> &point_1,
                                                                                           Point<double> &point_2, Point<double> &point_3);

double find_max_point(double value_1, double value_2, double value_3);
void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<double> &min_point);
void find_max_point(Point<double> &point_1, Point<double> &point_2,
                                 Point<double> &point_3, Point<double> &max_point);
void find_middle_point(Point<double> &middle_point, Point<double> &min_point, Point<double> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3);
void calculate_equation_plane(plane_koeffs_t &plane_koeffs,
                                                 Point<double> point_1, Point<double> point_2,
                                                 Point<double>point_3);

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix, std::vector<std::vector<QColor>> &color_matrix,
                                           std::vector<std::vector<Point<int>>> &rasterized_points, plane_koeffs_t &plane_koeffs);
double calculate_depth(int rasterize_x, int rasterize_y, plane_koeffs_t &plane_koeffs, double z_zbuffer);

void remove_invisible_lines(ZBuffer &zbuffer, Landscape &landscape)
{
    std::vector<std::vector<Point<int>>> rasterized_points_up;
    std::vector<std::vector<Point<int>>> rasterized_points_down;

    plane_koeffs_t plane_koeffs_up, plane_koeffs_down;

    int height_landscape = landscape.get_height(), width_landscape = landscape.get_width();
    for (int i = 0; i < height_landscape; i++){
        for (int j = 0; j < width_landscape; j++){
            //std::cout << "i = " << i << " j = " << j << std::endl;
            if (i < landscape.get_height() - 1 && j < landscape.get_width() - 1)
            {
                rasterized_points_up = rasterize_triangle(landscape.get_screen_point(i, j),
                                                                                 landscape.get_screen_point(i, j + 1),
                                                                                 landscape.get_screen_point(i + 1, j + 1));
                rasterized_points_down = rasterize_triangle(landscape.get_screen_point(i, j),
                                                                                 landscape.get_screen_point(i + 1, j),
                                                                                 landscape.get_screen_point(i + 1, j + 1));
                //std::cout << "End_rasterize!" << std::endl;
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
                //std::cout << "End_depth2!" << std::endl;
            }
        }
    }
    //std::cout << "END!";
}

std::vector<std::vector<Point<int>>> rasterize_triangle(Point<double> &point_1,
                                                                                           Point<double> &point_2, Point<double> &point_3)
{
    std::vector<std::vector<Point<int>>> rasterized_points;

    Point<double> min_point, max_point, middle_point;
    find_min_point(point_1, point_2, point_3, min_point);

    find_max_point(point_1, point_2, point_3, max_point);
    find_middle_point(middle_point, min_point, max_point,
                                 point_1, point_2, point_3);

    double dx_12 = 0, dx_23 = 0, dx_13 = 0;
    double dy_12 = 0, dy_23 = 0, dy_13 = 0;

    //определение приращений dx по каждой из сторон треугольника
    if ((int)middle_point.get_y() - (int)min_point.get_y() != 0){
            dx_12 = (min_point.get_x() - middle_point.get_x()) / ((int)min_point.get_y() - (int)middle_point.get_y());
    }

    if ((int)max_point.get_y() - (int)middle_point.get_y() != 0){
            dx_23 = (middle_point.get_x() - max_point.get_x()) / ((int)middle_point.get_y() - (int)max_point.get_y());
    }

    if ((int)max_point.get_y() - (int)min_point.get_y() != 0){
            dx_13 = (min_point.get_x() - max_point.get_x()) / ((int)min_point.get_y() - (int)max_point.get_y());
    }

    double fixed_point_x_12 = min_point.get_x();
    double fixed_point_x_13 = min_point.get_x();

    double min_fixed_x = 0, max_fixed_x = 0;
    double min_dx = 0, max_dx = 0;
    int exchanged = 0;

    //определение левой фиксированной точки
    if (fixed_point_x_12 + dx_12 < fixed_point_x_13 + dx_13)
    {
        min_fixed_x = fixed_point_x_12, max_fixed_x = fixed_point_x_13;
        min_dx = dx_12, max_dx = dx_13;
    }
    else
    {
        min_fixed_x = fixed_point_x_13, max_fixed_x = fixed_point_x_12;
        min_dx = dx_13, max_dx = dx_12;
        exchanged = 1;
    }

    //растеризация верхнего треугольника
    int resize_array = 0;
    for (int y = min_point.get_y(); y <= middle_point.get_y(); y++)
    {
        std::vector<Point<int>> temp;
        resize_array = (int)max_fixed_x - (int)min_fixed_x;
        if (resize_array == 0){
            temp.push_back(Point<int>((int)min_fixed_x, y, 0));
            //std::cout << "(" << (int)min_fixed_x << ", " << y << std::endl;
        }
        else
        {
            for (int x = min_fixed_x; x <= max_fixed_x; x++){
                temp.push_back(Point<int>(x, y, 0));
                //std::cout << "(" << x << ", " << y << std::endl;
            }
            //std::cout << std::endl;
        }
        rasterized_points.push_back(temp);
        min_fixed_x += min_dx;
        max_fixed_x += max_dx;
    }

   // std::cout << "rasterized_points[0][0] = "; rasterized_points[0][0].output_point();

    min_fixed_x -= min_dx;
    min_fixed_x = std::round(min_fixed_x);

    if (exchanged == 0)
    {
        min_dx = dx_23;
        max_dx = dx_13;
    }
    else
    {
        min_dx = dx_13;
        max_dx = dx_23;
    }

    //растеризация нижнего треугольника
    for (int y = middle_point.get_y() + 1; y <= max_point.get_y(); y++)
    {
        std::vector<Point<int>> temp;
        resize_array = (int)max_fixed_x - (int)min_fixed_x;

        if (resize_array == 0){
            temp.push_back(Point<int>((int)min_fixed_x, y, 0));
        }
        else{
            for (int x = min_fixed_x; x < max_fixed_x; x += 1){
                temp.push_back(Point<int>(x, y, 0));
            }
        }
        rasterized_points.push_back(temp);

        min_fixed_x += min_dx;
        max_fixed_x += max_dx;
    }

    //std::cout << "rasterized_points[0][0] = "; rasterized_points[0][0].output_point();
    return rasterized_points;
}

void find_min_point(Point<double> &point_1, Point<double> &point_2,
                                Point<double> &point_3, Point<double> &min_point)
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
                                 Point<double> &point_3, Point<double> &max_point)
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

void find_middle_point(Point<double> &middle_point, Point<double> &min_point, Point<double> &max_point,
                                     Point<double> &point_1, Point<double> &point_2, Point<double> &point_3)
{
    double y_middle = 0;
    int is_middle = 0; //если сторона || оси Оу
    if (point_1.get_y() != min_point.get_y()){
        if(point_1.get_y() != max_point.get_y()){
            middle_point.set_point(point_1.get_x(), point_1.get_y(), 0);
            is_middle = 1;
        }
    }

    if (point_2.get_y() != min_point.get_y()){
        if(point_2.get_y() != max_point.get_y()){
             middle_point.set_point(point_2.get_x(), point_2.get_y(), 0);
             is_middle = 1;
        }
    }

    if (point_3.get_y() != min_point.get_y()){
        if(point_3.get_y() != max_point.get_y()){
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
    //std::cout << "input points: ";
    //point_1.output_point();
    //point_2.output_point();
    //point_3.output_point();
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

    //std::cout << "Got equation: "  << plane_koeffs.a << "x, " << plane_koeffs.b << "y, " << plane_koeffs.c << "z, " << plane_koeffs.d << std::endl;
}

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                           std::vector<std::vector<Point<int>>> &rasterized_points,
                                           plane_koeffs_t &plane_koeffs)
{
    double z = 0;
    int rasterize_x = 0, rasterize_y = 0;
    int size_row = rasterized_points.size(), size_column = 0;
    //std::cout << "size_row = " << size_row << std::endl;
    //std::cout << "size_column = " << size_column << std::endl;
    for (int i = 0; i < size_row; i++)
    {
        size_column = rasterized_points[i].size();
        for (int j = 0; j < size_column; j++)
        {
            rasterize_x = rasterized_points[i][j].get_x();
            rasterize_y = rasterized_points[i][j].get_y();
            std::cout << "rasterize_x = " << rasterize_x;
            std::cout << " rasterize_y = " << rasterize_y << std::endl;
            z = calculate_depth(rasterize_x, rasterize_y, plane_koeffs, zbuffer_matrix[rasterize_x][rasterize_y]);
            //std::cout << "z = " << z << std::endl;
            //std::cout << "z = " << z << std::endl;
            //std::cout << "rasterize_x = " << rasterize_x << " rasterize_y = " << rasterize_y << std::endl;
            //std::cout << "zbuffer_matrix[rasterize_x][rasterize_y] = " << zbuffer_matrix[rasterize_x][rasterize_y] << std::endl;
            if (z > zbuffer_matrix[rasterize_x][rasterize_y])
            {

                zbuffer_matrix[rasterize_x][rasterize_y] = z;
                //std::cout << "here" << std::endl;
                //std::cout << "zbuffer_matrix[rasterize_x][rasterize_y] = " << zbuffer_matrix[rasterize_x][rasterize_y] << std::endl;

                //std::cout << "color.\n";
                //color_matrix[rasterize_x][rasterize_y].setRgb(0, 0, 0);
                //std::cout << "end_if_color.\n";
                if (j == 0 || j == size_column - 1){
                    //std::cout << "here_color" << std::endl;
                    color_matrix[rasterize_x][rasterize_y].setRgb(0, 0, 0);
                    //std::cout << "color_matrix[rasterize_x][rasterize_y] =" << color_matrix[rasterize_x][rasterize_y].name() << std::endl;
                }
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
