#ifndef _REQUEST_H_
#define _REQUEST_H_

#include <QGraphicsScene>

#include "driver/geometry/point.h"

class DrawerMediator
{
private:
    QGraphicsScene *scene;

public:
    explicit drawer_mediator(QGraphicsScene *scene);
    void draw_line(const Point);
};

#endif
