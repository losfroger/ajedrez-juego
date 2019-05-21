#include "caballo.h"

piezas::caballo::caballo(QGraphicsItem *parent, QPoint coordI, colorP iColor) : piezaBase (parent, coordI, iColor, CABALLO)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0caballo.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1caballo.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::caballo::caballo(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::caballo::movimientos()
{
	QList <QPoint> moves;
	return moves;
}
