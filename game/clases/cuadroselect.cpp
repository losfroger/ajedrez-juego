#include "cuadroselect.h"

piezas::cuadroSelect::cuadroSelect(QGraphicsItem *parent, QPoint coordI) : QObject (), QGraphicsRectItem (parent)
{
	//Poner el cuadrado en el origen de la escena y poner su posicion
	setRect (-1*parentItem()->x(),-1*parentItem()->y(),71,71);
	setPos (TAM_SANGRIA+TAM_CUADRO*coordI.x() , TAM_SANGRIA+TAM_CUADRO*coordI.y());
	setZValue(500);
	//Cambiar su color y opacidad
	setBrush(QBrush(Qt::green));
	setOpacity(0.5);
	coordT = coordI;
}

piezas::cuadroSelect::~cuadroSelect()
{
	scene()->removeItem(this);
}

//Falta revisar que tipo de click es
void piezas::cuadroSelect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug() << event;
	parentItem()->setPos(this->pos());
	emit selected(coordT);
}
