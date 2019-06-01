#ifndef REY_H
#define REY_H


#include "game/clases/piezabase.h"

namespace piezas {

///Pieza rey
/**
rey*/
class rey : public casillaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
        rey(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA, casillaBase ***nTablero = nullptr);

		///Constructor copia
		rey(const casillaBase &other);

        virtual void positionChanged(QPoint nCoord);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();
	private:
        QList<QPoint> Enroque;

        bool fistMove; // para saber si ya se movio por primera vez
};


}
#endif // REY_H
