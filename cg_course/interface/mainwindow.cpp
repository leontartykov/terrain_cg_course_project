#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/line/line.hpp"
#include "driver/geometry/grid/grid.hpp"
#include "driver/landscape/landscape.hpp"
#include "driver/invisible/zbuffer.hpp"
//#include "driver/geometry/vector/vector_3.hpp"

//#include "driver/perlin/perlin.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)\
{
    ui->setupUi(this);
    Landscape landscape;
    rotate_t rotate_angles = {1, 10, 0},
                 rotate_landscape_angles = {60, 0, 10};

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);
    image = new QImage(1024, 754, QImage::Format_A2RGB30_Premultiplied);
    image->fill(Qt::white);

    view->setScene(scene);

    //Grid3D grid;

    Light light;
    light.set_ia(ui->spinbox_is->value());
    light.set_ka(ui->spinbox_ks->value());
    light.set_id(ui->spinbox_id->value());
    light.set_kd(ui->spinbox_kd->value());
    light.set_is(ui->spinbox_is->value());
    light.set_ks(ui->spinbox_ks->value());


    //rotate_landscape_angles.angle_x = ui->spinbox_rotate_x->value();
    //rotate_landscape_angles.angle_y = ui->spinbox_rotate_y->value();
    //rotate_landscape_angles.angle_z = ui->spinbox_rotate_z->value();

    Line line(Point<double>(0, 0, 0), Point<double>(1,1,0));
    scene->addLine(line.get_start_point().get_x(), line.get_start_point().get_y(),
                               line.get_end_point().get_x(), line.get_end_point().get_y());

    //grid.rotate(rotate_angles);
    //grid.draw_grid(scene);

    ZBuffer zbuffer(SCREEN_WIDTH, SCREEN_HEIGHT);

    landscape.form_landscape();
    landscape.find_all_landscape_normals();
    landscape.find_average_normals_of_each_node();
    landscape.rotate_landscape(rotate_landscape_angles);
    landscape.transform_points_to_screen();
    landscape.remove_invisible_lines(zbuffer, scene, light.get_position());
    //light.adjust_illumination(zbuffer);

    //int r = 0, g = 0, b = 0;
    //zbuffer.get_color_matrix()[100][250].getRgb(&r, &g, &b);
    //std::cout << "r = " << r << " g = " << g << " b = " << b <<std::endl;
    landscape.draw_landscape(zbuffer, scene, image);

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::rotate_landscape_x()
{
    qDebug() << ui->spinbox_rotate_x->value();
}
