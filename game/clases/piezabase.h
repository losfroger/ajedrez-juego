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

enum colorP
{
	VACIA,
	BLANCA,
	NEGRA
};


namespace piezas {

using namespace piezas;

///Pieza base
/**
BLANCA = blanco , NEGRA = negra

Implementa:
- El click en el objeto
- El evento cuando se mueve la pieza
- La señal de cuando se mueve la pieza*/
class piezaBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	public:
		///Constructor
		/**
		@param [in] parent Padre del objeto
		@param [in] coordI Coordenada inicial en el tablero (va de 0,0 a 7,7)
		@param [in] iColor Color inicial de la pieza (0 = blanca, 1 = negra)*/
		piezaBase(QGraphicsItem *parent=nullptr, QPoint coordI = QPoint(0,0),
				  colorP iColor = VACIA, tipoPieza iPieza = BASE, piezaBase ***nTablero = nullptr);
		///Constructor copia
		piezaBase(const piezaBase &other);

		///Destructor
		virtual ~piezaBase();
		///Lista de movimientos de la pieza
		/**
		@return Una QList de los movimientos posibles de la pieza
		(expresados en coordenadas del tablero)*/
		virtual QList<QPoint> movimientos();

		///Evento de click con el mouse en la pieza
		/**
		Manda a llamar la funcion de movimientos y a partir de eso
		genera los cuadrados de a donde se puede llamar la pieza.

		Falta implementar que revise si se puede seleccionar y si esta
		seleccionada, poder deseleccionarla.*/
		void mousePressEvent(QGraphicsSceneMouseEvent *event);

		///Funcion llamada cuando se movio la pieza
		/**
		Util en casos como el del peon, que necesita saber cuando ya se ha movido*/
		virtual void positionChanged();


		//SETTERS AND GETTERS
		///Cambiar el valor del tipo de pieza
		void setPieza (tipoPieza newPieza) {pieza = newPieza;}
		///Conseguir el valor del tipo de pieza
		tipoPieza getPieza() const {return pieza;}

		///Cambiar las coordenadas en el tablero
		void setCoord(QPoint newPos) {coordTablero = newPos;}
		///Conseguir las coordenadas en el tablero
		QPoint getCoord() const {return coordTablero;}

		///Cambiar el color de la pieza (0 = blanco, 1 = negro)
		void setColor (colorP newColor) {color = newColor;}
		///Conseguir el color de la pieza
		colorP getColor() const {return color;}

		///Cambiar si la pieza se puede seleccionar o no
		void setSelectable(bool newS) {selectable = newS;}
		///Conseguir si la pieza se puede seleccionar o no
		bool getSelectable() const {return selectable;}

	public slots:
		///Se activa cuando se escoge una de las cajas de movimiento
		/**
		Elimina todas las cajas de seleccion y establece la nueva posicion de la pieza
		@param [in] coordT las nuevas coordenadas en el tablero de la pieza*/
		void move(QPoint coordT);
	signals:
		///Mandar señal al tablero de que se movio la pieza
		/**
		Manda las coordenadas viejas y nuevas de la pieza*/
		void piezaMoved(QPoint oldCoord, QPoint newCoord);
		///Hacer que todas las piezas del mismo equipo se puedan seleccionar
		void teamSelect(colorP team);
		///Hacer que todas las piezas del mismo equipo NO se puedan seleccionar
		void teamUnselect(colorP team);

	protected:
		piezaBase ***tablero;
	private:
		tipoPieza pieza; //!< Tipo de pieza
		QPoint coordTablero; //!< Posicion de la pieza en el tablero
		colorP color;
		bool selectable; //!< Si se puede seleccionar la pieza
};

}

#endif // PIEZABASE_H
