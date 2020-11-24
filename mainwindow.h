#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsItem>
#include <QRectF>
#include <QDesktopWidget>
#include <QtDebug>
#include <QKeyEvent>
#include "player.h"
#include "ghost.h"
#include "coin.h"
#include "wall.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private: //variables
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *title_pic;

    QTimer *coin_collition_timer;
    QTimer *wall_collition_timer;

    Player *pacman;
    Ghost *red;
    Ghost *pink;
    Ghost *blue;
    Ghost *orange;

    QList <Coin*> coins;
    QList <Wall*> walls;

    float x,y;
    float width, height;

public: //variables

private: //methods
    void keyPressEvent(QKeyEvent *event);
    QList<Coin*> delete_coins(QList <Coin*>, int pos);

public: //methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void check_coin_collition();
    void check_wall_collition();
};
#endif // MAINWINDOW_H
