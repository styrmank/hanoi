/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: StartDialog
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Start dialog shown to player at the start of the application.
 *   The player can start the game, adjust the amount of blocks,
 *   view the most recent high score or read the instructions.
 */

#ifndef STARTDIALOG_HH
#define STARTDIALOG_HH

#include "filehandler.hh"

#include <QDialog>
#include <QInputDialog>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>


// enum of different options in the dialog to make navigating easier.
enum options
{
    start = 0,
    edit_block_amount = 1,
    highscore_button = 2,
    instruction_button = 3,

    COUNT = 4
};

const QString BUTTON_TEXTS[] = {"Start","Set Block Amount","High Score","Help"};
const QString WINDOW_NAME = "TOWER OF HANOI";

// amount range for blocks
int const BLOCKS_MIN = 3;
int const BLOCKS_MAX = 12;


class StartDialog;

// typedef for function mapping
typedef void (StartDialog::*fun_pointer)();


class StartDialog : public QDialog
{
    Q_OBJECT

public:
    /* Contruct a new startdialog window instance.
     * param - parent (QWidget*) : parent of dialog window
     * param - blocks_amount (int*) : amount of blocks to spawn (sent to main)
     */
    StartDialog(QWidget *parent, int *blocks_amount);

    // Destroy instance of dialog window
    ~StartDialog();

public slots:
    // Let the player set block amount between range of min and max value
    void editBlockAmount();
    // Close dialog window and starts main game
    void startGame();
    // Prompt the previous high score (if found) to the player.
    void showHighScore();
    // Prompt instructions to the player (if found).
    void showInstructions();

private:
    QVBoxLayout *layout_;
    QPushButton *buttons_[options::COUNT];
    int *blocks_amount_;

    // creates, adds and connects all required widgets to window
    void setUp();

};

// function pointer array to the slot commands of the different buttons
const fun_pointer SLOTS[] = {&StartDialog::startGame,
                             &StartDialog::editBlockAmount,
                             &StartDialog::showHighScore,
                             &StartDialog::showInstructions};




#endif // STARTDIALOG_HH
