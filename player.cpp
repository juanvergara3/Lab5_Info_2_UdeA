#include "player.h"

std::string Player::getDir() const
{
    return dir;
}

Player::Player(QObject *parent) : QObject(parent) {

    posx = 335;
    posy = 815;
    this->setPos(posx, posy);

    velocity = 10;

    score = 0;

    i = 0;
    j = 0;
    width = 14;
    height = 13;

    sprite_timer = new QTimer();
    pixmap = new QPixmap(":/assets/sprites/pacman.png");
    movement_timer = new QTimer();

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

void Player::add_score(int value) {
    score += value;
}
int Player::get_score(){
    return score;
}

void Player::update_sprite() {

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
    dir = "Right";

    posx += velocity;
    setPos(posx, posy);
}
void Player::move_left() {
    dir = "Left";

    posx -= velocity;
    setPos(posx, posy);
}
void Player::move_up() {
    dir = "Up";

    posy -= velocity;
    setPos(posx, posy);
}
void Player::move_down() {
    dir = "Down";

    posy += velocity;
    setPos(posx, posy);
}

void Player::bounce_right() {
    posx += velocity;
    setPos(posx, posy);
}
void Player::bounce_left() {
    posx -= velocity;
    setPos(posx, posy);
}
void Player::bounce_up() {
    posy -= velocity;
    setPos(posx, posy);
}
void Player::bounce_down() {
    posy += velocity;
    setPos(posx, posy);
}
