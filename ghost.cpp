#include "ghost.h"

Ghost::Ghost(QObject *parent, std::string sprite_name) : QObject(parent) {

    timer = new QTimer();
    pixmap = new QPixmap(sprite_name.c_str());

    //dimensiones del sprite
    width = 14;
    height = 13;

    i = 0;
    j = 0;

    timer->start(150);
    connect(timer, &QTimer::timeout, this, &Ghost::update_sprite);

}

Ghost::~Ghost() {
    delete pixmap;
    delete timer;
}

QRectF Ghost::boundingRect() const {

    return  QRectF(-width/2, -height/2, width, height);
}

void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {

    painter->drawPixmap(-width/2, -height/2, *pixmap, i, j, width, height);
}

void Ghost::update_sprite() { //this needs some work
    i += 14;

    if(i >= 112){
        i = 0;
    }
    this->update(-width/2, -height/2, width, height);
}

void Ghost::setPosx(int value)
{

}

void Ghost::setPosy(int value)
{

}

