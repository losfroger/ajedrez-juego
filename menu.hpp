#ifndef MENU_HPP
#define MENU_HPP

#include <QMainWindow>
#include <QPixmap>
#include <QDebug>

#include "acerca/acercade.h"
#include "error/error.h"
#include "game/tablero.h"

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
		Q_OBJECT

	public:
		explicit menu(QWidget *parent = nullptr);
		~menu();

	private slots:
		void on_salir_clicked();

		void on_acerca_clicked();

		void on_jugar_clicked();

	private:
		Ui::menu *ui;
		acercaDe *acerca;
		tablero *juego;
};

#endif // MENU_HPP
