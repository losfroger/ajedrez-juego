#include "cuadroselect.h"

cuadroSelect::cuadroSelect(QGraphicsItem *parent, QPoint coordI) : QObject (), QGraphicsRectItem (parent)
{
	setRect(-1*parentItem()->x(),-1*parentItem()->y(),67,67);
	setPos(coordI);
	setBrush(QBrush(Qt::green));
	setOpacity(0.5);
}

cuadroSelect::~cuadroSelect()
{
	scene()->removeItem(this);
}

void cuadroSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	parentItem()->setPos(this->pos());
	emit selected();
}
