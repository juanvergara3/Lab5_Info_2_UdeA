#ifndef TELEPORTER_H
#define TELEPORTER_H

#include <QObject>
#include <QPainter>
#include <QGraphicsPixmapItem>

class Teleporter : public QObject, public QGraphicsItem {
    Q_OBJECT

private: //variables
    int posx, posy;
    int width, height;
    int desx, desy;

public: //variables

private: //methods

public:
    explicit Teleporter(QObject *parent = nullptr);
    Teleporter(QObject *parent = nullptr, int x = 0, int y = 0, int dx = 0, int dy = 0, int w = 0, int h = 0);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *options, QWidget *widget);

    int getDesx() const;
    int getDesy() const;

signals:



};

#endif // TELEPORTER_H
