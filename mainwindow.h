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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public: //methods
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private: //variables
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsScene *title_pic;

    Player *pacman;
    Ghost *red;
    Ghost *pink;
    Ghost *blue;
    Ghost *orange;

    float x,y;
    float width, height;

    void keyPressEvent(QKeyEvent *event);
};
#endif // MAINWINDOW_H
