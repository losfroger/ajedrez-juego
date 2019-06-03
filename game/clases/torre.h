#ifndef TORRE_H
#define TORRE_H


#include "game/clases/casillabase.h"

namespace piezas {

///Pieza torre
/**
# Valor
- 5 Puntos

# Movimientos:

- T = Alfil
- X = Movimientos posibles

_	 | _    | _    | _    | _
:--: | :--: | :--: | :--: | :--:
'	 | '    | X    | '    | '
'    | '    | X    | '    | '
X	 | X    | T    | X    | X
'    | '    | X    | '    | '
'	 | '    | X    | '    | '
Torre*/
class torre : public casillaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
		torre(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA,casillaBase ***nTablero = nullptr);

		///Constructor copia
		torre(const casillaBase &other);

        virtual void positionChanged(QPoint nCoord);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();
	private:
        bool specialA;
};


}

#endif // TORRE_H
