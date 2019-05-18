#include "cuadroselect.h"

cuadroSelect::cuadroSelect(QGraphicsItem *parent, QPoint coordI) : QObject (), QGraphicsRectItem (parent)
{
	//Poner el cuadrado en el origen de la escena y poner su posicion
	setRect (-1*parentItem()->x(),-1*parentItem()->y(),71,71);
	setPos (16+71*coordI.x() , 16+71*coordI.y());
	//Cambiar su color y opacidad
	setBrush(QBrush(Qt::green));
	setOpacity(0.5);
	coordT = coordI;
}

cuadroSelect::~cuadroSelect()
{
	scene()->removeItem(this);
}

void cuadroSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	parentItem()->setPos(this->pos());
	emit selected(coordT);
}
