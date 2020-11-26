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
#include "teleporter.h"

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
    QTimer *teleporter_collition_timer;

    QList <Coin*> coins;
    QList <Wall*> walls;
    QList<Teleporter*> teleporters;

    Player *pacman;
    Ghost *red;
    Ghost *pink;
    Ghost *blue;
    Ghost *orange;

    float x,y;
    float width, height;

public: //variables

private: //methods
    void keyPressEvent(QKeyEvent *event);

    QList<Coin*> delete_coins(QList <Coin*>, int pos);
    QList<Coin *> remove_initital_coins();

public: //methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void check_coin_collition();
    void check_wall_collition();
    void check_teleporter_collition();
};
#endif // MAINWINDOW_H
