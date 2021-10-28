#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);

    view->setScene(scene);

    Polygon polygon({Point<double>(100, 100, 0), Point<double>(500, 100, 0.0),\
                                Point<double>(500, 700, 0.0), Point<double>(100, 700, 0.0)});
    int size_polygon = polygon.get_amount();
    for (int i =0; i < size_polygon - 1; ++i){
        scene->addLine(polygon[i].get_x(), polygon[i].get_y(), polygon[i+1].get_x(), polygon[i+1].get_y());
    }
    scene->addLine(polygon[size_polygon - 1].get_x(), polygon[size_polygon - 1].get_y(),
                              polygon[0].get_x(), polygon[0].get_y());
    /*scene->addLine(100, 100, 500, 100);
    scene->addLine(500, 100, 500, 700);
    scene->addLine(500, 700, 100, 700);
    scene->addLine(100, 700, 100, 100);*/
    //scene->addPolygon()

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

