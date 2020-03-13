/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: MainWindow
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Main window of the game containing the game view and the widgets
 *   included along it. Communicates with gamemanager and creates
 *   start dialog window.
*/

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "tower.hh"
#include "gamemanager.hh"
#include "startdialog.hh"

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBoxLayout>
#include <QBrush>
#include <QPen>
#include <QKeyEvent>
#include <QGraphicsRectItem>
#include <QTimer>
#include <QLCDNumber>

/* parameters for the window.
 * testing shows these ones work properly but is scalable.
 */
qreal const X_MARGIN = 10;
qreal const Y_MARGIN = 10;
qreal const WIDTH = 600;
qreal const HEIGHT = 400;
qreal const WU = WIDTH/15;
qreal const HU = HEIGHT/9;


QString const BUTTON_TEXTS_MOVEMENT[] = {"<-","->","Select","Place"};
QString const CONGRATULATIONS_MESSAGE = "Good Job!";
QString const REPLAY_PROMPT_MESSAGE ="Would you like to replay the game?";


// enum for helping navigate different buttons.
enum options_movement
{
    moveleft = 0,
    moveright = 1,
    select_current = 2,
    place_here = 3,

    COUNT_MOVEMENT_BUTTONS = 4
};

class MainWindow;

// typedef for helping button mapping
typedef void (MainWindow::*fun_pointer_movement)();


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /* Construct instance of main window
     * param - startGame (&bool) : checker for if the game should be started
     * param - parent (QWidget) : parent widget
     */
    MainWindow(bool &startGame, QWidget *parent = 0);
    // Destroy window
    ~MainWindow();


protected:
    /* Perform action based on pressed key
     * param - event (QKeyEvent) : key event relating to pressed key.
     */
    void keyPressEvent(QKeyEvent *event);

public slots:
    // move cursor/selected block to the left
    void moveLeft();
    // move cursor/selected block to the right
    void moveRight();
    // select block the cursor currently points to, if none selected
    void select();
    // place selected block down if possible
    void place();
    // update time view to match passed game time
    void updateClock();

private:
    QGraphicsScene* scene_;
    QGraphicsView* view_;
    QGridLayout *layout_;
    QHBoxLayout *buttons_and_timer_layout_;
    QWidget* central_;
    Tower *towers_[3];
    GameManager *gm_;
    QPushButton *buttons_movement_[options::COUNT];
    QTimer *timer_;
    QLCDNumber *clock_[3];



    int blocks_amount_;
    // for timer
    int passed_time_;


    // populate scene with objects needed for game
    void generateScene();
    // create and add movement controller buttons to view
    void setUpMovementButtons();
    // create and start timer
    void setUpTimer();


    // tell player about victory, save result, possibly restart game
    void winProtocol();



};

// array of buttons used in movement
const fun_pointer_movement SLOTS_MOVEMENT[] = {&MainWindow::moveLeft,
                                               &MainWindow::moveRight,
                                              &MainWindow::select,
                                              &MainWindow::place};

#endif // MAINWINDOW_HH
