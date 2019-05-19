#include "peon.h"

peon::peon(QGraphicsItem *parent, QPoint coordI, bool iColor) : piezaBase (parent, coordI, iColor, PEON)
{
	QString routeImage;
	if (iColor == 0)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0peon.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1peon.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
	firstMove = true;
}

peon::peon(const piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> peon::movimientos()
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

		firstMove = false;
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

		firstMove = false;
	}
	return moves;
}
