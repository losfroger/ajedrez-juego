#include "tablero.h"
#include "ui_tablero.h"

tablero::tablero(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::tablero)
{
	ui->setupUi(this);

	//Crear la escena
	scene = new QGraphicsScene;
	scene->setSceneRect(0,0,600,600);

	//Configurar la vista del juego
	ui->gameView->setScene(scene);
	ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	//Mostrar imagen de fondo del tablero
	QGraphicsPixmapItem *tablero = new QGraphicsPixmapItem;
	QString routeTablero = QCoreApplication::applicationDirPath() + "/resources/tablero.png";
	tablero->setPixmap(routeTablero);
	scene->addItem(tablero);

	//Inicializar el tablero con casillas vacias
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j<8; j++)
		{
			matrizPiezas[i][j] = new piezaBase(nullptr,QPoint(i,j),0);
		}
	}

	//TEST
	//Crear peones negros
	for (int i = 0; i <  8; i++)
	{
		matrizPiezas[i][1] = new peon(nullptr,QPoint(i,1),1);
		connect(matrizPiezas[i][1], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
		scene->addItem(matrizPiezas[i][1]);
	}
	//Crear un peon blanco
	matrizPiezas[0][3] = new peon(nullptr,QPoint(0,3),0);
	connect(matrizPiezas[0][3], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
	scene->addItem(matrizPiezas[0][3]);


	//Asignar la escena a la ventana de juego
	ui->gameView->setScene(scene);
}

tablero::~tablero()
{
	delete ui;
}

void tablero::piezaMovida(QPoint oldCoord, QPoint newCoord)
{
	qDebug() << "Slot tablero! " << oldCoord << "," << newCoord;
	//Si no es una casilla vacia, eliminar el objeto de la escena
	if(matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() != BASE)
		scene->removeItem(matrizPiezas[newCoord.x()][newCoord.y()]);
	//Mover la pieza a la posicion nueva
	matrizPiezas[newCoord.x()][newCoord.y()] = matrizPiezas[oldCoord.x()][oldCoord.y()];
	//Hacer que la posicion anterior este vacia
	matrizPiezas[oldCoord.x()][oldCoord.y()] = new piezaBase(nullptr,QPoint(oldCoord.x(),oldCoord.y()));
}
