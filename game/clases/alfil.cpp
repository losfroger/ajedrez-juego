#include "alfil.h"

piezas::alfil::alfil(QGraphicsItem *parent, QPoint coordI, bool iColor) : piezaBase (parent, coordI, iColor, ALFIL)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == 0)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0alfil.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1alfil.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::alfil::alfil(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::alfil::movimientos()
{
	QList <QPoint> moves;
	return moves;
}

