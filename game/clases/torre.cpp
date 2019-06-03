#include "torre.h"
#include "game/global.hpp"

piezas::torre::torre(QGraphicsItem* parent,
					 QPoint coordI,
					 colorP iColor,
					 casillaBase*** nTablero)
  : casillaBase(parent, coordI, iColor, TORRE, nTablero)
{
  QString routeImage;
  specialA = false;
  // Cargar diferente imagen dependiendo si es una pieza negra o blanca
  if (iColor == BLANCA)
	routeImage =
	  QCoreApplication::applicationDirPath() + "/resources/0torre.png";
  else {
	routeImage =
	  QCoreApplication::applicationDirPath() + "/resources/1torre.png";
  }
  qDebug() << routeImage;
  setPixmap(routeImage);
}

piezas::torre::torre(const piezas::casillaBase& other)
  : casillaBase(other)
{
  this->setPixmap(other.pixmap());
}

void
piezas::torre::positionChanged(QPoint nCoord)
{
  nCoord * 1; // Para evitar warnings
  setSpecialA(true);
}

QList<QPoint>
piezas::torre::movimientos()
{
  QList<QPoint> moves;

  int posx = getCoord().x();
  int posy = getCoord().y();
  // Mivimiento hacia abajo
  bool aux = true;
  int x = posx;
  int y = posy;
  while (aux == true) {
	y += 1;
	if (y <= 7) {
	  if (tablero[x][y]->getColor() == VACIA) {
		moves.append(QPoint(x, y));
	  } else {
		if (tablero[x][y]->getColor() != this->getColor()) {
		  moves.append(QPoint(x, y));
		  aux = false;
		} else {
		  aux = false;
		}
	  }
	} else {
	  aux = false;
	}
  }

  // Mivimiento hacia arriba
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	y -= 1;
	if (y >= 0) {
	  if (tablero[x][y]->getColor() == VACIA) {
		moves.append(QPoint(x, y));
	  } else {
		if (tablero[x][y]->getColor() != this->getColor()) {
		  moves.append(QPoint(x, y));
		  aux = false;
		} else {
		  aux = false;
		}
	  }
	} else {
	  aux = false;
	}
  }

  // Mivimiento hacia la derecha
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	x += 1;
	if (x <= 7) {
	  if (tablero[x][y]->getColor() == VACIA) {
		moves.append(QPoint(x, y));
	  } else {
		if (tablero[x][y]->getColor() != this->getColor()) {
		  moves.append(QPoint(x, y));
		  aux = false;
		} else {
		  aux = false;
		}
	  }
	} else {
	  aux = false;
	}
  }

  // Mivimiento hacia la izquierda
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	x -= 1;
	if (x >= 0) {
	  if (tablero[x][y]->getColor() == VACIA) {
		moves.append(QPoint(x, y));
	  } else {
		if (tablero[x][y]->getColor() != this->getColor()) {
		  moves.append(QPoint(x, y));
		  aux = false;
		} else {
		  aux = false;
		}
	  }
	} else {
	  aux = false;
	}
  }

  if (this->getColor() == BLANCA) {
	if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque()) {
	  if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque() ==
		  1) {
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
