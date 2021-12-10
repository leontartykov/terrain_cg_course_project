#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/line/line.hpp"
#include "driver/geometry/grid/grid.hpp"
#include "driver/landscape/landscape.hpp"
#include "driver/invisible/zbuffer.hpp"
//#include "driver/geometry/vector/vector_3.hpp"

//#include "driver/perlin/perlin.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    qDebug() << "Manwindow constructor.";
    ui->setupUi(this);

    view = ui->graphicsView;

    scene = new QGraphicsScene(ui->graphicsView);
    image = new QImage(SCREEN_WIDTH, SCREEN_HEIGHT, QImage::Format_A2RGB30_Premultiplied);
    image->fill(Qt::white);
    view->setScene(scene);

    init_landscape();

    QObject::connect(ui->spinbox_rotate_x, SIGNAL(valueChanged(int)), this, SLOT(rotate_landscape()));
    QObject::connect(ui->spinbox_rotate_y, SIGNAL(valueChanged(int)), this, SLOT(rotate_landscape()));
    QObject::connect(ui->spinbox_rotate_z, SIGNAL(valueChanged(int)), this, SLOT(rotate_landscape()));

    QObject::connect(ui->spinbox_octaves, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_amplitude, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_exp, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_frequency, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_frequency_x, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_frequency_y, SIGNAL(valueChanged(int)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_gain, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));
    QObject::connect(ui->spinbox_lacunarity, SIGNAL(valueChanged(double)), this, SLOT(change_noise_parametrs()));

    QObject::connect(ui->spinbox_width_landscape, SIGNAL(valueChanged(int)), this, SLOT(change_size_noise()));
    QObject::connect(ui->spinbox_height_landscape, SIGNAL(valueChanged(int)), this, SLOT(change_size_noise()));

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::init_landscape()
{
    qDebug() << "Init landscape.";
    landscape.set_meta_config(ui->spinbox_octaves->value(), ui->spinbox_frequency->value(), ui->spinbox_frequency->value(),
                                                ui->spinbox_exp->value() * 1000, ui->spinbox_frequency_x->value(), ui->spinbox_frequency_y->value(),
                                                ui->spinbox_gain->value(), ui->spinbox_lacunarity->value());

    qDebug() << "form_landscape.";
    landscape.form_landscape();

    qDebug() << "find_all_landscapes.";
    landscape.find_all_landscape_normals();
    qDebug() << "end_find_all_landscapes.";

    //landscape.output_normals();


    qDebug() << "find_average_normals_of_each_node().";
    landscape.find_average_normals_of_each_node();
    landscape.set_rotate_angles(ui->spinbox_rotate_x->value(), ui->spinbox_rotate_y->value(), ui->spinbox_rotate_z->value());


    rotate_t rotate_angles;
    rotate_angles.angle_x = ui->spinbox_rotate_x->value();
    rotate_angles.angle_y = ui->spinbox_rotate_y->value();
    rotate_angles.angle_z = ui->spinbox_rotate_z->value();

    qDebug() << "rotate_landscape.";
    landscape.rotate_landscape(rotate_angles);

    qDebug() << "transform_points_to_screen.";
    landscape.transform_points_to_screen();

    qDebug() << "remove_invisible_lines.";
    landscape.remove_invisible_lines(zbuffer, scene, light.get_position());

    qDebug() << "draw_landscape.";
    landscape.draw_landscape(zbuffer, scene, image);
}

void MainWindow::rotate_landscape()
{
    // Здесь можно вызвать нужный метод объекта landscape
    image->fill(qRgb(255,255,255));
    scene->items().clear();

    rotate_t rotate_angles, rotate_angles_landscape = landscape.get_rotate_angles();
    rotate_angles.angle_x = ui->spinbox_rotate_x->value() -  landscape.get_rotate_x();
    rotate_angles.angle_y = ui->spinbox_rotate_y->value() - landscape.get_rotate_y();
    rotate_angles.angle_z = ui->spinbox_rotate_z->value() - landscape.get_rotate_z();
    landscape.set_rotate_angles(landscape.get_rotate_x() + rotate_angles.angle_x,
                                                  landscape.get_rotate_y() + rotate_angles.angle_y,
                                                  landscape.get_rotate_z() + rotate_angles.angle_z);
    //landscape.output_rotate_angles();

    zbuffer.clear();

    landscape.rotate_landscape(rotate_angles);
    landscape.transform_points_to_screen();
    landscape.remove_invisible_lines(zbuffer, scene, light.get_position());
    landscape.draw_landscape(zbuffer, scene, image);
}

void MainWindow::change_noise_parametrs()
{
    //qDebug() << "change_noise";
    meta_data_t meta_data;
    meta_data.octaves = ui->spinbox_octaves->value();
    meta_data.amplitude = ui->spinbox_amplitude->value();
    meta_data.exponent = ui->spinbox_exp->value() * 1000;
    meta_data.frequency = ui->spinbox_frequency->value();
    meta_data.frequency_x = ui->spinbox_frequency_x->value();
    meta_data.frequency_y = ui->spinbox_frequency_y->value();
    meta_data.gain = ui->spinbox_gain->value();
    meta_data.lacunarity = ui->spinbox_lacunarity->value();

    landscape.set_meta_data(meta_data);
    zbuffer.clear();
    //landscape.clear();

    init_landscape();
}

void MainWindow::change_size_noise()
{
    int width = ui->spinbox_width_landscape->value(), height = ui->spinbox_height_landscape->value();
    //qDebug() << "width = " << width;
    //landscape = Landscape(width, height);
    landscape.clear();
    landscape.change_size(width, height);
    zbuffer.clear();
    init_landscape();
    //landscape.change_size(width, height);
}
