#include "menu.hpp"
#include "ui_menu.h"

#include "game/global.hpp"
tablero *juego;

menu::menu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::menu)
{
	ui->setupUi(this);

	//Poner imagen del menu
	QString s = QCoreApplication::applicationDirPath() + "/resources/menu.png";
	QPixmap menuImage;
	//Si carga de manera correcta carga la imagen
	if (menuImage.load(s) == true)
	{
		ui->image->setPixmap(menuImage);
	}
	//Si no logra cargar la imagen muestra un error
	else
	{
		qDebug() << s;
		error errorImageLoad(this,"[ERROR]\nError al cargar los recursos, revisa que tengas la carpeta de 'resources' junto con el ejecutable");
		errorImageLoad.exec();
		this->close();
	}
}

menu::~menu()
{
	delete ui;
}

//Cerrar la ventana si se le da click al boton de salir
void menu::on_salir_clicked()
{
	this->close();
}

//Abrir el dialogo de acerca de si se le da click al boton
void menu::on_acerca_clicked()
{
	acerca = new acercaDe(this);
	acerca->exec();
	delete  acerca;
}

//Abrir la ventana de juego
void menu::on_jugar_clicked()
{
	juego = new tablero(this);
	juego->exec();
	delete juego;
}
