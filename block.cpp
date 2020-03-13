#include "block.hh"


int Block::n = 1;

Block::Block(const qreal &wu, const qreal &hu, int id):
    id_(id),
    WU(wu),
    HU(hu),
    tower_id_(0),
    color_(QColor("red"))
{
    n++;

}


QRectF Block::boundingRect() const
{
    // all functions except pos() based on own coordinates
    return QRectF(-(WIDTH_IN_UNITS_BLOCK*WU+id_*8)/2,-HU/6,
                    WIDTH_IN_UNITS_BLOCK*WU+id_*8,HU/3);

}

void Block::paint(QPainter *painter,
                  const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::black);
    painter->setBrush(color_);
    painter->drawRect(boundingRect());
}

void Block::recolor(QColor newColor)
{
    color_ = newColor;
    update();
}



bool Block::operator <(const Block &rhs)
{
    return id_<rhs.getId();
}

int Block::getId() const
{
    return id_;
}

void Block::setTower(const int &tower_id)
{
    tower_id_ = tower_id;
}

int Block::getTower() const
{
    return tower_id_;
}

void Block::moveUp()
{
    this->setY(2*HU);
}
