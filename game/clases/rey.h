#ifndef REY_H
#define REY_H


#include "game/clases/piezabase.h"

namespace piezas {

///Pieza rey
/**
rey*/
class rey : public piezaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
        rey(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA, piezaBase ***nTablero = nullptr);

		///Constructor copia
		rey(const piezaBase &other);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();
	private:
};


}
#endif // REY_H
