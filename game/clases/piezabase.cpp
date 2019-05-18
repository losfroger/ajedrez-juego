#include "piezabase.h"

piezaBase::piezaBase(QGraphicsItem *parent, QPoint coordI, bool iColor, tipoPieza iPieza) : QObject (), QGraphicsPixmapItem (parent)
{
	pieza = iPieza;
	coordTablero = coordI;
	color = iColor;

	this->setPos(coordI);
}

piezaBase::~piezaBase()
{

}

QList<QPoint> piezaBase::movimientos()
{
	QList<QPoint> lista;
	return lista;
}

void piezaBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug() << "Pieza click! " << pieza << "\tEvent:" << event;
	QList <QPoint> listaMovs = this->movimientos();

	for (int i = 0, n = listaMovs.size(); i < n ; i++)
	{
		cuadroSelect *move = new cuadroSelect(this,listaMovs[i]);
		scene()->addItem(move);
		connect(move , SIGNAL(selected()), this, SLOT(move()));
	}
}

void piezaBase::move()
{
	qDebug() << "Slot move!";

	QList <QGraphicsItem *> children = this->childItems();
	for (int i = 0, n = children.size(); i < n ; i++)
	{
		delete children[i];
	}
}
