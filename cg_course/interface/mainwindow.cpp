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

    rotate_t rotate_angles = {-40, -40, 0};

    grid.rotate_grid(rotate_angles);
    grid.draw_grid(scene);

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

