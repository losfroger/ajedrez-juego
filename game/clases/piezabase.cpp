#include "piezabase.h"

#include "game/clases/reina.h"

piezas::piezaBase::piezaBase(QGraphicsItem *parent, QPoint coordI,
							 colorP iColor, tipoPieza iPieza, piezaBase ***nTablero) : QObject (), QGraphicsPixmapItem (parent)
{
	pieza = iPieza;
	coordTablero = coordI;
	color = iColor;

	//Poner la pieza en su posicion inicial graficamente en el tablero
	setPos(TAM_SANGRIA + TAM_CUADRO*coordI.x() , TAM_SANGRIA + TAM_CUADRO*coordI.y());
	setZValue(0);

	tablero = nTablero;
	specialA = false;
	lastClicked = false;
    jaque_blancas = false;
    jaque_negras = false;
}

piezas::piezaBase::piezaBase(const piezaBase &other) : QObject (), QGraphicsPixmapItem(other.parentItem())
{
	this->setPieza (other.getPieza());
	this->setCoord (other.getCoord());
	this->setColor (other.getColor());
	this->setSelectable (other.getSelectable());
	this->setPixmap (other.pixmap());
	tablero = other.tablero;
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
			emit teamUnselect(getColor(),false);
			lastClicked = true;
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
	else if (event->button() == Qt::RightButton && selectable == false && turno == true && lastClicked == true)
	{
		lastClicked = false;
		emit teamSelect(getColor(),false);
		selectable = true;
		QList <QGraphicsItem *> children = this->childItems();
		for (int i = 0, n = children.size(); i < n ; i++)
			delete children[i];
	}
}

void piezas::piezaBase::positionChanged(QPoint nCoord)
{ nCoord; }

void piezas::piezaBase::update()
{ }

void piezas::piezaBase::move(QPoint coordT)
{
	QPoint aux = coordTablero;
	qDebug() << "Slot move!";
	QList <QGraphicsItem *> children = this->childItems();
	//Eliminar todos los cuadros de seleccion de movimiento
	for (int i = 0, n = children.size(); i < n ; i++)
		delete children[i];

	coordTablero = coordT;

	/*Mandarle al tablero las coordenadas viejas y nuevas
	para hacer el cambio dentro de la matriz*/
	emit piezaMoved(aux,coordT);
	this->positionChanged(coordT);
}

unsigned int piezas::check(piezaBase ***ntablero, QPoint coordI, colorP colorpieza, QList <QPoint> *arreglo_jaque)
{
    arreglo_jaque = nullptr;

    if (coordI.x() <= 7 && coordI.y() <= 7)
    {
        unsigned int cont_jaques = 0;

        int posx = coordI.x();
        int posy = coordI.y();

        QList <QPoint> moves_check;

        moves_check.clear();

        //checamos en forma vertical hacia arriba a ver si estan dando jaque a esa coordenada
        for (int i = posy - 1; i >= 0; --i)
        {
            if (ntablero[posx][i]->getColor() != colorpieza)
                moves_check.append(QPoint(posx, i));

            if (ntablero[posx][i]->getColor() != VACIA)
            {
                if (ntablero[posx][i]->getColor() != colorpieza)
                {
                    if (i == (posy - 1)) //saber si hay un rey enemigo arriba de la casilla
                    {
                        if (ntablero[posx][i]->getPieza() == REY)
                            ++cont_jaques;
                    }

                    if (ntablero[posx][i]->getPieza() == REINA || ntablero[posx][i]->getPieza() == TORRE)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma vertical hacia abajo a ver si estan dando jaque a esa coordenada
        for (int i = posy + 1; i <= 7; ++i)
        {
            if (!cont_jaques)
                moves_check.append(QPoint(posx, i));

            if (ntablero[posx][i]->getColor() != VACIA)
            {
                if (ntablero[posx][i]->getColor() != colorpieza)
                {
                    if (i == (posy + 1)) //saber si hay un rey enemigo abajo de la casilla
                    {
                        if (ntablero[posx][i]->getPieza() == REY)
                            ++cont_jaques;
                    }

                    if (ntablero[posx][i]->getPieza() == REINA || ntablero[posx][i]->getPieza() == TORRE)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma horizontal hacia la izquierda a ver si estan dando jaque a esa coordenada
        for (int i = posx - 1; i >= 0; --i)
        {
            if (ntablero[i][posy]->getColor() != VACIA)
            {
                if (ntablero[i][posy]->getColor() != colorpieza)
                {

                    if (i == (posx - 1)) //saber si hay un rey enemigo a la izquierda de la casilla
                    {
                        if (ntablero[i][posy]->getPieza() == REY)
                            ++cont_jaques;
                    }

                    if (ntablero[i][posy]->getPieza() == REINA || ntablero[i][posy]->getPieza() == TORRE)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma horizontal hacia la derecha a ver si estan dando jaque a esa coordenada
        for (int i = posx + 1; i <= 7; ++i)
        {
            if (ntablero[i][posy]->getColor() != VACIA)
            {
                if (ntablero[i][posy]->getColor() != colorpieza)
                {

                    if (i == (posx + 1)) //saber si hay un rey enemigo a la derecha de la casilla
                    {
                        if (ntablero[i][posy]->getPieza() == REY)
                            ++cont_jaques;
                    }

                    if (ntablero[i][posy]->getPieza() == REINA || ntablero[i][posy]->getPieza() == TORRE)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma diagonal hacia la izquierda superior a ver si estan dando jaque a esa coordenada
        for (int i = posx - 1, j = posy - 1; i >= 0 && j >= 0; --i, --j)
        {
            if (ntablero[i][j]->getColor() != VACIA)
            {
                if (ntablero[i][j]->getColor() != colorpieza)
                {
                    if (i == (posx - 1) && j == (posy - 1)) //saber si hay un rey o peon enemigo en la diagonal superior izquierda de la casilla
                    {
                        if (ntablero[i][j]->getPieza() == REY)
                            ++cont_jaques;

                        if (colorpieza == BLANCA)
                        {
                            if (ntablero[i][j]->getPieza() == PEON)
                                ++cont_jaques;
                        }
                    }

                    if (ntablero[i][j]->getPieza() == REINA || ntablero[i][j]->getPieza() == ALFIL)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma diagonal hacia la derecha superior a ver si estan dando jaque a esa coordenada
        for (int i = posx + 1, j = posy - 1; i <= 7 && j >= 0; ++i, --j)
        {
            if (ntablero[i][j]->getColor() != VACIA)
            {
                if (ntablero[i][j]->getColor() != colorpieza)
                {
                    if (i == (posx + 1) && j == (posy - 1)) //saber si hay un rey o peon enemigo en la diagonal superior izquierda de la casilla
                    {
                        if (ntablero[i][j]->getPieza() == REY)
                            ++cont_jaques;

                        if (colorpieza == BLANCA)
                        {
                            if (ntablero[i][j]->getPieza() == PEON)
                                ++cont_jaques;
                        }
                    }

                    if (ntablero[i][j]->getPieza() == REINA || ntablero[i][j]->getPieza() == ALFIL)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma diagonal hacia la izquierda inferior a ver si estan dando jaque a esa coordenada
        for (int i = posx - 1, j = posy + 1; i >= 0 && j <= 7; --i, ++j)
        {
            if (ntablero[i][j]->getColor() != VACIA)
            {
                if (ntablero[i][j]->getColor() != colorpieza)
                {
                    if (i == (posx - 1) && j == (posy + 1)) //saber si hay un rey o peon enemigo en la diagonal superior izquierda de la casilla
                    {
                        if (ntablero[i][j]->getPieza() == REY)
                            ++cont_jaques;

                        if (colorpieza == NEGRA)
                        {
                            if (ntablero[i][j]->getPieza() == PEON)
                                ++cont_jaques;
                        }
                    }

                    if (ntablero[i][j]->getPieza() == REINA || ntablero[i][j]->getPieza() == ALFIL)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en forma diagonal hacia la derecha inferior a ver si estan dando jaque a esa coordenada
        for (int i = posx + 1, j = posy + 1; i <= 7 && j <= 7; ++i, ++j)
        {
            if (ntablero[i][j]->getColor() != VACIA)
            {
                if (ntablero[i][j]->getColor() != colorpieza)
                {
                    if (i == (posx + 1) && j == (posy + 1)) //saber si hay un rey o peon enemigo en la diagonal superior izquierda de la casilla
                    {
                        if (ntablero[i][j]->getPieza() == REY)
                            ++cont_jaques;

                        if (colorpieza == NEGRA)
                        {
                            if (ntablero[i][j]->getPieza() == PEON)
                                ++cont_jaques;
                        }
                    }

                    if (ntablero[i][j]->getPieza() == REINA || ntablero[i][j]->getPieza() == ALFIL)
                        ++cont_jaques;
                }

                break;
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        //checamos en las posiciones del caballo a ver si un caballo esta dando jaque
        if (posx >= 2)
        {
            if (posy >= 1)
            {
                if (ntablero[posx - 2][posy - 1]->getColor() != VACIA)
                {
                    if (ntablero[posx - 2][posy - 1]->getColor() != colorpieza)
                    {
                        if (ntablero[posx - 2][posy - 1]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }

            if (posy <= 6)
            {
                if (ntablero[posx - 2][posy + 1]->getColor() != VACIA)
                {
                    if (ntablero[posx - 2][posy + 1]->getColor() != colorpieza)
                    {
                        if (ntablero[posx - 2][posy + 1]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        if (posx <= 5)
        {
            if (posy >= 1)
            {
                if (ntablero[posx + 2][posy - 1]->getColor() != VACIA)
                {
                    if (ntablero[posx + 2][posy - 1]->getColor() != colorpieza)
                    {
                        if (ntablero[posx + 2][posy - 1]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }

            if (posy <= 6)
            {
                if (ntablero[posx + 2][posy + 1]->getColor() != VACIA)
                {
                    if (ntablero[posx + 2][posy + 1]->getColor() != colorpieza)
                    {
                        if (ntablero[posx + 2][posy + 1]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        if (posy >= 2)
        {
            if (posx >= 1)
            {
                if (ntablero[posx - 1][posy - 2]->getColor() != VACIA)
                {
                    if (ntablero[posx - 1][posy - 2]->getColor() != colorpieza)
                    {
                        if (ntablero[posx - 1][posy - 2]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }

            if (posx <= 6)
            {
                if (ntablero[posx + 1][posy - 2]->getColor() != VACIA)
                {
                    if (ntablero[posx + 1][posy - 2]->getColor() != colorpieza)
                    {
                        if (ntablero[posx + 1][posy - 2]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }
        }

        if (!cont_jaques)
            moves_check.clear();

        if (posy <= 5)
        {
            if (posx >= 1)
            {
                if (ntablero[posx - 1][posy + 2]->getColor() != VACIA)
                {
                    if (ntablero[posx - 1][posy + 2]->getColor() != colorpieza)
                    {
                        if (ntablero[posx - 1][posy + 2]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }

            if (posx <= 6)
            {
                if (ntablero[posx + 1][posy + 2]->getColor() != VACIA)
                {
                    if (ntablero[posx + 1][posy + 2]->getColor() != colorpieza)
                    {
                        if (ntablero[posx + 1][posy + 2]->getPieza() == CABALLO)
                            ++cont_jaques;
                    }
                }
            }
        }

        if (!cont_jaques)
            moves_check.clear();
    }

    return false;
}
