#include "peon.h"

piezas::peon::peon(QGraphicsItem *parent, QPoint coordI,
				   colorP iColor, piezaBase ***nTablero) : piezaBase (parent, coordI, iColor, PEON,nTablero)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0peon.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1peon.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
	firstMove = true;
	count = 1;
	capturaPaso = false;
}

piezas::peon::peon(const piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::peon::movimientos()
{
	captura.clear();
	capturaPaso = false;
	QList <QPoint> moves;
	//Si es una pieza negra
	if (this->getColor() == NEGRA)
	{
		//Movimientos hacia adelante
		for (int i = 1 ; i < 2 + firstMove && getCoord().y()+1 <= 7 ; i++)
		{
			if (tablero[getCoord().x()][getCoord().y()+i]->getColor() != VACIA)
				break;
			else
				moves.append(QPoint(getCoord().x() , getCoord().y()+i));
		}

		if (getCoord().y()+1 <= 7)
		{
			if (getCoord().x()-1 > 0)
			{
				//Comer en diagonal
				if(tablero[getCoord().x()-1][getCoord().y()+1]->getColor() != VACIA
						&& tablero[getCoord().x()-1][getCoord().y()+1]->getColor() != this->getColor())
				{
					moves.append(QPoint(getCoord().x()-1 , getCoord().y()+1));
				}
				//Captura paso
				if(tablero[getCoord().x()-1][getCoord().y()]->getPieza() == PEON
						&& tablero[getCoord().x()-1][getCoord().y()]->getSpecialA() == true
						&& tablero[getCoord().x()-1][getCoord().y()]->getColor() != getColor())
				{
					qDebug() << "Captura a paso - 1";
					capturaPaso = true;
					captura.append((QPoint(getCoord().x()-1 , getCoord().y()+1)));
					moves.append((QPoint(getCoord().x()-1 , getCoord().y()+1)));
				}

			}
			if (getCoord().x()+1 <= 7)
			{
				//Comer en diagonal
				if(tablero[getCoord().x()+1][getCoord().y()+1]->getColor() != VACIA
						&& tablero[getCoord().x()+1][getCoord().y()+1]->getColor() != this->getColor())
				{
					moves.append(QPoint(getCoord().x()+1 , getCoord().y()+1));
				}
				//Captura paso
				if(tablero[getCoord().x()+1][getCoord().y()]->getPieza() == PEON
						&& tablero[getCoord().x()+1][getCoord().y()]->getSpecialA() == true
						&& tablero[getCoord().x()+1][getCoord().y()]->getColor() != getColor())
				{
					qDebug() << "Captura a paso + 1";
					capturaPaso = true;
					captura.append((QPoint(getCoord().x()+1 , getCoord().y()+1)));
					moves.append((QPoint(getCoord().x()+1 , getCoord().y()+1)));
				}
			}
		}

	}
	//Si es una pieza blanca
	else
	{
		//Movimiento hacia adelante
		for (int i = 1 ; i < 2 + firstMove && getCoord().y()-1 >= 0 ; i++)
		{
			if (tablero[getCoord().x()][getCoord().y()-i]->getColor() != VACIA)
				break;
			else
				moves.append(QPoint(getCoord().x() , getCoord().y()-i));
		}
		if (getCoord().y()-1 <= 7)
		{
			if (getCoord().x()-1 > 0)
			{
				//Comer en la diagonal
				if(tablero[getCoord().x()-1][getCoord().y()-1]->getColor() != VACIA
						&& tablero[getCoord().x()-1][getCoord().y()-1]->getColor() != this->getColor())
				{
					moves.append(QPoint(getCoord().x()-1 , getCoord().y()-1));
				}
				//Captura paso
				if(tablero[getCoord().x()-1][getCoord().y()]->getPieza() == PEON
						&& tablero[getCoord().x()-1][getCoord().y()]->getSpecialA() == true
						&& tablero[getCoord().x()-1][getCoord().y()]->getColor() != getColor())
				{
					qDebug() << "Captura a paso - 1";
					capturaPaso = true;
					captura.append((QPoint(getCoord().x()-1 , getCoord().y()-1)));
					moves.append((QPoint(getCoord().x()-1 , getCoord().y()-1)));
				}
			}
			if (getCoord().x()+1 <= 7)
			{
				//Comer en diagonal
				if(tablero[getCoord().x()+1][getCoord().y()-1]->getColor() != VACIA
						&& tablero[getCoord().x()+1][getCoord().y()-1]->getColor() != this->getColor())
				{
					moves.append(QPoint(getCoord().x()+1 , getCoord().y()-1));
				}
				//Captura paso
				if(tablero[getCoord().x()+1][getCoord().y()]->getPieza() == PEON
						&& tablero[getCoord().x()+1][getCoord().y()]->getSpecialA() == true
						&& tablero[getCoord().x()+1][getCoord().y()]->getColor() != getColor())
				{
					qDebug() << "Captura a paso + 1";
					capturaPaso = true;
					captura.append((QPoint(getCoord().x()+1 , getCoord().y()-1)));
					moves.append((QPoint(getCoord().x()+1 , getCoord().y()-1)));
				}
			}

		}
	}
	return moves;
}

void piezas::peon::positionChanged(QPoint nCoord)
{
	/*Comprobar si se movio a una casilla donde se realiza
	la captura a paso*/
	if (capturaPaso == true)
	{
		for (int i = 0; i<captura.size(); i++)
		{
			qDebug() << "CapturaPaso";
			if(captura[i] == nCoord && getColor() == NEGRA)
			{
				delete tablero[nCoord.x()][nCoord.y()-1];
				tablero[nCoord.x()][nCoord.y()-1] = new piezaBase(nullptr,QPoint(nCoord.x(),nCoord.y()-1));
			}
			if(captura[i] == nCoord && getColor() == BLANCA)
			{
				delete tablero[nCoord.x()][nCoord.y()+1];
				tablero[nCoord.x()][nCoord.y()+1] = new piezaBase(nullptr,QPoint(nCoord.x(),nCoord.y()+1));
			}
		}
		capturaPaso = false;
		captura.clear();
	}
	firstMove = false;
	setSpecialA(false);
	if (firstMove == false && count == 1)
	{
		setSpecialA(true);
		count = 0;
	}
}

void piezas::peon::update()
{
	if (count == 0)
		setSpecialA(false);
}

bool piezas::peon::getFirstMove()
{
	return firstMove;
}
