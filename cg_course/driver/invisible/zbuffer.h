#ifndef _ZBUFFER_H_
#define _ZBUFFER_H_

#include <limits>
#include <vector>
#include <QColor>
#include <QGraphicsScene>
#include <cmath>
#include <QDebug>

#include "driver/geometry/point/point.h"
#include "driver/geometry/matrix/matrix.h"
#include "driver/geometry/vector/vector.h"
#include "driver/geometry/triangle/triangle.h"

typedef struct rasterised_points rasterised_points_t;
struct rasterised_points
{
    Vector2D point;
    double intensity;
};

typedef struct plane_koeffs_polygon plane_koeffs_t;
struct plane_koeffs_polygon
{
    int a;
    int b;
    int c;
    double d;
};

typedef struct edge edge_t;
struct edge
{
    int x;
    int y;
};

class ZBuffer: Matrix
{
private:
    std::vector<std::vector<double>> _zbuffer_matrix;
    std::vector<std::vector<QColor>> _color_matrix;

    int _width, _height;
public:
    ZBuffer();
    ZBuffer(int width, int height);
    ~ZBuffer();

    void output();
    double get_z_point(int index_i, int index_j) const;
    void set_z_point(double value, int index_i, int index_j);

    std::vector<std::vector<double>> &get_zbuffer_matrix();
    std::vector<std::vector<QColor>> &get_color_matrix();

    void set_color(int index_i, int index_j, QRgb rgb);

    double get_width();
    double get_height();

    bool is_background(int index_i, int index_j);

    void clear();
};

void calculate_equation_plane(plane_koeffs_t &plane_koeffs,
                                                 Point<double> point_1, Point<double> point_2,
                                                 Point<double>point_3);

void calculate_depth_pixels(std::vector<std::vector<double>> &zbuffer_matrix,
                                            std::vector<std::vector<QColor>> &color_matrix,
                                            std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                            plane_koeffs_t &plane_koeffs, Vector3D<int> &light_position,
                                            Triangle<double>&triangle_normals, Triangle<double>points_3d);

Point<int> rasterize_triangle(std::vector<std::vector<rasterised_points_t>> &rasterized_points,
                                    Triangle<double>&triangle_normals,
                                    Vector3D<int> &light_position, Point<double> &point_1, Point<double> &point_2, Point<double> &point_3,
                                    QGraphicsScene *scene, std::vector<std::vector<QColor>> &colors);

#endif
