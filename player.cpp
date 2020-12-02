#include "player.h"

Player::Player(QObject *parent) : QObject(parent) {

    posx = 336;
    posy = 816;
    this->setPos(posx, posy);

    dir = "NA";

    velocity = 8;
    death_sprite_counter = 0;

    score = 0; //max 23000
    lives = 3;
    sprite_max_width = 70;

    i = 0;
    j = 0;
    width = 14;
    height = 13;

    sprite_timer = new QTimer();
    pixmap = new QPixmap(":/assets/sprites/pacman.png");
    movement_timer = new QTimer();

    movement_timer->start(60);

    sprite_timer->start(60);
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
std::string Player::getDir() const {
    return dir;
}
int Player::getLives() const {
    return lives;
}

void Player::update_sprite() {

    i += width;

    if(i >= sprite_max_width)
        i = 0;

    this->update(-width/2, -height/2, width, height);
}
void Player::update_death_sprite() {

    death_sprite_counter++;
    update_sprite();

    if(death_sprite_counter== 10){

        death_sprite_counter = 0;

        disconnect(sprite_timer,0,0,0);
        i = 0;
        width = 14;
        height = 13;
        sprite_max_width = 70;

        pixmap->load(":/assets/sprites/pacman.png");

        sprite_timer->stop();
        sprite_timer->start(60);
        connect(sprite_timer, &QTimer::timeout, this, &Player::update_sprite);

        posx = 336;
        posy = 816;
        this->setPos(posx, posy);
    }
}
void Player::death_animation() {

    dir =  "NA";

    disconnect(sprite_timer,0,0,0);
    disconnect(movement_timer,0,0,0);

    i = 0;
    width = 15;
    height = 9;
    sprite_max_width = 148;
    lives -= 1;

    pixmap->load(":/assets/sprites/death.png");

    sprite_timer->stop();
    sprite_timer->start(150);
    connect(sprite_timer, SIGNAL(timeout()), this, SLOT(update_death_sprite()));

}

void Player::setPosy(int value) {
    posy = value;
}
void Player::setPosx(int value) {
    posx = value;
}
int Player::getPosx() const {
    return posx;
}
int Player::getPosy() const {
    return posy;
}

void Player::reset(){
    dir = "NA";
    score = 0;
    lives = 3;

    disconnect(movement_timer,0,0,0);

    posx = 336;
    posy = 816;

    this->setPos(posx, posy);
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
