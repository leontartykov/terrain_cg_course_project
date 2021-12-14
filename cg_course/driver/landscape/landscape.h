#ifndef _LANDSCAPE_H_
#define _LANDSCAPE_H_

#include <vector>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QImage>

#include "driver/geometry/point/point.h"
#include "driver/geometry/figure/figure.h"
#include "driver/geometry/line/line.h"
#include "driver/invisible/zbuffer.h"
#include "driver/geometry/vector/vector.h"

typedef struct meta_data meta_data_t;
struct meta_data
{
    int octaves;
    double gain;
    double lacunarity;

    int seed;
    double frequency;
};

class Landscape
{
private:
    std::vector<std::vector<Point<double>>> _start_points;
    std::vector<std::vector<Point<double>>> _points;
    std::vector<std::vector<Point<double>>> _screen_points;
    std::vector<std::vector<Vector3D<int>>> _normals_up_triangles;
    std::vector<std::vector<Vector3D<int>>> _normals_down_triangles;
    std::vector<std::vector<Vector3D<double>>> _shading_normals;

    rotate_t _rotate_landscape_angles;
    meta_data_t _meta_config;
    int _width, _height;
    double _scale;
    Point<double> _center_figure_point;

    void fill_base(ZBuffer &zbuffer, std::vector<rasterised_points_t> &edge);
    void fill_boards(ZBuffer &zbuffer, Point<int> &point);

public:
    Landscape();
    Landscape(int width, int height);
    ~Landscape();

    void form_landscape();
    void transform_points_to_screen();
    void draw_landscape(ZBuffer &zbuffer, QGraphicsScene *scene, QGraphicsView *view);
    void remove_invisible_lines(ZBuffer &zbuffer, QGraphicsScene *scene, Vector3D<int> light_position);

    void output_landscape();
    void output_screen_landscape();

    void rotate_landscape(rotate_t &diff_rotate_angles);
    void scale_landscape();

    Point<double> &get_point(int index_i, int index_j);
    Point<double> &get_screen_point(int index_i, int index_j);

    void find_all_landscape_normals();
    void find_average_normals_of_each_node();
    int get_width();
    int get_height();

    void output_normals();
    void output_shading_normals();
    Vector3D<double> find_shading_normals(std::vector<Vector3D<int>> &normals, int i, int j);

    rotate_t get_rotate_angles();
    void set_rotate_angles(int angle_x, int angle_y, int angle_z);
    void set_meta_config(int octaves, double gain, double lacunarity, int seed, double frequency);

    void output_rotate_angles();
    int get_rotate_x();
    int get_rotate_y();
    int get_rotate_z();

    void set_meta_data(meta_data_t meta_data);
    void clear();

    void change_size(int width, int height);
    void resize(int width, int height);

    void make_base(ZBuffer &zbuffer, QGraphicsScene *scene);
    void find_base_normals();
    void clear_normals();
    void set_scale_landscape(double scale);
    double get_scale_landscape();
    void add_point_values(double value);
    void substract_point_values(double value);
    Point<double> get_center_figure();
    void set_center_figure(Point<double> &point);
};

#endif
