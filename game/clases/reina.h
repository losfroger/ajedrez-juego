#ifndef REINA_H
#define REINA_H


#include "game/clases/piezabase.h"

namespace piezas {

///Pieza reina
/**
reina*/
class reina : public piezaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
		reina(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA);

		///Constructor copia
		reina(const piezaBase &other);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();
	private:
};


}
#endif // REINA_H
