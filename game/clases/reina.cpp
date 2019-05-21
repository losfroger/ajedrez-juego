#include "reina.h"

piezas::reina::reina(QGraphicsItem *parent, QPoint coordI, colorP iColor) : piezaBase (parent, coordI, iColor, REINA)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0reina.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1reina.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::reina::reina(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::reina::movimientos()
{
	QList <QPoint> moves;
	return moves;
}
