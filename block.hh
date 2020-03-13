/*
 *   COURSE: Ohjelmointi 2
 *   ASSIGNMENT: Final project
 *   MODULE: Block
 *   AUTHOR: Kasper Styrman, student# 284971
 *
 *   Represents a block (disc) visually and logically.
 *   Inherits from QGraphicsItem. Blocks are ranked
 *   by size indicated by their id, and change color depending on game state.
 */
#ifndef BLOCK_HH
#define BLOCK_HH

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QColor>



qreal const WIDTH_IN_UNITS_BLOCK = 1;
qreal const HEIGHT_IN_UNITS_BLOCK = 1/3;


class Block : public QGraphicsItem
{
    // automates block generation
    static int n;

public:
    /* Construct an instance of the block class
     * param - wu (qreal) : width unit scaled to scene size
     * param - hu (qreal) : height unit scaled to scene size
     * param - id (int) : represents the id (size) of the block
     */
    Block(qreal const &wu, qreal const &hu,int id = n);

    // QT documentation clarifies overriding when inheriting from graphicsitem
    QRectF boundingRect() const override;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) override;

    /* Change block color to newColor
     * param - newColor (QColor) : new color of the block
     */
    void recolor(QColor newColor);

    /* Compare two blocks on their id (size)
     * param - rhs (Block) : block on the right side of <
     * return - (bool) : true if block is smaller than rhs otherwise false
     */
    bool operator <(Block const &rhs);

    /* Return id (size) of the block
     * return - (int) : id of the block.
     */
    int getId() const;

    /* 'Set' block to a tower (change the tower_id_ it contains)
     * param - tower_id (int) : tower id of the new tower
     */
    void setTower(int const &tower_id);

    /* Return tower id this block containts
     * return - (int) : tower id of the block's current tower
     */
    int getTower() const;

    // change block y coordinate higher to correspond to being selected
    void moveUp();

private:
    int id_;
    int const WU;
    int const HU;
    int tower_id_;
    QColor color_;

};

#endif // BLOCK_HH
