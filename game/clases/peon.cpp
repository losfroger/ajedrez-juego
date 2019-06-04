#include "peon.h"
#include "game/coronacionpeon.h"
#include "game/global.hpp"

piezas::peon::peon(QGraphicsItem* parent, QPoint coordI, colorP iColor, casillaBase*** nTablero) : casillaBase(parent, coordI, iColor, PEON, nTablero){
  QString routeImage;
  // Cargar diferente imagen dependiendo si es una pieza negra o blanca
  if (iColor == BLANCA)
	routeImage = QCoreApplication::applicationDirPath() + "/resources/0peon.png";
  else 
	routeImage = QCoreApplication::applicationDirPath() + "/resources/1peon.png";

  qDebug() << routeImage;
  setPixmap(routeImage);
  firstMove = true;
  count = 1;
  capturaPaso = false;
}

piezas::peon::peon(const casillaBase& other) : casillaBase(other){
  this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::peon::movimientos(){
  captura.clear();
  capturaPaso = false;
  QList<QPoint> moves;
  // Si es una pieza negra
  if (this->getColor() == NEGRA) {
	// Movimientos hacia adelante
	for (int i = 1; i < 2 + firstMove && getCoord().y() + 1 <= 7; i++) {
	  if (tablero[getCoord().x()][getCoord().y() + i]->getColor() != VACIA)
		break;
	  else
		moves.append(QPoint(getCoord().x(), getCoord().y() + i));
	}
	// Comer
	if (getCoord().y() + 1 <= 7) // Ver que no se vaya a salir de la matriz
	{
	  if (getCoord().x() - 1 >= 0) {
		// Comer en diagonal
		if (tablero[getCoord().x() - 1][getCoord().y() + 1]->getColor() != VACIA && tablero[getCoord().x() - 1][getCoord().y() + 1]->getColor() != this->getColor()) {
		  moves.append(QPoint(getCoord().x() - 1, getCoord().y() + 1));
		}
		// Captura paso
		if (tablero[getCoord().x() - 1][getCoord().y()]->getPieza() == PEON && tablero[getCoord().x() - 1][getCoord().y()]->getSpecialA() == true && tablero[getCoord().x() - 1][getCoord().y()]->getColor() != getColor()) {
		  qDebug() << "Captura a paso - 1";
		  capturaPaso = true;
		  captura.append((QPoint(getCoord().x() - 1, getCoord().y() + 1)));
		  moves.append((QPoint(getCoord().x() - 1, getCoord().y() + 1)));
		}
	  }
	  if (getCoord().x() + 1 <= 7) {
		// Comer en diagonal
		if (tablero[getCoord().x() + 1][getCoord().y() + 1]->getColor() != VACIA && tablero[getCoord().x() + 1][getCoord().y() + 1]->getColor() != this->getColor()) {
		  moves.append(QPoint(getCoord().x() + 1, getCoord().y() + 1));
		}
		// Captura paso
		if (tablero[getCoord().x() + 1][getCoord().y()]->getPieza() == PEON && tablero[getCoord().x() + 1][getCoord().y()]->getSpecialA() == true && tablero[getCoord().x() + 1][getCoord().y()]->getColor() != getColor()) {
		  qDebug() << "Captura a paso + 1";
		  capturaPaso = true;
		  captura.append((QPoint(getCoord().x() + 1, getCoord().y() + 1)));
		  moves.append((QPoint(getCoord().x() + 1, getCoord().y() + 1)));
		}
	  }
	}
		// Si es una pieza blanca
  } else {
	// Movimiento hacia adelante
	for (int i = 1; i < 2 + firstMove && getCoord().y() - 1 >= 0; i++) {
	  if (tablero[getCoord().x()][getCoord().y() - i]->getColor() != VACIA)
		break;
	  else
		moves.append(QPoint(getCoord().x(), getCoord().y() - i));
	}
	// Comer
	if (getCoord().y() - 1 <= 7) // Ver que no se vaya a salir de la matriz
    {
	  if (getCoord().x() - 1 >= 0) {
		// Comer en la diagonal
		if (tablero[getCoord().x() - 1][getCoord().y() - 1]->getColor() !=  VACIA && tablero[getCoord().x() - 1][getCoord().y() - 1]->getColor() != this->getColor()) {
		  moves.append(QPoint(getCoord().x() - 1, getCoord().y() - 1));
		}
		// Captura paso
		if (tablero[getCoord().x() - 1][getCoord().y()]->getPieza() == PEON && tablero[getCoord().x() - 1][getCoord().y()]->getSpecialA() == true && tablero[getCoord().x() - 1][getCoord().y()]->getColor() !=  getColor()) {
		  qDebug() << "Captura a paso - 1";
		  capturaPaso = true;
		  captura.append((QPoint(getCoord().x() - 1, getCoord().y() - 1)));
		  moves.append((QPoint(getCoord().x() - 1, getCoord().y() - 1)));
		}
	  }
	  if (getCoord().x() + 1 <= 7) {
		// Comer en diagonal
		if (tablero[getCoord().x() + 1][getCoord().y() - 1]->getColor() != VACIA && tablero[getCoord().x() + 1][getCoord().y() - 1]->getColor() != this->getColor()) {
		  moves.append(QPoint(getCoord().x() + 1, getCoord().y() - 1));
		}
		// Captura paso
		if (tablero[getCoord().x() + 1][getCoord().y()]->getPieza() == PEON && tablero[getCoord().x() + 1][getCoord().y()]->getSpecialA() == true && tablero[getCoord().x() + 1][getCoord().y()]->getColor() != getColor()) {
		  qDebug() << "Captura a paso + 1";
		  capturaPaso = true;
		  captura.append((QPoint(getCoord().x() + 1, getCoord().y() - 1)));
		  moves.append((QPoint(getCoord().x() + 1, getCoord().y() - 1)));
		}
	  }
	}
  }

  if (this->getColor() == BLANCA) {
	if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque()) {
	  if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque() == 1) {
		QList<QPoint> moves2;

		moves2 = interseccion(moves, arreglo_jaque_blancas);

		moves.clear();

		for (int i = 0; i < moves2.size(); ++i)
		  moves.append(moves2[i]);

		moves2.clear();
	  } else
		moves.clear();
    }
  } else {
	if (tablero[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque()) {
	  if (tablero[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque() == 1) {
		QList<QPoint> moves2;

		moves2 = interseccion(moves, arreglo_jaque_negras);

		moves.clear();

		for (int i = 0; i < moves2.size(); ++i)
		  moves.append(moves2[i]);

		moves2.clear();
	  } else
		moves.clear();
    }
  }

  return moves;
}

void
piezas::peon::positionChanged(QPoint nCoord)
{
  /*Comprobar si se movio a una casilla donde se realiza
  la captura a paso*/
  if (capturaPaso == true) {
	for (int i = 0; i < captura.size(); i++) {
	  qDebug() << "CapturaPaso";
	  if (captura[i] == nCoord && getColor() == NEGRA) {
		delete tablero[nCoord.x()][nCoord.y() - 1];
		tablero[nCoord.x()][nCoord.y() - 1] = new casillaBase(nullptr, QPoint(nCoord.x(), nCoord.y() - 1));
	  }
	  if (captura[i] == nCoord && getColor() == BLANCA) {
		delete tablero[nCoord.x()][nCoord.y() + 1];
		tablero[nCoord.x()][nCoord.y() + 1] =  new casillaBase(nullptr, QPoint(nCoord.x(), nCoord.y() + 1));
	  }
	}
	capturaPaso = false;
	captura.clear();
  }
  firstMove = false;
  setSpecialA(false);
  if (firstMove == false && count == 1) {
	setSpecialA(true);
	count = 0;
  }
  // Promocion peon negro
  if (this->getColor() == NEGRA && nCoord.y() == 7) {
	// Generar la ventana
	coronacionPeon* promocion = new coronacionPeon(juego, 1, getCoord(), nCoord);
	connect(promocion, SIGNAL(returnSelect(int, QPoint, QPoint)), juego, SLOT(promocion(int, QPoint, QPoint)));
	// Si se cierra la ventana sin haber escogido un tipo de pieza se genera una
	// reina por default
	if (promocion->exec() != true) {
	  qDebug() << "\nPromocion cancelada\n";
	  juego->promocion(0, getCoord(), nCoord);
	}
  }
  if (this->getColor() == BLANCA && nCoord.y() == 0) {
	// Generar la ventana
	coronacionPeon* promocion = new coronacionPeon(juego, 0, getCoord(), nCoord);
	connect(promocion, SIGNAL(returnSelect(int, QPoint, QPoint)), juego, SLOT(promocion(int, QPoint, QPoint)));
	// Si se cierra la ventana sin haber escogido un tipo de pieza se genera una
	// reina por default
	if (promocion->exec() != true) {
	  qDebug() << "\nPromocion cancelada\n";
	  juego->promocion(0, getCoord(), nCoord);
	}
  }
}

void piezas::peon::update() {
  if (count == 0)
	setSpecialA(false);
}

bool piezas::peon::getFirstMove() {
  return firstMove;
}
