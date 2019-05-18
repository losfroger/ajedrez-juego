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

QList<QPoint> peon::movimientos()
{
	QList <QPoint> moves;
	if(firstMove == true)
	{
		if (this->getPos().y()+2 < 8)
		moves.append(QPoint(this->getPos().x(),this->getPos().y()+2));
	}
	if(this->getPos().y()+1 < 8)
		moves.append(QPoint(this->getPos().x(),this->getPos().y()+1));

	firstMove = false;
	return moves;
}
