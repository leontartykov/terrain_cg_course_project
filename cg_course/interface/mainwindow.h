#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QDebug>

#include "driver/geometry/polygon/polygon.h"
#include "driver/landscape/landscape.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QImage *image;
    QPixmap *pixmap;
    Landscape landscape; //  Сделал лендскейп членом класса. Иначе этот объект умирал при выходе из конструктора

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void rotate_landscape_x();
};
#endif // MAINWINDOW_H
