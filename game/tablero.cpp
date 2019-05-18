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

	QGraphicsPixmapItem *tablero = new QGraphicsPixmapItem;
	QString routeTablero = QCoreApplication::applicationDirPath() + "/resources/tablero.png";
	tablero->setPixmap(routeTablero);
	scene->addItem(tablero);

	//peon *peonA = new peon(nullptr,QPoint(200,200),0);
	peon *peonB = new peon(nullptr,QPoint(32,32),1);
	//scene->addItem(peonA);
	scene->addItem(peonB);

	ui->gameView->setScene(scene);
}

tablero::~tablero()
{
	delete ui;
}
