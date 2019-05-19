#ifndef PIEZABASE_H
#define PIEZABASE_H

/*Libreria que uso para saber donde se encuentra
la aplicacion y poder cargar las imagenes*/
#include <QCoreApplication>
//Libreria para señales y slots
#include <QObject>
//Librerias graficas
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
//Libreria de evento de mouse
#include <QGraphicsSceneMouseEvent>
//Librerias de tipos de datos
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

class piezaBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	public:
		/**
		@param [in] parent Padre del objeto
		@param [in] coordI Coordenada inicial en el tablero (va de 0,0 a 7,7)
		@param [in] iColor Color inicial de la pieza (0 = blanca, 1 = negra)*/
		piezaBase(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0), bool iColor = 0, tipoPieza iPieza = BASE);
		///Constructor copia
		piezaBase(const piezaBase &other);

		///Destructor
		virtual ~piezaBase();
		/**
		@return Una QList de los movimientos posibles de la pieza*/
		virtual QList<QPoint> movimientos();

		//SETTERS AND GETTERS
		void setPieza (tipoPieza newPieza) {pieza = newPieza;}
		tipoPieza getPieza() const {return pieza;}

		void setCoord(QPoint newPos) {coordTablero = newPos;}
		QPoint getCoord() const {return coordTablero;}

		void setColor (bool newColor) {color = newColor;}
		bool getColor() const {return color;}

		void setSelectable(bool newS) {selectable = newS;}
		bool getSelectable() const {return selectable;}


		///Evento de click con el mouse en la pieza
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

	public slots:
		///Se activa cuando se escoge una de las cajas de movimiento
		/**
		Elimina todas las cajas de seleccion y establece la nueva posicion de la pieza*/
		void move(QPoint coordT);

	signals:
		///Mandar señal al tablero de que se movio la pieza, con la coordenada vieja y la nueva
		void piezaMoved(QPoint oldCoord, QPoint newCoord);

	private:
		tipoPieza pieza; //!Tipo de pieza
		QPoint coordTablero; //!Posicion de la pieza en el tablero
		bool color; //!Blanco = 0, negro = 1
		bool selectable;
};

#endif // PIEZABASE_H
