#include "menu.hpp"
#include <QApplication>

//Funcion main, muestra el menu inicial
int main(int argc, char *argv[])
{
	//change
	QApplication a(argc, argv);
	menu w;
	w.show();

	return a.exec();
}
