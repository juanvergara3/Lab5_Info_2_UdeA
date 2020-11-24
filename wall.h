#ifndef WALL_H
#define WALL_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Wall : public QObject, public QGraphicsItem {
    Q_OBJECT

private: //variables
    int posx, posy;
    int width, height;

public: //variables

private: //methods

public:
    explicit Wall(QObject *parent = nullptr);
    Wall(QObject *parent = nullptr, int x = 0, int y = 0, int w = 0, int h = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

signals:

};

#endif // WALL_H
