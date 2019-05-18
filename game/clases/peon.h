#ifndef PEON_H
#define PEON_H

#include "game/clases/piezabase.h"

class peon : public piezaBase
{
	public:
		peon(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), bool iColor = 0);
		QList<QPoint> movimientos();
};

#endif // PEON_H
