/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: Tower
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Represents tower logically and visually. Inherits from
 *   QGraphicsItem. Manages a stack of blocks and
 *   checks for victory.
 */

#ifndef TOWER_HH
#define TOWER_HH

#include "block.hh"

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <stack>
#include <QPainter>
#include <QColor>

// calibrating found to look good in view
qreal const WIDTH_IN_UNITS_TOWER = 0.5;
qreal const HEIGHT_IN_UNITS_TOWER = 5;
qreal const FIRST_BLOCK_Y_IN_UNITS = 7.85;


QColor const TOWER_COLORS[] = {QColor(Qt::red),
                               QColor(Qt::blue),
                               QColor(Qt::yellow)};

// enum naming tower types to make movement easier
enum tower_id_names
{
    start_tower = 0,
    help_tower = 1,
    goal_tower = 2,
    TOWER_COUNT = 3
};

class Tower : public QGraphicsItem
{
public:
    /* Create an instance of tower
     * param - wu (qreal) - width unit used for calibration
     * param - hu (qreal) - height unit used for calibration
     * param - blocks_amount (int) - amount of blocks in the game.
     */
    Tower(qreal const &wu, qreal const &hu, int const &blocks_amount);

    // Destroy instance of tower.
    ~Tower();

    // check QT documentation for reasons of overriding below functions
    QRectF boundingRect() const override;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /* Return blocks in tower
     * return - (stack<Block*>) : stack containing pointers to blocks in tower
     */
    std::stack<Block*> getBlocks();
    /* Return topmost block in tower
     * return - (Block*) : topmost block.
     */
    Block *getTop();
    /* Return id of tower
     * return - (int) : id of tower.
     */
    int getId();
    /* Return color of tower
     * return - (QColor) : color of tower.
     */
    QColor getColor();
    /* Return height to which set next inserted block.
     * return - (qreal) : calculated y coordinate for next block.
     */
    qreal nextBlockY();
    /* Creates appropriate amount of blocks for tower
     * param - n (int) : n amount of blocks to be created
     * param - scene (QGraphicsScene*) : scene to which add created blocks.
     */
    void generateBlocks(int n, QGraphicsScene *scene = nullptr);
    // Remove topmost block in tower.
    void removeTop();
    /* Add a new block to tower's stack
     * param - block (Block*) : pointer to block to be added.
     */
    void addBlock(Block * const block);
    /* Check if selected block can be placed on tower
     * param - block (Block*) : candidate block
     * return - (bool) : true if can be added, otherwise false
     */
    bool blockIsPlaceable(Block *const block);
    /* Return wheter tower has no blocks
     * return - (bool) : true if tower has no blocks, else false.
     */
    bool isEmpty();
    /* Check if player has won the game.
     * return - (bool) : true if all blocks on correct tower otherwise false.
     */
    bool playerHasWon();

private:
    std::stack<Block*> blocks_;
    int id_;
    int blocks_amount_;
    // static counter for automasation of tower generation.
    static int ID_COUNTER;
    // width and height unit used for scaling
    qreal const WU;
    qreal const HU;
    // color of tower
    QColor color_;


};

#endif // TOWER_HH
