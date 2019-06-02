#include "menu.hpp"
#include <QApplication>

//Funcion main, muestra el menu inicial
int main(int argc, char *argv[])
{
	//change
	//change 2
	QApplication a(argc, argv);
	menu w;
	w.show();

	return a.exec();
}
