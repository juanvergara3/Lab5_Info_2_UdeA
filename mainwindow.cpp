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

    /*------WALLS------*/

    walls.push_back(new Wall(nullptr, 336, 16, 656, 16)); //top wall
    walls.push_back(new Wall(nullptr, 336, 86, 16, 124));
    walls.push_back(new Wall(nullptr, 336, 848, 656, 16)); //bottom wall

    walls.push_back(new Wall(nullptr, 16, 216, 16, 382)); //left walls
    walls.push_back(new Wall(nullptr, 16, 648, 16, 384));

    walls.push_back(new Wall(nullptr, 656, 216, 16, 382)); //right walls
    walls.push_back(new Wall(nullptr, 656, 648, 16, 384));

    walls.push_back(new Wall(nullptr, 112, 112, 82, 82)); //top squares
    walls.push_back(new Wall(nullptr, 240, 112, 82, 82));
    walls.push_back(new Wall(nullptr, 432, 112, 82, 82));
    walls.push_back(new Wall(nullptr, 560, 112, 82, 82));

    walls.push_back(new Wall(nullptr, 88, 352, 126, 112)); //middle left squares
    walls.push_back(new Wall(nullptr, 88, 512, 126, 112));

    walls.push_back(new Wall(nullptr, 584, 352, 126, 112)); //middle right squares
    walls.push_back(new Wall(nullptr, 584, 512, 126, 112));

    walls.push_back(new Wall(nullptr, 336, 224, 148, 48)); //top rectangles
    walls.push_back(new Wall(nullptr, 336, 278, 16, 58));
    walls.push_back(new Wall(nullptr, 112, 224, 84, 48));
    walls.push_back(new Wall(nullptr, 560, 224, 84, 48));

    walls.push_back(new Wall(nullptr, 336, 544, 148, 48)); //bottom rectangles
    walls.push_back(new Wall(nullptr, 336, 598, 16, 58));
    walls.push_back(new Wall(nullptr, 336, 704, 148, 48));
    walls.push_back(new Wall(nullptr, 336, 758, 16, 58));
    walls.push_back(new Wall(nullptr, 56, 704, 64, 48));
    walls.push_back(new Wall(nullptr, 616, 704, 64, 48));

    walls.push_back(new Wall(nullptr, 272, 416, 16, 112)); //ghost's cage
    walls.push_back(new Wall(nullptr, 400, 416, 16, 112));
    walls.push_back(new Wall(nullptr, 336, 464, 112, 16));
    walls.push_back(new Wall(nullptr, 294, 368, 26, 16));
    walls.push_back(new Wall(nullptr, 378, 368, 26, 16));

    walls.push_back(new Wall(nullptr, 206, 512, 16, 112)); //other walls
    walls.push_back(new Wall(nullptr, 464, 512, 16, 112));

    walls.push_back(new Wall(nullptr, 206, 304, 16, 206));
    walls.push_back(new Wall(nullptr, 464, 304, 16, 206));
    walls.push_back(new Wall(nullptr, 246, 304, 58, 16));
    walls.push_back(new Wall(nullptr, 424, 304, 58, 16));

    walls.push_back(new Wall(nullptr, 240, 624, 72, 16));
    walls.push_back(new Wall(nullptr, 432, 624, 72, 16));

    walls.push_back(new Wall(nullptr, 112, 624, 82, 16));
    walls.push_back(new Wall(nullptr, 560, 624, 82, 16));
    walls.push_back(new Wall(nullptr, 144, 678, 16, 90));
    walls.push_back(new Wall(nullptr, 526, 678, 16, 90));

    walls.push_back(new Wall(nullptr, 176, 784, 198, 16));
    walls.push_back(new Wall(nullptr, 496, 784, 198, 16));
    walls.push_back(new Wall(nullptr, 206, 730, 16, 92));
    walls.push_back(new Wall(nullptr, 466, 730, 16, 92));

    /*------COINS------*/

    for(int i = 48; i < 650; i+= 32){
        for(int j = 48; j < 830; j+= 32){ //if it collides with a wall don't add it
            coins.push_back(new Coin(nullptr, i, j));
            coins.back()->setScale(3);
        }
    }

    coins = remove_initital_coins();

   /*------TELEPORTERS------*/

   teleporters.push_back(new Teleporter(nullptr, 688,432, 0, 432, 64, 64));
   teleporters.push_back(new Teleporter(nullptr, -16,432, 672, 432, 64, 64));

   /*------ ADDING THEM TO THE SCENE ------*/

   for(int k = 0; k<walls.size(); k++)
       scene->addItem(walls.at(k));

   for(int k = 0; k<coins.size(); k++)
        scene->addItem(coins.at(k));

   for(int k = 0; k<teleporters.size(); k++)
        scene->addItem(teleporters.at(k));

   /*------TIMERS AND CONNECTIONS------*/

    coin_collition_timer = new QTimer;
    connect(coin_collition_timer, &QTimer::timeout, this, &MainWindow::check_coin_collition);
    coin_collition_timer->start(60);

    wall_collition_timer = new QTimer;
    connect(wall_collition_timer, &QTimer::timeout, this, &MainWindow::check_wall_collition);
    wall_collition_timer->start(60); //setting it to 30 removes bouncing

    teleporter_collition_timer = new QTimer;
    connect(teleporter_collition_timer, &QTimer::timeout, this, &MainWindow::check_teleporter_collition);
    teleporter_collition_timer->start(60);

    //commit: teleporters. closed coins on walls fixed. whatever we do with dolph

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
    delete  teleporter_collition_timer;
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

        if(pacman->collidesWithItem(walls.at(k), Qt::IntersectsItemBoundingRect)){

            disconnect(pacman->movement_timer,0,0,0);

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
void MainWindow::check_teleporter_collition() {
    for(int k = 0; k < teleporters.size(); k++){

        if(pacman->collidesWithItem(teleporters.at(k), Qt::ContainsItemBoundingRect)){

            pacman->setPosx(teleporters.at(k)->getDesx());
            pacman->setPosy(teleporters.at(k)->getDesy());
            pacman->setPos(teleporters.at(k)->getDesx(), teleporters.at(k)->getDesy());

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
QList<Coin *> MainWindow::remove_initital_coins() {

    QList<Coin*> aux;
    int count  = 0;

    for(int k = 0; k < coins.size(); k++){
        for(int w = 0; w<walls.size(); w++){
            if(!coins.at(k)->collidesWithItem(walls.at(w))){

                count++;

            }
        }

        if(count == walls.size() && !coins.at(k)->collidesWithItem(pacman))
            aux.push_back(coins.at(k));
        count = 0;
    }


    return aux;
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(event->key() == Qt::Key_A || event->key() == Qt::Key_Left){
        pacman->setRotation(180);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_left);
    }
    else if(event->key() == Qt::Key_D || event->key() == Qt::Key_Right){
        pacman->setRotation(0);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_right);
    }
    else if(event->key() == Qt::Key_W || event->key() == Qt::Key_Up){
        pacman->setRotation(270);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_up);
    }
    else if(event->key() == Qt::Key_S || event->key() == Qt::Key_Down){
        pacman->setRotation(90);

        pacman->disconnect(pacman->movement_timer,0,0,0);
        pacman->connect(pacman->movement_timer, &QTimer::timeout, pacman, &Player::move_down);
    }
}
