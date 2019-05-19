#include "piezabase.h"

piezaBase::piezaBase(QGraphicsItem *parent, QPoint coordI, bool iColor, tipoPieza iPieza) : QObject (), QGraphicsPixmapItem (parent)
{
	pieza = iPieza;
	coordTablero = coordI;
	color = iColor;

	//this->setPos(16+71*coordI.x(),16+71*coordI.y());
	setPos(TAM_SANGRIA + TAM_CUADRO*coordI.x() , TAM_SANGRIA + TAM_CUADRO*coordI.y());
}

piezaBase::piezaBase(const piezaBase &other) : QObject (), QGraphicsPixmapItem(other.parentItem())
{
	this->setPieza(other.getPieza());
	this->setCoord(other.getCoord());
	this->setColor(other.getColor());
	this->setSelectable(other.getSelectable());
	this->setPixmap(other.pixmap());
}

piezaBase::~piezaBase()
{
	scene()->removeItem(this);
}

QList<QPoint> piezaBase::movimientos()
{
	QList<QPoint> lista;
	return lista;
}

void piezaBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug() << "Pieza click! " << pieza << "\tEvent:" << event;

	//Consigue la lista de movimientos posibles de la pieza
	QList <QPoint> listaMovs = this->movimientos();

	//Genera los cuadros de seleccion a los que se puede mover la pieza
	qDebug() << "Creando movimientos";

	for (int i = 0, n = listaMovs.size(); i < n ; i++)
	{
		cuadroSelect *move = new cuadroSelect(this,listaMovs[i]);
		scene()->addItem(move);
		//Conectar la señal del cuadrado al objeto.
		connect(move , SIGNAL(selected(QPoint)), this, SLOT(move(QPoint)) );
	}
}

void piezaBase::move(QPoint coordT)
{
	QPoint aux = coordTablero;
	qDebug() << "Slot move!";
	coordTablero = coordT;
	QList <QGraphicsItem *> children = this->childItems();
	for (int i = 0, n = children.size(); i < n ; i++)
	{
		delete children[i];
	}
	emit piezaMoved(aux,coordTablero);
}
