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

    init = false;

    /*------GHOSTS------*/

    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/red.png", 310, 396));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/pink.png", 360, 396));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/blue.png", 310, 434));
    ghosts.push_back( new Ghost(nullptr, ":/assets/sprites/orange.png", 360, 434));

    for(int k = 0; k<ghosts.size(); k++)
         ghosts.at(k)->setScale(2.5);

    /*------WALLS------*/

    walls = load_walls("walls.txt");

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

   collitions_timer = new QTimer;
   connect(collitions_timer, SIGNAL(timeout()), this, SLOT(check_collitions()));
   collitions_timer->start(60);

   bg_sound_timer = new QTimer;

   init_timer = new QTimer;

   enemy_movement_timer = new QTimer;
   //connect(enemy_movement_timer, SIGNAL(timeout()), this, SLOT(move_enemies()));
   //enemy_movement_timer->start(100);

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
    delete collitions_timer;
    delete init_timer;

    delete  enemy_movement_timer;

    delete bg_sound_timer;
    delete bg_sound;
    delete death_sound;
    delete intro_sound;
    delete ui;
}

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

        win_sound->play();

        disconnect(collitions_timer,0,0,0);
        collitions_timer->stop();

        disconnect(bg_sound_timer,0,0,0);
        bg_sound_timer->stop();
        bg_sound->stop();

        pacman->reset();
        pacman->setRotation(0);

        init = false;
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
        QMessageBox *pop_up =  new QMessageBox(QMessageBox::Information, "You Won!", " ");
        pop_up->setGeometry(194, 113, 858, 459);

        pop_up->setIconPixmap(QPixmap(":/assets/sprites/win_icon.png"));

        pop_up->setFont(QFont("System"));
        pop_up->setText("Thanks for playing!");
        pop_up->setInformativeText("Play Again?");

        pop_up->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        pop_up->setButtonText(QMessageBox::Ok, "Yes");
        pop_up->setButtonText(QMessageBox::Cancel, "No");

        int *res =  new int;
        *res = pop_up->exec();

        if(*res == QMessageBox::Ok)
            win_sound->stop();
        else if (*res == QMessageBox::Cancel)
            this->close();

        delete res;
        delete pop_up;
    }

    /*------WALLS------*/
    for(int k = 0; k < walls.size(); k++){

        if(pacman->collidesWithItem(walls.at(k), Qt::IntersectsItemBoundingRect)){

            disconnect(pacman->movement_timer,0,0,0);

            if(pacman->getDir() == "Right")
                pacman->bounce_left();
            else if (pacman->getDir() == "Left")
                pacman->bounce_right();
             if (pacman->getDir() == "Up")
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

                init = false;
                for(int w = 0; w < ghosts.size(); w++)
                    ghosts.at(w)->reset();

                disconnect(bg_sound_timer,0,0,0);
                bg_sound->stop();

                death_sound->play();

                pacman->setRotation(0);
                pacman->death_animation();

                ui->lives_display->setText(QString::number(pacman->getLives()));

                break;
            }
        }
    }
    else if(pacman->getLives() == 0){

        gameover_sound->play();

        disconnect(collitions_timer,0,0,0);
        collitions_timer->stop();

        disconnect(bg_sound_timer,0,0,0);
        bg_sound_timer->stop();
        bg_sound->stop();

        pacman->reset();
        pacman->setRotation(0);

        init = false;
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
        QMessageBox *pop_up =  new QMessageBox(QMessageBox::Information, "GameOver :(", " ");
        pop_up->setGeometry(194, 113, 858, 459);

        pop_up->setIconPixmap(QPixmap(":/assets/sprites/gameover_icon.png"));

        pop_up->setFont(QFont("System"));
        pop_up->setText("Better luck next time!");
        pop_up->setInformativeText("Play Again?");

        pop_up->setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        pop_up->setButtonText(QMessageBox::Ok, "Yes");
        pop_up->setButtonText(QMessageBox::Cancel, "No");

        int *res =  new int;
        *res = pop_up->exec();

        if(*res == QMessageBox::Ok)
            gameover_sound->stop();
        else if (*res == QMessageBox::Cancel)
            this->close();

        delete res;
        delete pop_up;
    }
    if(pacman->getDir() != "NA")
        move_enemies();

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

QList<Wall *> MainWindow::load_walls(std::string file_name) {

    QList<Wall *> res;

    std::fstream file (file_name, std:: fstream::in | std::fstream::binary);

     if(file.is_open()){

         std::string x_, y_, w_, h_, temp;
         short counter = 1;

         while (file >> temp){

             if(counter == 1)
                 x_ = temp;

             else if (counter == 2)
                 y_ = temp;

             else if (counter == 3)
                 w_ = temp;

             else if (counter == 4){
                 h_ = temp;

                 res.push_back(new Wall(nullptr, stoi(x_), stoi(y_), stoi(w_), stoi(h_)));

                 counter = 0;
             }

             counter++;
         }
     }
     file.close();

     return res;
}

void MainWindow::keyPressEvent(QKeyEvent *event){

    if(!init){ // not working. connecting multiple singleshots to a single timer makes it now work propperly
        for(int k = 0, time = 5000; k<ghosts.size(); k++, time += 5000)
            init_timer->singleShot(time, ghosts.at(k), SLOT(init()));
        init = true;
    }

    connect(bg_sound_timer, &QTimer::timeout, this, &MainWindow::play_bg_sound);

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

void MainWindow::move_enemies() {

    if(pacman->getDir() != "NA"){ // si pacman esta activo

        //for(int k = 0; k < walls.size(); k++){ // iterar sobre walls

            for(int w = 0; w<ghosts.size(); w++){ //iterar sobre ghosts

                if(ghosts.at(w)->getState()){ //si el fantasma esta activo

                    if(ghosts.at(w)->getPosx() < pacman->getPosx()){
                        //if(ghosts.at(w)->collidesWithItem(walls.at(k))){
                        //if(ghosts.at(w)->collidingItems().size() != 0){
                               // ghosts.at(w)->bounce_left();
                        //} else
                            ghosts.at(w)->move_right();
                    }

                    else if(ghosts.at(w)->getPosx() > pacman->getPosx()){
                        //if(ghosts.at(w)->collidesWithItem(walls.at(k))){
                        //if(ghosts.at(w)->collidingItems().size() != 0){
                                //ghosts.at(w)->bounce_right();
                        //} else
                            ghosts.at(w)->move_left();
                    }



                    if(ghosts.at(w)->collidingItems().size() != 0){ //don't move as intended
                        for(int i=0; i < ghosts.at(w)->collidingItems().size(); ++i){
                            if(typeid (*((ghosts.at(w)->collidingItems())[i])) == typeid (Wall)){
                                if(ghosts.at(w)->getX_dir() == "Right")
                                    ghosts.at(w)->bounce_left();
                                else if (ghosts.at(w)->getX_dir() == "Left")
                                    ghosts.at(w)->bounce_right();
                            }
                        }
                    }

                     if(ghosts.at(w)->getPosy() < pacman->getPosy()){
                        //if(ghosts.at(w)->collidesWithItem(walls.at(k))){
                         //if(ghosts.at(w)->collidingItems().size() != 0){
                                //ghosts.at(w)->bounce_up();
                        //} else
                            ghosts.at(w)->move_down();
                    }

                    else if(ghosts.at(w)->getPosy() > pacman->getPosy()){
                        //if(ghosts.at(w)->collidesWithItem(walls.at(k))){
                         //if(ghosts.at(w)->collidingItems().size() != 0){
                                //ghosts.at(w)->bounce_down();
                        //} else
                             ghosts.at(w)->move_up();
                     }

                     if(ghosts.at(w)->collidingItems().size() != 0){
                         for(int i=0; i < ghosts.at(w)->collidingItems().size(); ++i){
                             if(typeid (*((ghosts.at(w)->collidingItems())[i])) == typeid (Wall)){
                                 if(ghosts.at(w)->getY_dir() == "Up")
                                     ghosts.at(w)->bounce_down();
                                 else if (ghosts.at(w)->getY_dir() == "Down")
                                     ghosts.at(w)->bounce_up();
                             }
                         }
                     }

//                     if(ghosts.at(w)->collidingItems().size() != 0){ //collide with everything
//                         if(ghosts.at(w)->getX_dir() == "Right")
//                             ghosts.at(w)->bounce_left();
//                         else if (ghosts.at(w)->getX_dir() == "Left")
//                             ghosts.at(w)->bounce_right();
//                     }


                }
            }
    }
    //}
}



