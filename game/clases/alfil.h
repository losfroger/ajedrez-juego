#ifndef ALFIL_H
#define ALFIL_H

#include "game/clases/piezabase.h"

namespace piezas {

///Pieza alfil
/**
alfil*/
class alfil : public piezaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
		alfil(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), bool iColor = 0);

		///Constructor copia
		alfil(const piezaBase &other);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();
	private:
};

}
#endif // ALFIL_H
