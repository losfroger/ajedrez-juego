#ifndef TABLERO_H
#define TABLERO_H

#include <QDialog>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTextBrowser>
#include <QtDebug>

#include "game/clases/peon.h"

namespace Ui {
class tablero;
}

class tablero : public QDialog
{
		Q_OBJECT

	public:
		explicit tablero(QWidget *parent = nullptr);
		~tablero();

	private:
		Ui::tablero *ui;
		QTextBrowser *log;
		QGraphicsScene *scene;
		QGraphicsPixmapItem *pieza;
};

#endif // TABLERO_H
