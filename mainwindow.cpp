#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->score_display->display(0);
    ui->lives_display->setText("3");

    title_pic = new QGraphicsScene;
    title_pic->setSceneRect(0,0,ui->title->width(),ui->title->height());
    title_pic->setBackgroundBrush((QPixmap(":/assets/sprites/title_screen.png").scaledToWidth(ui->title->width())));
    ui->title->setScene(title_pic);

    ui->checkBox->setChecked(true);

    scene = new QGraphicsScene;
    scene->setSceneRect(0,0, ui->game_screen->width(), ui->game_screen->height());
    scene->setBackgroundBrush(QPixmap(":/assets/sprites/map.png").scaledToWidth(ui->game_screen->width()));
    ui->game_screen->setScene(scene);

    pacman = new Player();
    pacman->setScale(2.5);

    pop_up =  new QMessageBox;

    /*------GHOSTS------*/

    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/red.png", 310, 396));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/pink.png", 360, 396));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/blue.png", 310, 434));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/orange.png", 360, 434));

    for(int k = 0; k<ghosts.size(); k++)
         ghosts.at(k)->setScale(2.5);

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

    init_coins();

   /*------TELEPORTERS------*/

   teleporters.push_back(new Teleporter(nullptr, 688,432, 0, 432, 64, 64));
   teleporters.push_back(new Teleporter(nullptr, -16,432, 672, 432, 64, 64));

   /*------ ADDING THEM TO THE SCENE ------*/

   scene->addItem(pacman);

   for(int k = 0; k<walls.size(); k++)
       scene->addItem(walls.at(k));

   for(int k = 0; k<coins.size(); k++)
        scene->addItem(coins.at(k));

   for(int k = 0; k<teleporters.size(); k++)
        scene->addItem(teleporters.at(k));

   for(int k = 0; k<ghosts.size(); k++)
        scene->addItem(ghosts.at(k));

   /*------TIMERS AND CONNECTIONS------*/

//    coin_collition_timer = new QTimer;
//    connect(coin_collition_timer, &QTimer::timeout, this, &MainWindow::check_coin_collition);
//    coin_collition_timer->start(60);

//    wall_collition_timer = new QTimer;
//    connect(wall_collition_timer, &QTimer::timeout, this, &MainWindow::check_wall_collition);
//    wall_collition_timer->start(60);

//    teleporter_collition_timer = new QTimer;
//    connect(teleporter_collition_timer, &QTimer::timeout, this, &MainWindow::check_teleporter_collition);
//    teleporter_collition_timer->start(60);

   collitions_timer = new QTimer;
   connect(collitions_timer, &QTimer::timeout, this, &MainWindow::check_collitions);
   collitions_timer->start(60);

   bg_sound_timer = new QTimer;

    /*------SOUND------*/

    intro_sound = new QMediaPlayer;
    intro_sound->setMedia(QUrl("qrc:/assets/sound/intro.mp3"));
    intro_sound->setVolume(15);
    intro_sound->play();

    bg_sound = new QMediaPlayer;
    bg_sound->setMedia(QUrl("qrc:/assets/sound/waka.mp3"));
    bg_sound->setVolume(15);

    death_sound = new QMediaPlayer;
    death_sound->setMedia(QUrl("qrc:/assets/sound/death.mp3"));
    death_sound->setVolume(15);

    win_sound =  new QMediaPlayer;
    win_sound->setMedia(QUrl("qrc:/assets/sound/win.mp3"));
    win_sound->setVolume(15);

    gameover_sound = new QMediaPlayer;
    gameover_sound->setMedia(QUrl("qrc:/assets/sound/gameover.mp3"));
    gameover_sound->setVolume(15);

}
MainWindow::~MainWindow() {
    delete pacman;
    delete scene;
    delete title_pic;

//    delete coin_collition_timer;
//    delete  wall_collition_timer;
//    delete  teleporter_collition_timer;

    delete collitions_timer;
    delete pop_up;

    delete bg_sound_timer;
    delete bg_sound;
    delete death_sound;
    delete intro_sound;
    delete ui;
}

/*(void MainWindow::check_coin_collition(){
    if(pacman->get_score() < 23000){

        for(int k = 0; k < coins.size(); k++){

            if(pacman->collidesWithItem(coins.at(k))){

                scene->removeItem(coins.at(k));
                coins = delete_coins(coins, k);
                pacman->add_score(100);
                ui->score_display->display(pacman->get_score());
            }
        }
    }

    else if(pacman->get_score() == 23000){


        //win screen


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
    for(int k = 0; k<ghosts.size(); k++){ //remove this hit from here later

        if(pacman->collidesWithItem(ghosts.at(k))){ //just for testing

            for(int w = 0; w < ghosts.size(); w++)
                ghosts.at(k)->back_to_cage();

            disconnect(bg_sound_timer,0,0,0);
            bg_sound->stop();

            death_sound->play();

            pacman->setRotation(0);
            pacman->death_animation();

            ui->lives_display->setText(QString::number(pacman->getLives()));

            k = ghosts.size();
        }
    }

}*/

void MainWindow::check_collitions() {
    /*------COINS------*/
    if(pacman->get_score() < 23000){

        for(int k = 0; k < coins.size(); k++){

            if(pacman->collidesWithItem(coins.at(k))){

                scene->removeItem(coins.at(k));
                coins = delete_coins(coins, k);
                pacman->add_score(100);
                ui->score_display->display(pacman->get_score());
            }
        }
    }
     if(pacman->get_score() == 23000){

        win_sound->play(); //stop when you click the button***

        disconnect(collitions_timer,0,0,0);
        collitions_timer->stop();

        disconnect(bg_sound_timer,0,0,0);
        bg_sound_timer->stop();
        bg_sound->stop();

        pacman->reset();
        pacman->setRotation(0);
        for(int w = 0; w < ghosts.size(); w++)
            ghosts.at(w)->reset();

        for(int k = 0; k<coins.size(); k++)
            scene->removeItem(coins.at(k));
        init_coins();
        for(int k = 0; k<coins.size(); k++)
             scene->addItem(coins.at(k));

        ui->lives_display->setText(QString::number(pacman->getLives()));
        ui->score_display->display(pacman->get_score());

        connect(collitions_timer, &QTimer::timeout, this, &MainWindow::check_collitions);
        collitions_timer->start(60);

        //pop up
        pop_up->setIconPixmap(QPixmap(":/assets/sprites/icon.png"));
        pop_up->setBackgroundRole(QPalette::ColorRole::Window); //how does this fucking work
        pop_up->setFont(QFont("System"));
        pop_up->setForegroundRole(QPalette::ColorRole::WindowText);
        pop_up->setText("You Won!");
        pop_up->setInformativeText("Thanks for playing!");
        pop_up->setButtonText(0, "Play Again?");
        pop_up->exec();

    }

    /*------WALLS------*/
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

    /*------TELEPORTERS------*/
    for(int k = 0; k < teleporters.size(); k++){

        if(pacman->collidesWithItem(teleporters.at(k), Qt::ContainsItemBoundingRect)){

            pacman->setPosx(teleporters.at(k)->getDesx());
            pacman->setPosy(teleporters.at(k)->getDesy());
            pacman->setPos(teleporters.at(k)->getDesx(), teleporters.at(k)->getDesy());

        }
    }

    /*------GHOSTS------*/
    if(pacman->getLives() > 0){

        for(int k = 0; k<ghosts.size(); k++){

            if(pacman->collidesWithItem(ghosts.at(k))){

                for(int w = 0; w < ghosts.size(); w++)
                    ghosts.at(w)->reset();

                disconnect(bg_sound_timer,0,0,0);
                bg_sound->stop();

                death_sound->play();

                pacman->setRotation(0);
                pacman->death_animation();

                ui->lives_display->setText(QString::number(pacman->getLives()));

                k = ghosts.size();
            }
        }
    }
    else if(pacman->getLives() == 0){ // no lives left

        gameover_sound->play(); //stop when you click the button *********

        disconnect(collitions_timer,0,0,0);
        collitions_timer->stop();

        disconnect(bg_sound_timer,0,0,0);
        bg_sound_timer->stop();
        bg_sound->stop();

        pacman->reset();
        pacman->setRotation(0);
        for(int w = 0; w < ghosts.size(); w++)
            ghosts.at(w)->reset();

        for(int k = 0; k<coins.size(); k++)
            scene->removeItem(coins.at(k));
        init_coins();
        for(int k = 0; k<coins.size(); k++)
             scene->addItem(coins.at(k));

        ui->lives_display->setText(QString::number(pacman->getLives()));
        ui->score_display->display(pacman->get_score());

        connect(collitions_timer, &QTimer::timeout, this, &MainWindow::check_collitions);
        collitions_timer->start(60);
    }
    /*------WAKA SOUND------*/
    if(ui->checkBox->isChecked()){
        if(!bg_sound_timer->isActive())
            bg_sound_timer->start(60);
    }
    else if(!ui->checkBox->isChecked()){
        bg_sound->stop();
        bg_sound_timer->stop();
    }
}

void MainWindow::play_bg_sound() {
    if(bg_sound->PlayingState == QMediaPlayer::PlayingState)
        bg_sound->play();
}

void MainWindow::init_coins() {

    coins.clear();

    for(int i = 48; i < 650; i+= 32){
        for(int j = 48; j < 830; j+= 32){
            coins.push_back(new Coin(nullptr, i, j));
            coins.back()->setScale(3);
        }
    }

    coins = remove_initital_coins();
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
    int count_walls = 0, count_ghosts = 0;

    for(int k = 0; k < coins.size(); k++){

        for(int w = 0; w<walls.size(); w++)
            if(!coins.at(k)->collidesWithItem(walls.at(w)))
                count_walls++;

        for(int w = 0; w<ghosts.size(); w++)
            if(!coins.at(k)->collidesWithItem(ghosts.at(w)))
                count_ghosts++;

        if(count_walls == walls.size() && count_ghosts == ghosts.size() && !coins.at(k)->collidesWithItem(pacman) && k!=235)
            aux.push_back(coins.at(k));

        count_walls = 0;
        count_ghosts = 0;
    }
    return aux;
}

void MainWindow::keyPressEvent(QKeyEvent *event){ //timer issues

    //bg_sound_timer->start(bg_sound->duration());
    connect(bg_sound_timer, &QTimer::timeout, this, &MainWindow::play_bg_sound);
    //bg_sound_timer->start(300);
    //bg_sound->play();

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
