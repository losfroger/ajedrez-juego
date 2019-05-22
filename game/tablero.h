#ifndef TABLERO_H
#define TABLERO_H

//Libreria de que es un dialogo
#include <QDialog>
//Librerias graficas
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
//Tipos de datos
#include <QPoint>
//Clases de las piezas
#include "game/clases/peon.h"
#include "game/clases/torre.h"
#include "game/clases/caballo.h"
#include "game/clases/alfil.h"
#include "game/clases/rey.h"
#include "game/clases/reina.h"


#include <QtDebug>

namespace Ui {
class tablero;
}

using namespace piezas;

///Ventana de juego
/**
Contiene:

- El tablero
- El log
- Indicador de quien es el turno*/
class tablero : public QDialog
{
	Q_OBJECT

	public:
		explicit tablero (QWidget *parent = nullptr);
		~tablero();

	private:
		int turno;
		Ui::tablero *ui;
		QGraphicsScene *scene; //!< Escena donde se ponen las imagenes
		piezaBase ***matrizPiezas; //!< Matriz de las piezas del tablero

	public slots:
		///Cuando se mueve una pieza
		/**
		Las coordenadas se expresan en coordenadas del tablero
		@param [in] oldCoord Coordenada anterior
		@param [in] newCoord Corrdenada nueva*/
		void piezaMovida (QPoint oldCoord, QPoint newCoord);
		///Hacer seleccionable un equipo
		/**
		@param [in] team Equipo al que se va a hacer seleccionable
		@param [in] changeT Si se va a cambiar de turno*/
		void teamSelectable (colorP team, bool changeT);
		///Hacer NO seleccionable un equipo
		/**
		@param [in] team Equipo al que se va a hacer NO seleccionable
		@param [in] changeT Si se va a cambiar de turno*/
		void teamUnselectable (colorP team, bool changeT);
};

#endif // TABLERO_H
