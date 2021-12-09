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
    ui->setupUi(this);

    _view = std::make_unique<QGraphicsView>(ui->graphicsView);

    _scene = std::unique_ptr<QGraphicsScene>(new QGraphicsScene(ui->graphicsView));
    _image = std::unique_ptr<QImage>(new QImage(SCREEN_WIDTH, SCREEN_HEIGHT, QImage::Format_A2RGB30_Premultiplied));
    _image->fill(Qt::white);
    _view->setScene(_scene.get());

    init_landscape();

    QObject::connect(ui->spinbox_rotate_x, SIGNAL(valueChanged(int)), this, SLOT(rotate_landscape_x()));
    _view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::init_landscape()
{
    landscape.set_meta_config(ui->spinbox_octaves->value(), ui->spinbox_frequency->value(), ui->spinbox_frequency->value(),
                                                ui->spinbox_exp->value(), ui->spinbox_frequency_x->value(), ui->spinbox_frequency_y->value(),
                                                ui->spinbox_gain->value(), ui->spinbox_lacunarity->value());
    landscape.form_landscape();
    //landscape.output_landscape();
    landscape.find_all_landscape_normals();
    //landscape.output_normals();
    landscape.find_average_normals_of_each_node();
    landscape.set_rotate_angles(ui->spinbox_rotate_x->value(), ui->spinbox_rotate_y->value(), ui->spinbox_rotate_z->value());

    rotate_t rotate_angles;
    rotate_angles.angle_x = ui->spinbox_rotate_x->value();
    rotate_angles.angle_y = ui->spinbox_rotate_y->value();
    rotate_angles.angle_z = ui->spinbox_rotate_z->value();

    landscape.rotate_landscape(rotate_angles);
    landscape.transform_points_to_screen();
    landscape.remove_invisible_lines(zbuffer, _scene, light.get_position());
    landscape.draw_landscape(zbuffer, _scene, _image);
    _scene->addPixmap(QPixmap::fromImage(*_image));
}

void MainWindow::rotate_landscape_x()
{
    // Здесь можно вызвать нужный метод объекта landscape
    _image.get()->fill(qRgb(255,255,255));
    _scene.get()->items().clear();

    rotate_t rotate_angles, rotate_angles_landscape = landscape.get_rotate_angles();
    rotate_angles.angle_x = ui->spinbox_rotate_x->value() - rotate_angles_landscape.angle_x;
    rotate_angles.angle_y = ui->spinbox_rotate_y->value() - rotate_angles_landscape.angle_y;
    rotate_angles.angle_z = ui->spinbox_rotate_z->value() - rotate_angles_landscape.angle_z;
    qDebug() << "rotate_angles_x = " << rotate_angles.angle_x << "rotate_angles_y = " << rotate_angles.angle_y << "rotate_angles_z = " << rotate_angles.angle_z;
    //qDebug() << "new_angle_x = " <<
    zbuffer = ZBuffer{};

    landscape.rotate_landscape(rotate_angles);
    landscape.transform_points_to_screen();
    landscape.remove_invisible_lines(zbuffer, _scene, light.get_position());
    landscape.draw_landscape(zbuffer, _scene, _image);

    _scene->addPixmap(QPixmap::fromImage(*_image));
}
