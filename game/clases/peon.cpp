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
}

piezas::peon::peon(const piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::peon::movimientos()
{
	QList <QPoint> moves;
	//Si es una pieza negra
	if (this->getColor() == NEGRA)
	{
		for (int i = 1 ; i < 2 + firstMove && getCoord().y()+1 <= 7 ; i++)
		{
			if (tablero[getCoord().x()][getCoord().y()+i]->getColor() == this->getColor())
				break;
			else
				moves.append(QPoint(getCoord().x() , getCoord().y()+i));
		}
		/*
		if(firstMove == true)
		{
			if (this->getCoord().y()+2 <= 7
				&& this->tablero[getCoord().x()][getCoord().y()+2]->getColor() != this->getColor())
				//Indica que se puede mover dos casillas abajo en y
				moves.append(QPoint(getCoord().x() , getCoord().y()+2));
		}
		if(this->getCoord().y()+1 <= 7 && this->tablero[getCoord().x()][getCoord().y()+1]->getColor() != this->getColor())
			moves.append(QPoint(getCoord().x() , getCoord().y()+1));*/
	}
	//Si es una pieza blanca
	else
	{
		for (int i = 1 ; i < 2 + firstMove && getCoord().y()-1 >= 0 ; i++)
		{
			if (tablero[getCoord().x()][getCoord().y()-i]->getColor() == this->getColor())
				break;
			else
				moves.append(QPoint(getCoord().x() , getCoord().y()-i));
		}
		/*
		if(firstMove == true)
		{
			if (this->getCoord().y()-2 >= 0 && this->tablero[getCoord().x()][getCoord().y()-2]->getColor() != this->getColor())
				moves.append(QPoint(getCoord().x() , getCoord().y()-2));
		}
		if(this->getCoord().y()-1 >= 0 && this->tablero[getCoord().x()][getCoord().y()-1]->getColor() != this->getColor())
			moves.append(QPoint(getCoord().x() , getCoord().y()-1));*/
	}
	return moves;
}

void piezas::peon::positionChanged()
{
	firstMove = false;
}
