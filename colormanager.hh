/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: ColorManager
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Color manager class used for outsourcing all the color changes
 *   applied to the blocks as the game continues.
 */

#ifndef COLORMANAGER_HH
#define COLORMANAGER_HH

#include "block.hh"
#include "tower.hh"

#include <QColor>

// color constants used in indicating block state
QColor const COLOR_SELECTED = QColor(Qt::white);
QColor const COLOR_NOT_PLACEABLA = QColor(Qt::black);

class ColorManager
{
public:
    /* Construct a new colormanager instance.
     * param - starting_block (Block*) : smallest block in the game.
     */
    ColorManager(Block *starting_block);

    /* Recolor blocks to reflect current game state.
     * param - current_block (Block*) : ptr to top most block
     *                                  of current tower.
     * param - selected (Block*) : ptr to block the player controls (if any).
     */
    void updateColors(Block *current_block, Block *selected);

    /* Color given block in its tower's respective color.
     * param - block (Block*) : ptr to block to be colored.
     */
    void setToTowerColor(Block *block);

private:
    Block *previous_block;
};

#endif // COLORMANAGER_HH
