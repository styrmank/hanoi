#include "gamemanager.hh"


GameManager::GameManager(Tower **towers):
    towers_(towers),
    current_block_(towers[0]->getTop()),
    selected_(nullptr),
    current_tower_(towers[0]),
    colormanager_(ColorManager(current_block_))
{

}


void GameManager::moveCursor(int dir)
{
    // case a block is moving
    if(selected_ != nullptr){return;}
    //empty towers are skipped over
    do
    {
        int next_tower_id = nextTowerId(dir);
        current_tower_ = towers_[next_tower_id];
        current_block_ = current_tower_->getTop();
    }while(current_block_ == nullptr);

    colormanager_.updateColors(current_block_,selected_);
}

void GameManager::selectBlock()
{
    if(selected_ != nullptr){return;}
    selected_ = current_block_;
    selected_->moveUp();
    current_tower_->removeTop();
    current_block_ = current_tower_->getTop();
    colormanager_.updateColors(current_block_,selected_);
}

void GameManager::moveBlock(int dir)
{
    // case block hasn't been selected yet
    if(selected_ == nullptr){return;}
    int next_tower_id = nextTowerId(dir);
    current_block_ = towers_[next_tower_id]->getTop();
    current_tower_ = towers_[next_tower_id];
    // move horizontally
    selected_->setX(current_tower_->x());
    colormanager_.updateColors(current_block_,selected_);
}

void GameManager::placeBlock(bool &win)
{
    if(selected_ == nullptr){return;}
    // case block can be placed on tower
    if(current_block_ == nullptr || *selected_ < *current_block_)
    {
        // move vertically
        selected_->setY(current_tower_->nextBlockY());
        current_tower_->addBlock(selected_);
        current_block_ = selected_;
        current_block_->setTower(current_tower_->getId());
        // block placed back down
        selected_ = nullptr;
    }
    colormanager_.updateColors(current_block_,selected_);
    win = towers_[goal_tower]->playerHasWon();
    // block won't be white
    if(win){colormanager_.setToTowerColor(current_block_);}
}

int GameManager::nextTowerId(int dir)
{
    // kept in range of three towers
    int next_tower_id = current_tower_->getId() + dir;
    if(next_tower_id < 0)
    {
        next_tower_id = 2;
    }
    else if(next_tower_id > 2)
    {
        next_tower_id = 0;
    }
    return next_tower_id;
}


