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
		explicit tablero(QWidget *parent = nullptr);
		~tablero();

	private:
		Ui::tablero *ui;
		QGraphicsScene *scene;
		QGraphicsPixmapItem *pieza;
		piezaBase *matrizPiezas[8][8];

	public slots:
		void piezaMovida(QPoint oldCoord, QPoint newCoord);
};

#endif // TABLERO_H
