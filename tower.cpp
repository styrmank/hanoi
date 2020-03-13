#include "tower.hh"
#include <QDebug>

int Tower::ID_COUNTER = 0;

Tower::Tower(qreal const &wu, qreal const &hu, const int &blocks_amount):
    blocks_{},
    id_(ID_COUNTER),
    blocks_amount_(blocks_amount),
    WU(wu),
    HU(hu),
    color_(TOWER_COLORS[id_])
{
    ID_COUNTER++;
    // always drawn on back
    setZValue(-1);
}

Tower::~Tower()
{
    Block *p = nullptr;

    while(!blocks_.empty())
    {
        p = blocks_.top();
        blocks_.pop();
        delete p;
        p = nullptr;
    }
}

QRectF Tower::boundingRect() const
{
    // calculations based on testing and scaling
    return QRectF((-WIDTH_IN_UNITS_TOWER*WU-1)/2,
                  (-HEIGHT_IN_UNITS_TOWER*HU-1)/2,
                  WIDTH_IN_UNITS_TOWER*WU,
                  HEIGHT_IN_UNITS_TOWER*HU);
}

void Tower::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(color_);
    painter->drawRect(boundingRect());
}

std::stack<Block *> Tower::getBlocks()
{
    return blocks_;
}

Block *Tower::getTop()
{
    if(blocks_.empty()){return nullptr;}
    return blocks_.top();
}

int Tower::getId()
{
    return id_;
}

QColor Tower::getColor()
{
    return color_;
}

qreal Tower::nextBlockY()
{
    if(blocks_.empty()){return FIRST_BLOCK_Y_IN_UNITS*HU;}
    return blocks_.top()->y()-HU/3;
}

void Tower::generateBlocks(int n, QGraphicsScene *scene)
{
    if ( id_ != start_tower){return;}

    // largest block is created first
    for(int i = n; i>0; i--)
    {

        blocks_.push(new Block(WU,HU,i));
        // spawned appropriately on top of each other
        blocks_.top()->setPos(pos().x(),
                  FIRST_BLOCK_Y_IN_UNITS*HU-(n-i)*HU/3);
        if(scene != nullptr){scene->addItem(blocks_.top());}
    }
}

void Tower::removeTop()
{
    if(!blocks_.empty())
    {
        blocks_.pop();
    }
}

void Tower::addBlock(Block * const block)
{
    blocks_.push(block);
    block->setTower(id_);
}

bool Tower::blockIsPlaceable(Block * const block)
{
    if(blocks_.empty()){return true;}
    return *block < *(blocks_.top());
}

bool Tower::isEmpty()
{
    return blocks_.empty();
}

bool Tower::playerHasWon()
{
    return (id_ == goal_tower && (int)blocks_.size() == blocks_amount_);
}





