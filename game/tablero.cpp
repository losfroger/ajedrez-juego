#include "tablero.h"
#include "ui_tablero.h"

tablero::tablero(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::tablero)
{
	ui->setupUi(this);

	scene = new QGraphicsScene;

	//Configurar la vista del juego
	ui->gameView->setScene(scene);
	ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

tablero::~tablero()
{
	delete ui;
}
