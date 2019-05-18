#ifndef PIEZABASE_H
#define PIEZABASE_H

#include <QCoreApplication>

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include <QString>
#include <QPoint>
#include <QList>

#include <QDebug>

#include "game/clases/cuadroselect.h"

enum tipoPieza
{
	BASE,
	PEON,
	CABALLO,
	ALFIL,
	TORRE,
	REINA,
	REY
};

//Tamaño del cuadrado
const int TAM_CUADRO = 71;
//Tamaño del espacio donde estan los numeros y letras
const int TAM_SANGRIA = 16;


class piezaBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	public:
		/**
		@param [in] parent Padre del objeto
		@param [in] coordI Coordenada inicial en el tablero (va de 0,0 a 7,7)
		@param [in] iColor Color inicial de la pieza (0 = blanca, 1 = negra)*/
		piezaBase(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), bool iColor = 0, tipoPieza iPieza = BASE);
		///Destructor
		virtual ~piezaBase();
		/**
		@return Una QList de los movimientos posibles de la pieza*/
		virtual QList<QPoint> movimientos();

		void cambiarPos(QPoint newPos);
		///Regresa la posicion actual en el tablero de la pieza
		QPoint getPos();
		///Evento de click con el mouse en la pieza
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

	public slots:
		///Se activa cuando se escoge una de las cajas de movimiento
		/**
		Elimina todas las cajas de seleccion y establece la nueva posicion de la pieza*/
		void move(QPoint coordT);
	private:
		tipoPieza pieza; //!Tipo de pieza
		QPoint coordTablero; //!Posicion de la pieza en el tablero
		bool color; //!Blanco = 0, negro = 1
};

#endif // PIEZABASE_H
