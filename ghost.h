#ifndef GHOST_H
#define GHOST_H

#include <QObject>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QPainter>

class Ghost : public QObject, public QGraphicsItem {
    Q_OBJECT

private: //variables
    int posx, posy, velocity;
    int Sposx, Sposy;

    std::string x_dir;
    std::string y_dir;

    bool state;

    float i, j;
    float width, height;

    QTimer *sprite_timer;
    QPixmap *pixmap;

public: //varibles

private: //methods

public: //methods
    explicit Ghost(QObject *parent = nullptr, std::string sprite_name = "", int x = 0, int y = 0);
    ~Ghost();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getPosx() const;
    int getPosy() const;

    std::string getX_dir() const;
    std::string getY_dir() const;

    void reset();
    bool getState() const;

public slots:
    void init();

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

    void bounce_right();
    void bounce_left();
    void bounce_up();
    void bounce_down();

};

#endif // GHOST_H
