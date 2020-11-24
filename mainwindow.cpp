#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->score_display->display(0);

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

    walls.push_back(new Wall(nullptr, 336, 16, 656, 16)); //top wall
    walls.push_back(new Wall(nullptr, 336, 848, 656, 16)); //bottom wall

    walls.push_back(new Wall(nullptr, 16, 216, 16, 382)); //left walls
    walls.push_back(new Wall(nullptr, 16, 648, 16, 384));

    walls.push_back(new Wall(nullptr, 656, 216, 16, 382)); //right walls
    walls.push_back(new Wall(nullptr, 656, 648, 16, 384));

    walls.push_back(new Wall(nullptr, 112, 112, 82, 82)); //top squares
    walls.push_back(new Wall(nullptr, 240, 112, 82, 82));
    walls.push_back(new Wall(nullptr, 432, 112, 82, 82));
    walls.push_back(new Wall(nullptr, 560, 112, 82, 82));


    for(int k = 0; k<walls.size(); k++)
        scene->addItem(walls.at(k));

    for(int i = 48; i < 650; i+= 32){
        for(int j = 48; j < 830; j+= 32){ //if it collides with a wall don't add it
            coins.push_back(new Coin(nullptr, i, j));
            coins.back()->setScale(3);
        }
    }

    for(int k = 0; k<coins.size(); k++)
        scene->addItem(coins.at(k));

    //also make it so u win when you pick all the coins up *********

    coin_collition_timer = new QTimer;
    coin_collition_timer->start(60);
    connect(coin_collition_timer, &QTimer::timeout, this, &MainWindow::check_coin_collition);

    wall_collition_timer = new QTimer;
    wall_collition_timer->start(60);
    connect(wall_collition_timer, &QTimer::timeout, this, &MainWindow::check_wall_collition);

}
MainWindow::~MainWindow() {
    delete pacman;
    delete red;
    delete pink;
    delete blue;
    delete orange;
    delete scene;
    delete title_pic;
    delete coin_collition_timer;
    delete  wall_collition_timer;
    delete ui;
}

void MainWindow::check_coin_collition(){

   for(int k = 0; k < coins.size(); k++){

       if(pacman->collidesWithItem(coins.at(k))){

           scene->removeItem(coins.at(k));
           coins = delete_coins(coins, k);
           pacman->add_score(100);
           ui->score_display->display(pacman->get_score());
       }
   }
}
void MainWindow::check_wall_collition() {
    for(int k = 0; k < walls.size(); k++){

        if(pacman->collidesWithItem(walls.at(k))){

            if(pacman->getDir() == "Right")
                pacman->bounce_left();
            else if (pacman->getDir() == "Left")
                pacman->bounce_right();
            else if (pacman->getDir() == "Up")
                pacman->bounce_down();
            else if (pacman->getDir() == "Down")
                pacman->bounce_up();

        }
    }
}

QList<Coin *> MainWindow::delete_coins(QList<Coin *> list, int pos) {

    QList<Coin*> aux;

    for(int k = 0; k < list.size(); k++)
        if(k != pos)
            aux.push_back(list.at(k));

    return aux;
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
