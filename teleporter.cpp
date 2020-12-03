#include "teleporter.h"

Teleporter::Teleporter(QObject *parent, int x, int y, int dx, int dy, int w, int h) {
    posx = x;
    posy = y;
    desx = dx;
    desy = dy;
    width = w;
    height = h;

    setPos(posx, posy);
}

QRectF Teleporter::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}
void Teleporter::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {
    //painter->setBrush(Qt::green);
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

int Teleporter::getDesx() const {
    return desx;
}
int Teleporter::getDesy() const {
    return desy;
}
