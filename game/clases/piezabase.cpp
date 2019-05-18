#include "piezabase.h"

piezaBase::piezaBase(QGraphicsItem *parent, QPoint coordI, bool iColor, tipoPieza iPieza) : QObject (), QGraphicsPixmapItem (parent)
{
	pieza = iPieza;
	coordTablero = coordI;
	color = iColor;

	//this->setPos(16+71*coordI.x(),16+71*coordI.y());
	setPos(TAM_SANGRIA + TAM_CUADRO*coordI.x() , TAM_SANGRIA + TAM_CUADRO*coordI.y());
}

piezaBase::~piezaBase()
{

}

QList<QPoint> piezaBase::movimientos()
{
	QList<QPoint> lista;
	return lista;
}

QPoint piezaBase::getPos()
{
	return coordTablero;
}

void piezaBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug() << "Pieza click! " << pieza << "\tEvent:" << event;
	QList <QPoint> listaMovs = this->movimientos();
	for (int i = 0, n = listaMovs.size(); i < n ; i++)
	{
		qDebug() << "Creando movimientos";
		cuadroSelect *move = new cuadroSelect(this,listaMovs[i]);
		scene()->addItem(move);
		connect( move , SIGNAL(selected(QPoint)), this, SLOT(move(QPoint)) );
	}
}

void piezaBase::move(QPoint coordT)
{
	qDebug() << "Slot move!";
	coordTablero = coordT;
	QList <QGraphicsItem *> children = this->childItems();
	for (int i = 0, n = children.size(); i < n ; i++)
	{
		delete children[i];
	}
}
