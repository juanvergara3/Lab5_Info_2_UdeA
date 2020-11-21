#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
//#include <QGraphicsItem>
//#include <QPixmap>
#include <QPainter>

class Player : public QObject, public QGraphicsItem {
    Q_OBJECT
private: //variables
    int posx, posy, velocity;

    QTimer *sprite_timer;
    QPixmap *pixmap;

    float i, j;
    float width, height;

public: //variables
    QTimer *movement_timer;

public: //methods
    explicit Player(QObject *parent = nullptr);
    ~Player();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void setPosx(int value);
    void setPosy(int value);

    void move_right();
    void move_left();
    void move_up();
    void move_down();

signals:

public slots:
    void update_sprite();
    void setVelocity(int value);

};

#endif // PLAYER_H
