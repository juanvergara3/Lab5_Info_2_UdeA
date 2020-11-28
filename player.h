#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
//#include <QGraphicsItem>
//#include <QPixmap>
#include <QPainter>
#include <QThread>

class Player : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy, velocity;

    std::string dir;

    int score;
    int lives;
    int sprite_max_width;

    float i, j;
    float width, height;

    QTimer *sprite_timer;
    QPixmap *pixmap;

public: //variables
    QTimer *movement_timer;
    int death_sprite_counter;

private: //methods

public: //methods
    explicit Player(QObject *parent = nullptr);
    ~Player();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void add_score(int value);
    int get_score();
    int getLives() const;

    void setPosx(int value);
    void setPosy(int value);

    void reset();

    void move_right();
    void move_left();
    void move_up();
    void move_down();

    void bounce_right();
    void bounce_left();
    void bounce_up();
    void bounce_down();

    std::string getDir() const;

signals:

public slots:
    void update_sprite();
    void update_death_sprite();
    void death_animation();
    void setVelocity(int value);

};

#endif // PLAYER_H
