#include "peon.h"

piezas::peon::peon(QGraphicsItem *parent, QPoint coordI, bool iColor) : piezaBase (parent, coordI, iColor, PEON)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == 0)
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
	if (this->getColor() == 1)
	{
		if(firstMove == true)
		{
			if (this->getCoord().y()+2 <= 7)
				//Indica que se puede mover dos casillas abajo en y
				moves.append(QPoint(getCoord().x() , getCoord().y()+2));
		}
		if(this->getCoord().y()+1 <= 7)
			moves.append(QPoint(getCoord().x() , getCoord().y()+1));
	}
	//Si es una pieza blanca
	else
	{
		if(firstMove == true)
		{
			if (this->getCoord().y()-2 >= 0)
				moves.append(QPoint(getCoord().x() , getCoord().y()-2));
		}
		if(this->getCoord().y()-1 >= 0)
			moves.append(QPoint(getCoord().x() , getCoord().y()-1));
	}
	return moves;
}

void piezas::peon::positionChanged()
{
	firstMove = false;
}
