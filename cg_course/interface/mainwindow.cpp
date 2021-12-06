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

    Line line(Point<double>(0, 0, 0), Point<double>(1,1,0));
    scene->addLine(line.get_start_point().get_x(), line.get_start_point().get_y(),
                               line.get_end_point().get_x(), line.get_end_point().get_y());

    //grid.rotate(rotate_angles);
    //grid.draw_grid(scene);

    ZBuffer zbuffer(SCREEN_WIDTH, SCREEN_HEIGHT);

    landscape.form_landscape();
    //landscape.output_landscape();
    landscape.find_all_landscape_normals();
    //landscape.output_normals();
    landscape.find_average_normals_of_each_node();
    //landscape.output_shading_normals();

    landscape.rotate_landscape(rotate_landscape_angles);
    landscape.transform_points_to_screen();
    landscape.remove_invisible_lines(zbuffer, scene, light.get_position());
    //light.adjust_illumination(zbuffer);

    landscape.draw_landscape(zbuffer, scene, image);
    // Пример создания сигнал-слот соединения
    QObject::connect(ui->spinbox_rotate_x, SIGNAL(valueChanged(int)), this, SLOT(rotate_landscape_x()));
    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::rotate_landscape_x()
{
    // Здесь можно вызвать нужный метод объекта landscape
    qDebug() << ui->spinbox_rotate_x->value();
    rotate_t rotate_landscape_angles = {60, 0, 10};
    landscape.rotate_landscape(rotate_landscape_angles);
}
