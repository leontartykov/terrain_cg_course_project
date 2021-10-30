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

    rotate_t rotate_angles = {40, 40, 0};
    std::cout << "Начальная линия до поворота: " << std::endl;
    grid.get_start_line_grid().output_line();
    grid.set_start_line_grid(grid.get_start_line_grid().rotate_line(rotate_angles));
    std::cout << "Начальная линия после поворота: " << std::endl;
    grid.get_start_line_grid().output_line();

    std::cout << "Конечная линия до поворота: " << std::endl;
    grid.get_end_line_grid().output_line();
    grid.set_end_line_grid(grid.get_end_line_grid().rotate_line(rotate_angles));

    std::cout << std::endl << "Начальная линия после поворота: " << std::endl;
    grid.get_start_line_grid().output_line();
    std::cout << "Конечная линия после поворота: " << std::endl;
    grid.get_end_line_grid().output_line();

    Line screen_line_start(grid.get_start_line_grid().get_start_point(), grid.get_start_line_grid().get_end_point());
    Line screen_line_end(grid.get_end_line_grid().get_start_point(), grid.get_end_line_grid().get_end_point());

    transform_3d_into_2d(screen_line_start.get_start_point(), grid.get_start_line_grid().get_start_point());
    transform_3d_into_2d(screen_line_end.get_start_point(), grid.get_end_line_grid().get_start_point());
    transform_3d_into_2d(screen_line_start.get_end_point(), grid.get_start_line_grid().get_end_point());
    transform_3d_into_2d(screen_line_end.get_end_point(), grid.get_end_line_grid().get_end_point());
    std::cout << "Преобразованные в 2д точки 3д линии старта: " << std::endl;
    screen_line_start.output_line();
    std::cout << "Преобразованные в 2д точки 3д линии конца: " << std::endl;
    screen_line_end.output_line();

    scene->addLine(screen_line_start.get_start_point().get_x(), screen_line_start.get_start_point().get_y(),
                               screen_line_start.get_end_point().get_x(), screen_line_start.get_end_point().get_y());
    double start_x = screen_line_start.get_start_point().get_x(),
            end_x = screen_line_start.get_end_point().get_x(),
            start_y = screen_line_start.get_start_point().get_y(),
            end_y = screen_line_end.get_end_point().get_y();
    //double part = (grid.get_start_line_grid().get_line()[1].get_x() - grid.get_start_line_grid().get_line()[0].get_x()) / 7;
    double part = (end_x - start_x) / 7;
    std::cout << "Part = " << part << std::endl;

    std::cout << "Start x = " << start_x << std::endl;
    std::cout << "End x = " << end_x << std::endl;
    std::cout << "Start y = " << start_y << std::endl;
    std::cout << "End y = " << end_y << std::endl;

    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x, start_y, start_x, end_y);
        start_x += part;
    }

    /*start_x = screen_points_start.get_x();
    end_x = screen_points_end.get_x();
    start_y = screen_points_start.get_y();
    end_y = screen_points_end.get_y();

    std::cout << start_y << std::endl;
    std::cout << end_y << std::endl;

    part = (end_y - start_y) / 7;
    for (int i = 0; i < 8; i++)
    {
        scene->addLine(start_x, start_y, end_x, start_y);
        start_y += part;
    }*/


    view->show();
}

MainWindow::~MainWindow(){
    delete ui;
}

