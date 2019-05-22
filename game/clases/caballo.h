#ifndef CABALLO_H
#define CABALLO_H


#include "game/clases/piezabase.h"

namespace piezas {

///Pieza caballo
/**
Caballo*/
class caballo : public piezaBase
{
    public:
        ///Constructor
        /**
        @param [in] parent Padre objeto
        @param [in] coordI Coordenada del tablero donde va a estar la pieza
        @param [in] iColor Color de la pieza*/
        caballo(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), colorP iColor = BLANCA, piezaBase ***nTablero = nullptr);

        ///Constructor copia
        caballo(const piezaBase &other);

        ///Lista de movimientos de la pieza
        /**
        Funcion que calcula los movimientos que puede hacer la pieza
        @return Lista con los movimientos posibles expresados en coordenadas del tablero*/
        QList<QPoint> movimientos();
    private:
};


}

#endif // CABALLO_H
