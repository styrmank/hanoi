/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: GameManager
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Module responsible for managing and running the Tower of Hanoi game.
 *   Communicates with mainwindow and colormanager to update game scene
 *   to correspond with game state. Checks and informs if the game has ended.
 */

#ifndef GAMEMANAGER_HH
#define GAMEMANAGER_HH

#include "block.hh"
#include "tower.hh"
#include "colormanager.hh"
#include "filehandler.hh"

#include <QColor>
#include <vector>

// enum to help match meant direction l stands for left and r for right
enum direction
{
    l = -1,
    r = 1
};


class GameManager
{
public:

   /* Contruct instance of gamemanager
    * param - towers (Tower**) : array of the three towers in the game.
    */
    GameManager(Tower **towers);


    /* Move cursor to next available block in direction dir
     * param - dir (int) : direction of movement l(-1) is left, r(1) is right.
     */
    void moveCursor(int dir);

    // Select current block for movement.
    void selectBlock();

    /* Move selected block in given direction
     * param - dir (int) : same as in moveCursor.
     */

    void moveBlock(int dir);

    /* Place block on top of current tower.
     * param - win (bool&) : reference to condition checking if game has ended
     */
    void placeBlock(bool &win);

private:
    Tower **towers_;
    Block *current_block_;
    Block *selected_;
    Tower *current_tower_;
    ColorManager colormanager_;

    /* Return id of next tower in direction dir
     * param - dir (int) : direction of movement (same as above)
     * return - (int) : id of next tower in given direction.
     */
    int nextTowerId(int dir);

};


#endif // GAMEMANAGER_HH
