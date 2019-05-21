#include "piezabase.h"

piezas::piezaBase::piezaBase(QGraphicsItem *parent, QPoint coordI, bool iColor, tipoPieza iPieza) : QObject (), QGraphicsPixmapItem (parent)
{
	pieza = iPieza;
	coordTablero = coordI;
	color = iColor;

	//Poner la pieza en su posicion inicial graficamente en el tablero
	setPos(TAM_SANGRIA + TAM_CUADRO*coordI.x() , TAM_SANGRIA + TAM_CUADRO*coordI.y());
	setZValue(0);
}

piezas::piezaBase::piezaBase(const piezaBase &other) : QObject (), QGraphicsPixmapItem(other.parentItem())
{
	this->setPieza (other.getPieza());
	this->setCoord (other.getCoord());
	this->setColor (other.getColor());
	this->setSelectable (other.getSelectable());
	this->setPixmap (other.pixmap());
}

piezas::piezaBase::~piezaBase()
{
	scene()->removeItem(this);
}

QList<QPoint> piezas::piezaBase::movimientos()
{
	QList<QPoint> lista;
	return lista;
}

void piezas::piezaBase::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	qDebug() << "Pieza click! " << pieza << "\tEvent:" << event;
	if (event->button() == Qt::LeftButton && selectable == true)
	{
		//Consigue la lista de movimientos posibles de la pieza
		QList <QPoint> listaMovs = this->movimientos();
		qDebug() << "Creando movimientos, cantidad de movimientos posibles: " << listaMovs.size();
		if (listaMovs.size() > 0)
		{
			emit teamUnselect(getColor());
			//Genera los cuadros de seleccion a los que se puede mover la pieza
			for (int i = 0, n = listaMovs.size(); i < n ; i++)
			{
				cuadroSelect *move = new cuadroSelect(this,listaMovs[i]);
				//scene()->addItem(move);
				//Conectar la señal del cuadrado al objeto.
				connect(move , SIGNAL(selected(QPoint)), this, SLOT(move(QPoint)) );
			}
		}
	}
	else if (event->button() == Qt::RightButton && selectable == false)
	{
		emit teamSelect(getColor());
		selectable = true;
		QList <QGraphicsItem *> children = this->childItems();
		for (int i = 0, n = children.size(); i < n ; i++)
			delete children[i];
	}
}

void piezas::piezaBase::positionChanged()
{ }

void piezas::piezaBase::move(QPoint coordT)
{
	this->positionChanged();

	QPoint aux = coordTablero;
	qDebug() << "Slot move!";
	coordTablero = coordT;
	QList <QGraphicsItem *> children = this->childItems();
	//Eliminar todos los cuadros de seleccion de movimiento
	for (int i = 0, n = children.size(); i < n ; i++)
	{
		delete children[i];
	}
	/*Mandarle al tablero las coordenadas viejas y nuevas
	para hacer el cambio dentro de la matriz*/
	emit piezaMoved(aux,coordTablero);
}
