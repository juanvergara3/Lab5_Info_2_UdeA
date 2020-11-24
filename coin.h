#ifndef COIN_H
#define COIN_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPainter>


class Coin : public QObject, public QGraphicsItem {
    Q_OBJECT

private: //variables
    int posx, posy;
    float width, height;
    QPixmap *pixmap;

public: //variables

private: //methods

public: //methods
    explicit Coin(QObject *parent = nullptr);
    Coin(QObject *parent = nullptr, int x = 0, int y = 0);
    ~Coin();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

signals:

};

#endif // COIN_H
