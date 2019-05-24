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

    //TABLERO DINAMICO
    matrizPiezas = new piezaBase**[8];
    for (int i = 0; i < 8; i++)
        matrizPiezas[i] = new piezaBase*[8];

    //Inicializar el tablero con casillas vacias
    for (int i = 0; i<8; i++)
    {
        for (int j = 0; j<8; j++)
			matrizPiezas[i][j] = new piezaBase(tablero,QPoint(i,j),VACIA,BASE,matrizPiezas);
    }

    //TEST TABLERO
    //Crear peones negros
    for (int i = 0; i <  8; i++)
    {
		matrizPiezas[i][1] = new peon(tablero,QPoint(i,1),NEGRA,matrizPiezas);
        //connect(matrizPiezas[i][1], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
        scene->addItem(matrizPiezas[i][1]);
    }
    //Crear peones blancos
    for (int i = 0; i <  8; i++)
    {
		matrizPiezas[i][6] = new peon(tablero,QPoint(i,6),BLANCA,matrizPiezas);
        //connect(matrizPiezas[i][6], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
        scene->addItem(matrizPiezas[i][6]);
    }
    //Crear torres
    for (int i = 0 ; i < 8; i+=7)
    {
        for (int j = 0; j < 8 ; j+= 7)
        {
            if(j>0)
				matrizPiezas[i][j] = new torre(tablero,QPoint(i,j),BLANCA, matrizPiezas);
            else
				matrizPiezas[i][j] = new torre(tablero,QPoint(i,j),NEGRA, matrizPiezas);
            //connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
            scene->addItem(matrizPiezas[i][j]);
        }
    }
    //Crear caballos
    for (int i = 1 ; i < 8; i+=5)
    {
        for (int j = 0; j < 8 ; j+= 7)
        {
            if(j>0)
				matrizPiezas[i][j] = new caballo(tablero,QPoint(i,j),BLANCA, matrizPiezas);
            else
				matrizPiezas[i][j] = new caballo(tablero,QPoint(i,j),NEGRA, matrizPiezas);
            //connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
            scene->addItem(matrizPiezas[i][j]);
        }
    }
    //Crear alfiles
    for (int i = 2 ; i < 8; i+=3)
    {
        for (int j = 0; j < 8 ; j+= 7)
        {
            if(j>0)
				matrizPiezas[i][j] = new alfil(tablero,QPoint(i,j),BLANCA,matrizPiezas);
            else
				matrizPiezas[i][j] = new alfil(tablero,QPoint(i,j),NEGRA,matrizPiezas);
            //connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
            scene->addItem(matrizPiezas[i][j]);
        }
    }
    //Crear reinas
    int i = 3;
    for (int j = 0; j < 8 ; j+= 7)
    {
        if(j>0)
            matrizPiezas[i][j] = new reina(tablero,QPoint(i,j),BLANCA, matrizPiezas);
        else
            matrizPiezas[i][j] = new reina(tablero,QPoint(i,j),NEGRA, matrizPiezas);
        //connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
        scene->addItem(matrizPiezas[i][j]);
    }
    i = 4;
    //Crear reyes
    for (int j = 0; j < 8 ; j+= 7)
    {
        if(j>0)
            matrizPiezas[i][j] = new rey(tablero,QPoint(i,j),BLANCA,matrizPiezas);
        else
            matrizPiezas[i][j] = new rey(tablero,QPoint(i,j),NEGRA,matrizPiezas);
        //connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
        scene->addItem(matrizPiezas[i][j]);
    }

    //Conectar señales
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (matrizPiezas[i][j]->getPieza() != BASE)
            {
                connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint,QPoint)), this, SLOT(piezaMovida(QPoint,QPoint)));
				connect(matrizPiezas[i][j], SIGNAL(teamSelect(colorP, bool)), this, SLOT(teamSelectable(colorP, bool)));
				connect(matrizPiezas[i][j], SIGNAL(teamUnselect(colorP, bool)), this, SLOT(teamUnselectable(colorP, bool)));
            }
        }
    }

    //Hacer que el primer turno sea de las piezas blancas
	teamSelectable(BLANCA, true);
	teamUnselectable(NEGRA, false);

    //Asignar la escena a la ventana de juego
    ui->gameView->setScene(scene);
}

tablero::~tablero()
{
    for (int w = 0; w < 8; w++)
        delete[] matrizPiezas[w];
    delete[] matrizPiezas;
    delete ui;
}

void tablero::piezaMovida(QPoint oldCoord, QPoint newCoord)
{
    qDebug() << "Slot tablero! " << oldCoord << "," << newCoord;

	teamUnselectable(matrizPiezas[oldCoord.x()][oldCoord.y()]->getColor(),true);
    if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getColor() == BLANCA)
		teamSelectable(NEGRA, true);
    else
		teamSelectable(BLANCA, true);

    //Si no es una casilla vacia, eliminar el objeto de la escena
    if(matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() != BASE)
        scene->removeItem(matrizPiezas[newCoord.x()][newCoord.y()]);

    //Mover la pieza a la posicion nueva
    matrizPiezas[newCoord.x()][newCoord.y()] = matrizPiezas[oldCoord.x()][oldCoord.y()];

    //Hacer que la posicion anterior este vacia
    matrizPiezas[oldCoord.x()][oldCoord.y()] = new piezaBase(nullptr,QPoint(oldCoord.x(),oldCoord.y()));

    //Escribir en el log
    QString texto;
    if (matrizPiezas[newCoord.x()][newCoord.y()]->getColor() == BLANCA)
        texto += "[Blancas] ";
    else
        texto += "[Negras] ";

    texto += "[" + QString::number(oldCoord.x()) + "," + QString::number(oldCoord.y()) + "] a ["
             + QString::number(newCoord.x()) + "," + QString::number(newCoord.y()) + "]";

    ui->log->append(texto);



}

void tablero::teamSelectable(colorP team, bool changeT)
{
    qDebug() << "Team selectable " << team;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (matrizPiezas[i][j]->getPieza() != BASE && matrizPiezas[i][j]->getColor() == team)
            {
                matrizPiezas[i][j]->setSelectable(true);
				if(changeT == true)
					matrizPiezas[i][j]->setTurno(true);
                matrizPiezas[i][j]->update();
            }
        }
    }
}

void tablero::teamUnselectable(colorP team, bool changeT)
{
    qDebug() << "Team unselectable " << team;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (matrizPiezas[i][j]->getPieza() != BASE && matrizPiezas[i][j]->getColor() == team)
            {
                matrizPiezas[i][j]->setSelectable(false);
				if(changeT == true)
					matrizPiezas[i][j]->setTurno(false);
            }
        }
    }
}
