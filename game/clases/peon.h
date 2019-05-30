#ifndef PEON_H
#define PEON_H

#include "game/clases/piezabase.h"


namespace piezas {

///Pieza peon
/**
# Valor
- 1 Punto

# Movimientos:

- P = Peon
- X = Movimientos posibles

##Primer turno:

 _    | _    | _   
 :--: | :--: | :--:
 '    | '    | '
 '    | X    | '
 '    | X    | '
 '    | p    | '
 '    | '    | '

 ## Demas turnos:
 _    | _    | _
 :--: | :--: | :--:
 '    | '    | '
 '    | '    | '
 '    | X    | '
 '    | p    | '
 '    | '    | '

*/
class peon : public piezaBase
{
	public:
		///Constructor
		/**
		@param [in] parent Padre objeto
		@param [in] coordI Coordenada del tablero donde va a estar la pieza
		@param [in] iColor Color de la pieza*/
		peon(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA, piezaBase ***nTablero = nullptr);

		///Constructor copia
		peon(const piezaBase &other);

		///Lista de movimientos de la pieza
		/**
		Funcion que calcula los movimientos que puede hacer la pieza
		@return Lista con los movimientos posibles expresados en coordenadas del tablero*/
		QList<QPoint> movimientos();

		void positionChanged(QPoint nCoord);
		void update();

		bool getFirstMove();

	private:

		QList <QPoint> captura;

		int count;
		bool firstMove; //!< Si es el primer movimiento del peon
		bool capturaPaso;

	signals:
		void capturaPasoSignal(QPoint coord);

};


}

#endif // PEON_H
