#include "wall.h"

Wall::Wall(QObject *parent, int x, int y, int w, int h) {
    posx = x;
    posy = y;
    width = w;
    height = h;

    setPos(posx, posy);
}

QRectF Wall::boundingRect() const{
    return QRectF(-width/2, -height/2, width, height);
}
void Wall::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    //painter->setBrush(Qt::red);
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}
