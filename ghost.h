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

private:
    int posx, posy, velocity;

    QTimer *timer;
    QPixmap *pixmap;

    float i, j;
    float width, height;

public:
    explicit Ghost(QObject *parent = nullptr, std::string sprite_name = "");
    ~Ghost();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

signals:
public slots:
    void update_sprite();

    void setPosx(int value);
    void setPosy(int value);

};

#endif // GHOST_H
