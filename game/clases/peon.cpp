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
}

QList<QPoint> peon::movimientos()
{
	QList <QPoint> moves;
	moves.append(QPoint(this->x(),this->y()+67));
	moves.append(QPoint(this->x(),this->y()+134));


	return moves;
}
