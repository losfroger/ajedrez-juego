#include "menu.hpp"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::menu)
{
	ui->setupUi(this);

	//Configurar acerca de
	acerca = new acercaDe(this);

	//Poner imagen del menu
	QString s = QCoreApplication::applicationDirPath() + "/resources/menu.png";
	QPixmap menuImage;
	if (menuImage.load(s) == true)
	{
		ui->image->setPixmap(menuImage);
	}
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

void menu::on_salir_clicked()
{
	this->close();
}

void menu::on_acerca_clicked()
{
	acerca->exec();
}

void menu::on_jugar_clicked()
{
	hide();
	juego = new tablero(this);
	juego->exec();
	show();
}
