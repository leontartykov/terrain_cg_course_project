#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>
#include <QPixmap>
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QScreen>
#include <memory>

#include "driver/geometry/polygon/polygon.h"
#include "driver/landscape/landscape.h"
#include "driver/light/light.h"

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
    QPixmap pixmap;

    Landscape landscape; //  Сделал лендскейп членом класса. Иначе этот объект умирал при выходе из конструктора
    Light light;
    ZBuffer zbuffer;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init_landscape();

public slots:
    void rotate_landscape();
    void change_noise_parametrs();
    void change_size_noise();
};
#endif // MAINWINDOW_H
