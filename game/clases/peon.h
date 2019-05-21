#ifndef PEON_H
#define PEON_H

#include "game/clases/piezabase.h"

namespace piezas {

///Pieza peon
/**
Con implementacion de movimiento diferente su primer movimiento*/
class peon : public piezaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
		peon(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), bool iColor = 0);

		///Constructor copia
		peon(const piezaBase &other);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();

		void positionChanged();

	private:
		bool firstMove; //!< Si es el primer movimiento del peon
};


}

#endif // PEON_H
