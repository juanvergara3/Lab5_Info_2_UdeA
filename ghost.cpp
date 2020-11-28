#include "ghost.h"

Ghost::Ghost(QObject *parent, std::string sprite_name, int x, int y) : QObject(parent) {

    sprite_timer = new QTimer();
    movement_timer = new QTimer();
    wall_collition = new QTimer();

    pixmap = new QPixmap(sprite_name.c_str());

    posx = x;
    posy = y;
    Sposx = x;
    Sposy = y;
    setPos(Sposx, Sposy);

    velocity = 10;

    //dimensiones del sprite
    width = 14;
    height = 13;

    i = 0;
    j = 0;

    sprite_timer->start(150);
    movement_timer->start(60);
    wall_collition->start();

}
Ghost::~Ghost() {
    delete pixmap;
    delete sprite_timer;
    delete movement_timer;
}

QRectF Ghost::boundingRect() const {

    return  QRectF(-width/2, -height/2, width, height);
}
void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {

    painter->drawPixmap(-width/2, -height/2, *pixmap, i, j, width, height);
}

void Ghost::test_init() { //just for testing

    connect(movement_timer, &QTimer::timeout, this, &Ghost::move_left);

}

void Ghost::reset()
{
    posx = Sposx;
    posy = Sposy;
    setPos(Sposx, Sposy);
}

void Ghost::sprite_right() { //this might need some work

    if(i < 0 || i > 28)
        i = 0;

    i += 14;

    if(i >= 28){
        i = 0;
    }
    this->update(-width/2, -height/2, width, height);
}
void Ghost::sprite_left() {

    if(i < 28 || i > 56)
        i = 28;

    i += 14;

    if(i >= 56){
        i = 28;
    }
    this->update(-width/2, -height/2, width, height);
}
void Ghost::sprite_up() {

    if(i < 56 || i > 84)
        i = 56;

    i += 14;

    if(i >= 84){
        i = 56;
    }
    this->update(-width/2, -height/2, width, height);
}
void Ghost::sprite_down() {

    if(i < 84 || i > 112)
        i = 84;

    i += 14;

    if(i >= 112){
        i = 84;
    }
    this->update(-width/2, -height/2, width, height);
}

void Ghost::setPosx(int value) {
    posx = value;
}
void Ghost::setPosy(int value) {
    posy = value;
}

void Ghost::move_right() {

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_right);

    posx += velocity;
    setPos(posx, posy);
}
void Ghost::move_left() {

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_left);

    posx -= velocity;
    setPos(posx, posy);
}
void Ghost::move_up() {

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_up);

    posy -= velocity;
    setPos(posx, posy);
}
void Ghost::move_down() {

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_down);

    posy += velocity;
    setPos(posx, posy);
}
