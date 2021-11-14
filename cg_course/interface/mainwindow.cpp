#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/line/line.hpp"
#include "driver/geometry/grid/grid.hpp"
#include "driver/landscape/landscape.hpp"
#include "driver/invisible/zbuffer.hpp"

//#include "driver/perlin/perlin.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);

    view->setScene(scene);

    Grid3D grid;

    rotate_t rotate_angles = {40, 40, 0},
                 rotate_landscape_angles = {0, 0, 0};


    rotate_landscape_angles.angle_x = ui->spinBox->value();
    rotate_landscape_angles.angle_y = ui->spinBox_2->value();
    rotate_landscape_angles.angle_z = ui->spinBox_3->value();
    std::cout << "rotate_angles.angle_x = " << rotate_angles.angle_x << std::endl;
    std::cout << "rotate_angles.angle_y = " << rotate_angles.angle_y << std::endl;

    Line line(Point<double>(0, 0, 0), Point<double>(1,1,0));
    scene->addLine(line.get_start_point().get_x(), line.get_start_point().get_y(),
                               line.get_end_point().get_x(), line.get_end_point().get_y());

    grid.rotate(rotate_angles);
    grid.draw_grid(scene);

    Landscape landscape_1;
    landscape_1.form_landscape();
    //std::cout << "Ususal points: " << std::endl;
    //landscape_1.output_landscape();
    landscape_1.rotate_landscape(rotate_landscape_angles);

    //std::cout << "Ususal points: " << std::endl;
    //landscape_1.output_landscape();

    landscape_1.draw_landscape(scene);
    //landscape_1.output_landscape();

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

