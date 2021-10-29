#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "driver/geometry/point.hpp"
#include "driver/geometry/grid.h"
#include "driver/geometry/line.hpp"
#include "driver/geometry/grid.hpp"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    view = ui->graphicsView;
    scene = new QGraphicsScene(ui->graphicsView);

    view->setScene(scene);

    Polygon polygon({Point<double>(100, 100, 0), Point<double>(500, 100, 0.0),
                                Point<double>(500, 700, 0.0), Point<double>(100, 700, 0.0)});
    int size_polygon = polygon.get_amount();
    /*for (int i =0; i < size_polygon - 1; ++i){
        scene->addLine(polygon[i].get_x(), polygon[i].get_y(), polygon[i+1].get_x(), polygon[i+1].get_y());
    }
    scene->addLine(polygon[size_polygon - 1].get_x(), polygon[size_polygon - 1].get_y(),
                              polygon[0].get_x(), polygon[0].get_y());*/

    Line line_1(Point<double>(10, 10, 0), Point<double>(400, 400, 0));
    scene->addLine(line_1.get_line()[0].get_x(), line_1.get_line()[0].get_y(),
                               line_1.get_line()[1].get_x(), line_1.get_line()[1].get_y());
    std::cout << "Координата x первой точки: " << line_1.get_line()[1].get_x() << std::endl;
    Grid3D grid;

    std::cout << grid.get_start_line_grid().get_line()[1].get_x() << std::endl;
    std::cout << grid.get_start_line_grid().get_line()[0].get_x() << std::endl;
    double part = (grid.get_start_line_grid().get_line()[1].get_x() - grid.get_start_line_grid().get_line()[0].get_x()) / 7;
    std::cout << "Part = " << part << std::endl;

    double start_x = grid.get_start_line_grid().get_line()[0].get_x(),
            end_x = grid.get_start_line_grid().get_line()[1].get_x(),
            start_y = grid.get_start_line_grid().get_line()[0].get_y(),
            end_y = grid.get_end_line_grid().get_line()[0].get_y();

    std::cout << "Start x = " << start_x << std::endl;
    std::cout << "End x = " << end_x << std::endl;
    std::cout << "Start y = " << start_y << std::endl;
    std::cout << "End y = " << end_y << std::endl;

    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x, start_y, start_x, end_y);
        start_x += part;
    }

    start_x = grid.get_start_line_grid().get_line()[0].get_x();
    end_x = grid.get_start_line_grid().get_line()[1].get_x();
    start_y = grid.get_start_line_grid().get_line()[0].get_y();
    end_y = grid.get_end_line_grid().get_line()[1].get_y();

    std::cout << start_y << std::endl;
    std::cout << end_y << std::endl;

    part = (end_y - start_y) / 7;
    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x, start_y, end_x, start_y);
        start_y += part;
    }

    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

