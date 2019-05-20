#include "rey.h"

piezas::rey::rey(QGraphicsItem *parent, QPoint coordI, bool iColor) : piezaBase (parent, coordI, iColor, REY)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == 0)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0rey.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1rey.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::rey::rey(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::rey::movimientos()
{
	QList <QPoint> moves;
	return moves;
}
