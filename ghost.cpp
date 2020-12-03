#include "ghost.h"

Ghost::Ghost(QObject *parent, std::string sprite_name, int x, int y) : QObject(parent) {

    sprite_timer = new QTimer();
    pixmap = new QPixmap(sprite_name.c_str());

    posx = x;
    posy = y;
    Sposx = x;
    Sposy = y;
    setPos(Sposx, Sposy);

    x_dir = "NA";
    y_dir = "NA";

    state = false;

    velocity = 4;

    width = 14;
    height = 13;

    i = 0;
    j = 0;

    sprite_timer->start(150);
}
Ghost::~Ghost() {
    delete pixmap;
    delete sprite_timer;
}

QRectF Ghost::boundingRect() const {

    return  QRectF(-width/2, -height/2, width, height);
}
void Ghost::paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget) {

    painter->drawPixmap(-width/2, -height/2, *pixmap, i, j, width, height);
}

int Ghost::getPosx() const {
    return posx;
}
int Ghost::getPosy() const {
    return posy;
}

std::string Ghost::getX_dir() const {
    return x_dir;
}
std::string Ghost::getY_dir() const {
    return y_dir;
}

bool Ghost::getState() const {
    return state;
}

void Ghost::init() {
    state = true;

    posx = 336;
    posy = 816;
    setPos(336, 816);
}

void Ghost::reset() {
    x_dir = "NA";
    y_dir = "NA";

    state = false;

    posx = Sposx;
    posy = Sposy;
    setPos(Sposx, Sposy);
}

void Ghost::sprite_right() {

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
    x_dir = "Right";

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_right);

    posx += velocity;
    setPos(posx, posy);
}
void Ghost::move_left() {
    x_dir = "Left";

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_left);

    posx -= velocity;
    setPos(posx, posy);
}
void Ghost::move_up() {
    y_dir = "Up";

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_up);

    posy -= velocity;
    setPos(posx, posy);
}
void Ghost::move_down() {
    y_dir = "Down";

    disconnect(sprite_timer,0,0,0);
    connect(sprite_timer, &QTimer::timeout, this, &Ghost::sprite_down);

    posy += velocity;
    setPos(posx, posy);
}

void Ghost::move_x(std::string direction) {
    if(direction == "Right")
        bounce_right();
    else if (direction == "Left")
        bounce_left();

//    if(direction == "Left")
//        bounce_right();
//    else if (direction == "Right")
//        bounce_left();
}

void Ghost::move_y(std::string direction) {
    if(direction == "Up")
        bounce_up();
    else if (direction == "Down")
        bounce_down();

//    if(direction == "Down")
//        bounce_up();
//    else if (direction == "Up")
//        bounce_down();
}

void Ghost::bounce_right() {
    posx += velocity;
    setPos(posx, posy);
}
void Ghost::bounce_left() {
    posx -= velocity;
    setPos(posx, posy);
}
void Ghost::bounce_up() {
    posy -= velocity;
    setPos(posx, posy);
}
void Ghost::bounce_down() {
    posy += velocity;
    setPos(posx, posy);
}
