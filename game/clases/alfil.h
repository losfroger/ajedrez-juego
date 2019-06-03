#ifndef ALFIL_H
#define ALFIL_H

#include "game/clases/casillabase.h"

namespace piezas {

///Pieza alfil
/**
# Valor
- 3 Puntos

# Movimientos:

- Al = Alfil
- X = Movimientos posibles

_	 | _    | _    | _    | _
:--: | :--: | :--: | :--: | :--:
X	 | '    | '    | '    | X
'    | X    | '    | X    | '
'	 | '    | Al   | '    | '
'    | X    | '    | X    | '
X	 | '    | '    | '    | X
*/
class alfil : public casillaBase
{
    public:
        ///Constructor
        /**
        @param [in] parent Padre objeto
        @param [in] coordI Coordenada del tablero donde va a estar la pieza
        @param [in] iColor Color de la pieza*/
        alfil(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA,casillaBase ***nTablero = nullptr);

        ///Constructor copia
        alfil(const casillaBase &other);

        ///Lista de movimientos de la pieza
        /**
        Funcion que calcula los movimientos que puede hacer la pieza
        @return Lista con los movimientos posibles expresados en coordenadas del tablero*/
        QList<QPoint> movimientos();
    private:
};

}
#endif // ALFIL_H
