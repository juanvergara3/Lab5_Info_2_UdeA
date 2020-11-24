#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
//#include <QGraphicsItem>
//#include <QPixmap>
#include <QPainter>

class Ghost : public QObject, public QGraphicsItem {
    Q_OBJECT

private: //variables
    int posx, posy, velocity;

    float i, j;
    float width, height;

    QTimer *sprite_timer;
    QTimer *movement_timer;
    QPixmap *pixmap;

public: //varibles

private: //methods

public: //methods
    explicit Ghost(QObject *parent = nullptr, std::string sprite_name = "");
    ~Ghost();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    void test_init();

signals:

public slots:
    void sprite_right();
    void sprite_left();
    void sprite_up();
    void sprite_down();

    void setPosx(int value);
    void setPosy(int value);

    void move_right();
    void move_left();
    void move_up();
    void move_down();

};

#endif // GHOST_H
