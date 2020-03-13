#include "mainwindow.hh"

MainWindow::MainWindow(bool &startGame, QWidget *parent)
    : QMainWindow(parent),
      scene_(new QGraphicsScene(X_MARGIN,Y_MARGIN,WIDTH,HEIGHT,this)),
      view_(new QGraphicsView(scene_,this)),
      layout_(new QGridLayout),
      buttons_and_timer_layout_(new QHBoxLayout),
      central_(new QWidget(this)),
      towers_{},
      gm_(nullptr),
      buttons_movement_{},
      timer_(new QTimer()),
      clock_{},
      blocks_amount_(BLOCKS_MIN),
      passed_time_(0)

{
    // tells main to not run game if rejected
    if(StartDialog(this,&blocks_amount_).exec() == QDialog::Rejected)
    {
        startGame = false;
        return;
    }
    // side setup needed to display non-ui file derived scene
    layout_->addWidget(view_,0,0,2,3);
    central_->setLayout(layout_);
    this->setCentralWidget(central_);
    generateScene();
    setUpMovementButtons();
    setUpTimer();

    layout_->addLayout(buttons_and_timer_layout_,3,0,1,3);
    gm_ = new GameManager(towers_);
}

MainWindow::~MainWindow()
{

    for(Tower *t : towers_)
        delete t;
    for(QPushButton *b : buttons_movement_)
    {
        delete b;
    }
    for(QLCDNumber *n : clock_)
    {
        delete n;
    }
    delete buttons_and_timer_layout_;
    delete scene_;
    delete layout_;
    delete view_;
    delete central_;
    delete gm_;
    delete timer_;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_W:
        select();
        break;
    case Qt::Key_A:
        moveLeft();
        break;
    case Qt::Key_D:
        moveRight();
        break;
    case Qt::Key_S:
        place();
        break;
    default:
        break;
    }
}

void MainWindow::moveLeft()
{
    gm_->moveCursor(direction::l);
    gm_->moveBlock(direction::l);
}

void MainWindow::moveRight()
{
    gm_->moveCursor(direction::r);
    gm_->moveBlock(direction::r);
}


void MainWindow::select()
{
    gm_->selectBlock();
}

void MainWindow::place()
{
    bool win = false;
    gm_->placeBlock(win);
    if(win)
    {
        winProtocol();
    }
}

void MainWindow::updateClock()
{
    passed_time_++;
    int hours  = passed_time_/3600;
    int minutes = (passed_time_ - 3600*hours)/60;
    int seconds = passed_time_%60;

    clock_[0]->display(hours);
    clock_[1]->display(minutes);
    clock_[2]->display(seconds);
}

void MainWindow::generateScene()
{
    // first create table and towers
    scene_->addRect(WU,8*HU,13*WU,HU,QPen(Qt::black),QBrush(Qt::black));

    for(int i = 0; i<3; i++)
    {
        towers_[i] = new Tower(WU,HU,blocks_amount_);
        // calibrated ok position coordinates
        towers_[i]->setPos(3.75*WU*(i+1),
                           5.5*HU);
        scene_->addItem(towers_[i]);
        // adds blocks to scene
        towers_[i]->generateBlocks(blocks_amount_,scene_);
    }


}

void MainWindow::setUpMovementButtons()
{

    for(int i = 0; i<options_movement::COUNT_MOVEMENT_BUTTONS; i++)
    {
        buttons_movement_[i] = new QPushButton(this);
        buttons_movement_[i]->setText(BUTTON_TEXTS_MOVEMENT[i]);
        buttons_and_timer_layout_->addWidget(buttons_movement_[i]);
    }
    connect(buttons_movement_[moveleft],
            &QPushButton::clicked,
            this,
            SLOTS_MOVEMENT[moveleft]);
    connect(buttons_movement_[moveright],
            &QPushButton::clicked,
            this,
            SLOTS_MOVEMENT[moveright]);
    connect(buttons_movement_[select_current],
            &QPushButton::clicked,
            this,
            SLOTS_MOVEMENT[select_current]);
    connect(buttons_movement_[place_here],
            &QPushButton::clicked,
            this,
            SLOTS_MOVEMENT[place_here]);
}

void MainWindow::setUpTimer()
{
    for(int i = 0; i<3; i++)
    {
        clock_[i] = new QLCDNumber();
        clock_[i]->display(0);
        buttons_and_timer_layout_->addWidget(clock_[i]);
    }
    connect(timer_,&QTimer::timeout, this, &MainWindow::updateClock);
    timer_->start(1000);


}

void MainWindow::winProtocol()
{
    timer_->stop();
    FileHandler().saveHighScore(passed_time_);

    QMessageBox mbox;
    mbox.setText(CONGRATULATIONS_MESSAGE);
    mbox.exec();
    close();
}


