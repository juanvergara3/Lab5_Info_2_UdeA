#include "player.h"

Player::Player(QObject *parent) : QObject(parent) {
    sprite_timer = new QTimer();
    movement_timer = new QTimer();
    pixmap = new QPixmap(":/assets/sprites/pacman.png");

    //dimensiones del sprite
    width = 14;
    height = 13;

    i = 0;
    j = 0;

    posx = 200;
    posy = 200;

    velocity = 10;
    movement_timer->start(60);

    sprite_timer->start(100);
    connect(sprite_timer, &QTimer::timeout, this, &Player::update_sprite);

}

Player::~Player() {
    delete pixmap;
    delete sprite_timer;
    delete movement_timer;
}

QRectF Player::boundingRect() const {

    return QRectF(-width/2, -height/2, width, height);
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {

    painter->drawPixmap(-width/2, -height/2, *pixmap, i, j, width, height);
}

void Player::update_sprite() { //this needs some work

    i += 14;

    if(i >= 70){
        i = 0;
    }
    this->update(-width/2, -height/2, width, height);
}

void Player::setVelocity(int value) {
    velocity = value;
}

void Player::setPosy(int value) {
    posy = value;
}

void Player::setPosx(int value) {
    posx = value;
}

void Player::move_right() {
    posx += velocity;
    setPos(posx, posy);
}

void Player::move_left() {
    posx -= velocity;
    setPos(posx, posy);
}

void Player::move_up() {
    posy -= velocity;
    setPos(posx, posy);
}

void Player::move_down() {
    posy += velocity;
    setPos(posx, posy);
}
