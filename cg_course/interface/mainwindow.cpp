#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point/point.hpp"
#include "driver/geometry/grid/grid.h"
#include "driver/geometry/line/line.h"
#include "driver/geometry/line/line.hpp"
#include "driver/geometry/grid/grid.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);

    view->setScene(scene);

    Grid3D grid;

    rotate_t rotate_angles = {40, 40, 0};

    Line line(Point<double>(0, 0, 0), Point<double>(1,1,0));
    scene->addLine(line.get_start_point().get_x(), line.get_start_point().get_y(), line.get_end_point().get_x(), line.get_end_point().get_y());

    grid.rotate_grid(rotate_angles);
    grid.draw_grid(scene);

    Grid3D grid_2;
    double **new_z_grid = grid_2.create_z_grid(4);
    fill_z_grid(&new_z_grid, 4);
    output_matrix(new_z_grid, 4);

    draw_new_z_grid(new_z_grid, scene);

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

