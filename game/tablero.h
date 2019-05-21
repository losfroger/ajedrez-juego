#ifndef TABLERO_H
#define TABLERO_H

//Libreria de que es un dialogo
#include <QDialog>
//Librerias graficas
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
//Tipos de datos
#include <QPoint>

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
		void piezaMovida (QPoint oldCoord, QPoint newCoord);
		void teamSelectable (colorP team);
		void teamUnselectable (colorP team);
};

#endif // TABLERO_H
