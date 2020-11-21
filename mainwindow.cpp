#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    title_pic = new QGraphicsScene;
    title_pic->setSceneRect(0,0,ui->title->width(),ui->title->height());
    title_pic->setBackgroundBrush((QPixmap(":/assets/sprites/title_screen.png").scaledToWidth(ui->title->width())));
    ui->title->setScene(title_pic);

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0, ui->game_screen->width(), ui->game_screen->height());
    scene->setBackgroundBrush(QPixmap(":/assets/sprites/map.png").scaledToWidth(ui->game_screen->width()));
    ui->game_screen->setScene(scene);

    pacman = new Player();
    red = new Ghost(nullptr, ":/assets/sprites/red.png");
    pink =  new Ghost(nullptr, ":/assets/sprites/pink.png");
    blue =  new Ghost(nullptr, ":/assets/sprites/blue.png");
    orange =  new Ghost(nullptr, ":/assets/sprites/orange.png");

    pacman->setScale(3);
    red->setScale(3);
    pink->setScale(3);
    blue->setScale(3);
    orange->setScale(3);

    scene->addItem(pacman);
    scene->addItem(red);
    scene->addItem(pink);
    scene->addItem(blue);
    scene->addItem(orange);

    pacman->setPos(200, 200);
    red->setPos(50, 50);
    pink->setPos(50, 100);
    blue-> setPos(100, 50);
    orange-> setPos(100, 100);
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
        pacman->setRotation(180);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_left);
    }

    else if(event->key() == Qt::Key_D){
        pacman->setRotation(0);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_right);
    }

    else if(event->key() == Qt::Key_W){
        pacman->setRotation(270);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_up);
    }
    else if(event->key() == Qt::Key_S){
        pacman->setRotation(90);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_down);
    }
}



MainWindow::~MainWindow() {
    delete pacman;
    delete red;
    delete pink;
    delete blue;
    delete orange;
    delete scene;
    delete title_pic;
    delete ui;

}

