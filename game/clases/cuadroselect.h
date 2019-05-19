#ifndef CUADROSELECT_H
#define CUADROSELECT_H

//Libreria para mandar señales
#include <QObject>
//Librerias de cosas graficas
#include <QGraphicsScene>
#include <QGraphicsRectItem>
//Libreria del evento del mouse
#include <QGraphicsSceneMouseEvent>

#include <QDebug>

//Tamaño del cuadrado
const int TAM_CUADRO = 71;
//Tamaño del espacio donde estan los numeros y letras
const int TAM_SANGRIA = 16;


namespace piezas {

using namespace piezas;

///Cuadros de seleccion de movimientos
/**
Genera un cuadro de color verde a donde se puede mover la pieza

Implementa:
- Evento de click
- Señal que se manda cuando se le da click y da las coordenadas nuevas de la pieza*/
class cuadroSelect : public QObject, public QGraphicsRectItem
{
	Q_OBJECT
	public:
		///Constructor
		/**
		@param [in] parent Objeto padre
		@param [in] coordI Coordenada del tablero a donde se puede mover la pieza*/
		cuadroSelect(QGraphicsItem *parent = nullptr, QPoint coordI = QPoint(0,0));
		///Destructor
		~cuadroSelect();
	private:
		QPoint coordT; //!< Coordenada del tablero

		///Evento al hacer click con el mouse
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		///Señal que emite la coordenada del tablero cuando se escoge un movimiento
		/**
		Manda las coordenadas nuevas del objeto*/
		void selected(QPoint coordT);
};


}

#endif // CUADROSELECT_H
