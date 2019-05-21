#include "torre.h"

piezas::torre::torre(QGraphicsItem *parent, QPoint coordI, colorP iColor) : piezaBase (parent, coordI, iColor, TORRE)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0torre.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1torre.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::torre::torre(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::torre::movimientos()
{
	QList <QPoint> moves;
	return moves;
}
