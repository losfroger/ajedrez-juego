#include "tablero.h"
#include "game/global.hpp"
#include "ui_tablero.h"
#include <QPoint>

// Variable para activar al demostracion del ahogado
const bool demoahog = false;

tablero::tablero(QWidget* parent) : QDialog(parent), ui(new Ui::tablero){
  jaque_blancas = false;
  jaque_negras = false;
  jaque_mate_blancas = false;
  jaque_mate_negras = false;
  ahogado = false;

  ui->setupUi(this);

  // Crear la escena
  scene = new QGraphicsScene;
  scene->setSceneRect(0, 0, 600, 600);

  // Configurar la vista del juego
  ui->gameView->setScene(scene);
  ui->gameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  ui->gameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  // Mostrar imagen de fondo del tablero
  tableroBG = new QGraphicsPixmapItem;
  QString routeTablero =
	QCoreApplication::applicationDirPath() + "/resources/tablero.png";
  tableroBG->setPixmap(routeTablero);
  scene->addItem(tableroBG);

  // Generar el tablero
  matrizPiezas = new casillaBase**[8];
  for (int i = 0; i < 8; i++)
	matrizPiezas[i] = new casillaBase*[8];

  // Inicializar el tablero con casillas vacias
  for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++)
	  matrizPiezas[i][j] = new casillaBase(tableroBG, QPoint(i, j), VACIA, BASE, matrizPiezas);
  }

  // Agregar las piezas al tablero
  // Crear peones negros
  for (int i = 0; i < 8; i++) {
	if (!demoahog)
	  matrizPiezas[i][1] = new peon(tableroBG, QPoint(i, 1), NEGRA, matrizPiezas);
  }
  // Crear peones blancos
  for (int i = 0; i < 8; i++) {
	matrizPiezas[i][6] = new peon(tableroBG, QPoint(i, 6), BLANCA, matrizPiezas);
  }
  // Crear torres
  for (int i = 0; i < 8; i += 7) {
	for (int j = 0; j < 8; j += 7) {
	  if (j > 0)
		matrizPiezas[i][j] = new torre(tableroBG, QPoint(i, j), BLANCA, matrizPiezas);
	  else if (!demoahog)
		matrizPiezas[i][j] = new torre(tableroBG, QPoint(i, j), NEGRA, matrizPiezas);
	}
  }
  // Crear caballos
  for (int i = 1; i < 8; i += 5) {
	for (int j = 0; j < 8; j += 7) {
	  if (j > 0)
		matrizPiezas[i][j] = new caballo(tableroBG, QPoint(i, j), BLANCA, matrizPiezas);
	  else if (!demoahog)
		matrizPiezas[i][j] = new caballo(tableroBG, QPoint(i, j), NEGRA, matrizPiezas);
    }
  }
  // Crear alfiles
  for (int i = 2; i < 8; i += 3) {
	for (int j = 0; j < 8; j += 7) {
	  if (j > 0)
		matrizPiezas[i][j] = new alfil(tableroBG, QPoint(i, j), BLANCA, matrizPiezas);
	  else if (!demoahog)
		matrizPiezas[i][j] = new alfil(tableroBG, QPoint(i, j), NEGRA, matrizPiezas);
    }
  }
  // Crear reinas
  int i = 3;
  for (int j = 0; j < 8; j += 7) {
	if (j > 0)
	  matrizPiezas[i][j] = new reina(tableroBG, QPoint(i, j), BLANCA, matrizPiezas);
	else if (!demoahog)
	  matrizPiezas[i][j] = new reina(tableroBG, QPoint(i, j), NEGRA, matrizPiezas);
  }
  i = 4;
  // Crear reyes
  for (int j = 0; j < 8; j += 7) {
	if (j > 0) {
	  matrizPiezas[i][j] = new rey(tableroBG, QPoint(i, j), BLANCA, matrizPiezas);
	  coord_rey_blanco = QPoint(i, j);
	} else {
	  matrizPiezas[i][j] = new rey(tableroBG, QPoint(i, j), NEGRA, matrizPiezas);
	  coord_rey_negro = QPoint(i, j);
    }
  }

  // Conectar señales
  for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++) {
	  if (matrizPiezas[i][j]->getPieza() != BASE) {
		connect(matrizPiezas[i][j], SIGNAL(piezaMoved(QPoint, QPoint)), this, SLOT(piezaMovida(QPoint, QPoint)));
		connect(matrizPiezas[i][j], SIGNAL(teamSelect(colorP, bool)), this, SLOT(teamSelectable(colorP, bool)));
		connect(matrizPiezas[i][j], SIGNAL(teamUnselect(colorP, bool)), this, SLOT(teamUnselectable(colorP, bool)));
	  }
    }
  }

  // Hacer que el primer turno sea de las piezas blancas
  teamSelectable(BLANCA, true);
  teamUnselectable(NEGRA, false);

  ui->label->setText("Turno de las piezas Blancas");
  // Asignar la escena a la ventana de juego
  ui->gameView->setScene(scene);
}

tablero::~tablero() {
  // Regresar las variables globales a su estado original
  jaque_blancas = false;
  jaque_negras = false;
  jaque_mate_blancas = false;
  jaque_mate_negras = false;
  ahogado = false;

  for (int w = 0; w < 8; w++)
	delete[] matrizPiezas[w];
  delete[] matrizPiezas;
  delete ui;
}

void tablero::piezaMovida(QPoint oldCoord, QPoint newCoord) {
  // Variables para el log de movimientos del ajedrez
  char vX[8] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };
  char piezaMovimiento;
  QString textoLabel;

  qDebug() << "Slot tablero! " << oldCoord << "," << newCoord;

  // Hacer que el equipo contrario se pueda seleccionar al pasar el turno
  teamUnselectable(matrizPiezas[oldCoord.x()][oldCoord.y()]->getColor(), true);
  if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getColor() == BLANCA) {
	teamSelectable(NEGRA, true);
	qDebug() << "Coordenadas del rey negro = " << coord_rey_negro;
  } else {
	teamSelectable(BLANCA, true);
	qDebug() << "Coordenadas del rey blanco = " << coord_rey_blanco;
  }

  // seguimos las posiciones de los reyes
  if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getPieza() == REY) {
	if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getColor() == BLANCA) {
	  if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getJaque()) {
		jaque_blancas = false;
		matrizPiezas[oldCoord.x()][oldCoord.y()]->setJaque(0);
		arreglo_jaque_blancas.clear();
	  }

	  coord_rey_blanco = QPoint(newCoord.x(), newCoord.y());
	} else {
	  if (matrizPiezas[oldCoord.x()][oldCoord.y()]->getJaque()) {
		jaque_negras = false;
		matrizPiezas[oldCoord.x()][oldCoord.y()]->setJaque(0);
		arreglo_jaque_negras.clear();
	  }

	  coord_rey_negro = QPoint(newCoord.x(), newCoord.y());
    }
  }

  // Si no es una casilla vacia, eliminar el objeto de la escena
  if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() != BASE)
	scene->removeItem(matrizPiezas[newCoord.x()][newCoord.y()]);

  // Mover la pieza a la posicion nueva
  matrizPiezas[newCoord.x()][newCoord.y()] = matrizPiezas[oldCoord.x()][oldCoord.y()];

  // Hacer que la posicion anterior este vacia
  matrizPiezas[oldCoord.x()][oldCoord.y()] = new casillaBase(nullptr, QPoint(oldCoord.x(), oldCoord.y()));

  if (matrizPiezas[newCoord.x()][newCoord.y()]->getColor() == BLANCA) {
	matrizPiezas[coord_rey_negro.x()][coord_rey_negro.y()]->setJaque(
	  check(matrizPiezas, coord_rey_negro, NEGRA, &arreglo_jaque_negras));

	jaque_negras = ((check(matrizPiezas, coord_rey_negro, NEGRA) != 0) ? true : false);

	if (matrizPiezas[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque()) {
	  jaque_mate_negras = check_mate(matrizPiezas, NEGRA);

	  if (jaque_mate_negras) {
		jaque_negras = false;
		qDebug() << "\t\tMate de las negras";
	  }
	} else {
	  ahogado = check_mate(matrizPiezas, NEGRA);

	  if (ahogado)
		qDebug() << "\t\tAhogado de las negras";
	}

	if (matrizPiezas[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque())
	  matrizPiezas[coord_rey_blanco.x()][coord_rey_blanco.y()]->setJaque(0);

	if (check(matrizPiezas, coord_rey_negro,  NEGRA)) // borrar esto en la version final
	{
	  qDebug() << "\tCheck!!! de blancas a negras";
    }
  } else {
	matrizPiezas[coord_rey_blanco.x()][coord_rey_blanco.y()]->setJaque(
	  check(matrizPiezas, coord_rey_blanco, BLANCA, &arreglo_jaque_blancas));

	jaque_blancas =  ((check(matrizPiezas, coord_rey_blanco, BLANCA) != 0) ? true : false);

	if (matrizPiezas[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque()) {
	  jaque_mate_blancas = check_mate(matrizPiezas, BLANCA);

	  if (jaque_mate_blancas) {
		jaque_blancas = false;
		qDebug() << "\t\tMate de las blancas";
	  }
	} else {
	  ahogado = check_mate(matrizPiezas, BLANCA);

	  if (ahogado)
		qDebug() << "\t\tAhogado de las blancas";
	}

	if (matrizPiezas[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque())
	  matrizPiezas[coord_rey_negro.x()][coord_rey_negro.y()]->setJaque(0);

	if (check(matrizPiezas, coord_rey_blanco, BLANCA)) {
	  qDebug() << "\tCheck!!! de negras a blancas";
    }
  }

  // Escribir en el log
  QString texto;
  if (matrizPiezas[newCoord.x()][newCoord.y()]->getColor() == BLANCA) {

	texto += "Blanco:\t";

	if (jaque_negras == true) {
	  textoLabel = "Jaque";
	} else if (jaque_mate_negras == true) {
	  textoLabel = "Jaque Mate";
	} else if (ahogado == true) {
	  textoLabel = "Ahogado";
	} else {
	  textoLabel = "Turno de las piezas Negras";
    }
  } else {
	texto += "Negro:\t";

	if (jaque_blancas == true) {
	  textoLabel = "Jaque";
	} else if (jaque_mate_blancas == true) {
	  textoLabel = "Jaque Mate";
	} else if (ahogado == true) {
	  textoLabel = "Ahogado";
	} else {
	  textoLabel = "Turno de las piezas Blancas";
    }
  }

  if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() == REY) {
	piezaMovimiento = 'R';
  } else if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() == REINA) {
	piezaMovimiento = 'D';
  } else if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() == TORRE) {
	piezaMovimiento = 'T';
  } else if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() == ALFIL) {
	piezaMovimiento = 'A';
  } else if (matrizPiezas[newCoord.x()][newCoord.y()]->getPieza() == CABALLO) {
	piezaMovimiento = 'C';
  } else
	piezaMovimiento = 'P';

  texto += QString(piezaMovimiento) + QString(vX[oldCoord.x()]) + QString::number(8 - oldCoord.y()) + " -> " + QString(piezaMovimiento) + QString(vX[newCoord.x()]) + QString::number(8 - newCoord.y());

  if (jaque_blancas == true || jaque_negras == true)
	texto += " \u2020";

  if (jaque_mate_blancas == true || jaque_mate_negras == true)
	texto += " \u2020\u2020";

  if (ahogado == true)
	texto += " =";

  // Agregar texto al log
  ui->log->append(texto);
  // Poner el texto del label
  ui->label->setText(textoLabel);
}

void tablero::teamSelectable(colorP team, bool changeT) {
  qDebug() << "Team selectable " << team;
  for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++) {
	  if (matrizPiezas[i][j]->getPieza() != BASE &&
		  matrizPiezas[i][j]->getColor() == team) {
		matrizPiezas[i][j]->setSelectable(true);
		if (changeT == true) {
		  matrizPiezas[i][j]->setTurno(true);
		  matrizPiezas[i][j]->update();
        }
	  }
	}
  }
}

void tablero::teamUnselectable(colorP team, bool changeT) {
  qDebug() << "Team unselectable " << team;
  for (int i = 0; i < 8; i++) {
	for (int j = 0; j < 8; j++) {
	  if (matrizPiezas[i][j]->getPieza() != BASE && matrizPiezas[i][j]->getColor() == team) {
		matrizPiezas[i][j]->setSelectable(false);
		if (changeT == true)
		  matrizPiezas[i][j]->setTurno(false);
	  }
	}
  }
}

void tablero::promocion(int type, QPoint oldCoord, QPoint newCoord) {
  int xo = newCoord.x(), yo = newCoord.y();
  qDebug() << "\nPromocion: " << oldCoord << newCoord;
  // Borrar la pieza
  delete matrizPiezas[oldCoord.x()][oldCoord.y()];
  // Sustituirla por una nueva
  switch (type) {
	case 0:
	  matrizPiezas[xo][yo] = new reina( tableroBG, oldCoord, matrizPiezas[xo][yo]->getColor(), matrizPiezas);
	  break;
	case 1:
	  matrizPiezas[xo][yo] = new torre( tableroBG, oldCoord, matrizPiezas[xo][yo]->getColor(), matrizPiezas);
	  break;
	case 2:
	  matrizPiezas[xo][yo] = new alfil( tableroBG, oldCoord, matrizPiezas[xo][yo]->getColor(), matrizPiezas);
	  break;
	case 3:
	  matrizPiezas[xo][yo] = new caballo( tableroBG, oldCoord, matrizPiezas[xo][yo]->getColor(), matrizPiezas);
	  break;
	default:
	  matrizPiezas[xo][yo] = new reina( tableroBG, oldCoord, matrizPiezas[xo][yo]->getColor(), matrizPiezas);
	  break;
  }
  // Hacer que no se pueda seleccionar
  matrizPiezas[xo][yo]->setSelectable(false);
  matrizPiezas[xo][yo]->setTurno(false);
  // Conectar la pieza con el tablero
  connect(matrizPiezas[xo][yo], SIGNAL(piezaMoved(QPoint, QPoint)), this, SLOT(piezaMovida(QPoint, QPoint)));
  connect(matrizPiezas[xo][yo], SIGNAL(teamSelect(colorP, bool)), this,  SLOT(teamSelectable(colorP, bool)));
  connect(matrizPiezas[xo][yo], SIGNAL(teamUnselect(colorP, bool)), this, SLOT(teamUnselectable(colorP, bool)));
}

bool check_mate(casillaBase*** ntablero, colorP equipo) {
  for (int i = 0; i < 8; ++i) {
	for (int j = 0; j < 8; ++j) {
	  if (ntablero[i][j]->getColor() != VACIA) {
		if (ntablero[i][j]->getColor() == equipo) {
		  if (ntablero[i][j]->movimientos().size() != 0)
			return false;
        }
	  }
	}
  }

  return true;
}
