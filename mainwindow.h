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
#include <QMediaPlayer>
#include <QMessageBox>
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

    QTimer *collitions_timer;
    QTimer *bg_sound_timer;
    QTimer *init_timer;

    QList <Coin*> coins;
    QList <Wall*> walls;
    QList<Teleporter*> teleporters;
    QList<Ghost*> ghosts;

    QMediaPlayer *intro_sound;
    QMediaPlayer *death_sound;
    QMediaPlayer *bg_sound;
    QMediaPlayer *win_sound;
    QMediaPlayer *gameover_sound;

    Player *pacman;

    bool init;

    float x,y;
    float width, height;

public: //variables

private: //methods
    void keyPressEvent(QKeyEvent *event);

    void init_coins();
    QList<Coin*> delete_coins(QList <Coin*>, int pos);
    QList<Coin *> remove_initital_coins();

public: //methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void check_coin_collition();
    void check_wall_collition();
    void check_teleporter_collition();

    void check_collitions();

public slots:
    void play_bg_sound();
    void move_enemies();

};
#endif // MAINWINDOW_H
