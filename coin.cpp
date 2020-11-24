#include "coin.h"

Coin::Coin(QObject *parent) : QObject(parent) {
    posx = 400;
    posy = 400;
    setPos(posx,posy);

    width = 6;
    height = 6;
    pixmap = new QPixmap(":/assets/sprites/coin.png");
}

Coin::Coin(QObject *parent, int x, int y) {
    posx = x;
    posy = y;
    setPos(posx,posy);

    width = 6;
    height = 6;
    pixmap = new QPixmap(":/assets/sprites/coin.png");
}

Coin::~Coin() {
    delete pixmap;
}

QRectF Coin::boundingRect() const {
    return QRectF(-width/2, -height/2, width, height);
}

void Coin::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget){
    painter->drawPixmap(-width/2, -height/2, *pixmap, 0, 0, width, height);
}
