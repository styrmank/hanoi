#include "colormanager.hh"

ColorManager::ColorManager(Block *starting_block):
    previous_block(starting_block)
{
    previous_block->recolor(COLOR_SELECTED);
}



void ColorManager::updateColors(Block *current_block, Block *selected)
{
    // two modes (if else) needed depending on if the player controls a block
    if(selected == nullptr)
    {

        setToTowerColor(previous_block);
        current_block->recolor(COLOR_SELECTED);
        previous_block = current_block;

    }
    else
    {
        // case the tower below is empty
        if(current_block == nullptr)
        {
            selected->recolor(COLOR_SELECTED);
            return;
        }

        setToTowerColor(current_block);
        // case block cannot be placed
        if(*current_block < *selected)
        {
            selected->recolor(COLOR_NOT_PLACEABLA);
        }
        else
        {
            selected->recolor(COLOR_SELECTED);
        }

    }
}



void ColorManager::setToTowerColor(Block *block)
{
    block->recolor(TOWER_COLORS[block->getTower()]);
}
