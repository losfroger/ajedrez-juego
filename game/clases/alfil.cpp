#include "alfil.h"
#include "game/global.hpp"

piezas::alfil::alfil(QGraphicsItem* parent,
					 QPoint coordI,
					 colorP iColor,
					 casillaBase*** nTablero)
  : casillaBase(parent, coordI, iColor, ALFIL, nTablero)
{
  QString routeImage;
  // Cargar diferente imagen dependiendo si es una pieza negra o blanca
  if (iColor == BLANCA)
	routeImage =
	  QCoreApplication::applicationDirPath() + "/resources/0alfil.png";
  else {
	routeImage =
	  QCoreApplication::applicationDirPath() + "/resources/1alfil.png";
  }
  qDebug() << routeImage;
  setPixmap(routeImage);
}

piezas::alfil::alfil(const piezas::casillaBase& other)
  : casillaBase(other)
{
  this->setPixmap(other.pixmap());
}

QList<QPoint>
piezas::alfil::movimientos()
{
  QList<QPoint> moves;

  int posx = getCoord().x();
  int posy = getCoord().y();

  // Movimiento hacia abajo a la derecha
  bool aux = true;
  int x = posx, y = posy;
  while (aux == true) {
	x += 1;
	y += 1;
	if (x <= 7 && y <= 7) {
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
  // Movimiento hacia abajo a la izquierda
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	x -= 1;
	y += 1;
	if (x >= 0 && y <= 7) {
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
  // Movimiento hacia arriba a la derecha
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	x += 1;
	y -= 1;
	if (x <= 7 && y >= 0) {
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
  // Movimiento hacia arriba a la izquierda
  aux = true;
  x = posx;
  y = posy;
  while (aux == true) {
	x -= 1;
	y -= 1;
	if (x >= 0 && y >= 0) {
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

  /*
  if (this->getColor() == BLANCA)
  {
	  QList <QPoint> moves2;

	  //moves2 = legal_mov(tablero, this->getCoord(), moves, BLANCA);

	  moves.clear();

	  for (int i = 0; i < moves2.size(); ++i)
		  moves.append(moves2[i]);

	  moves2.clear();
  }
  else
  {
	  QList <QPoint> moves2;

	  //moves2 = legal_mov(tablero, this->getCoord(), moves, NEGRA);

	  moves.clear();

	  for (int i = 0; i < moves2.size(); ++i)
		  moves.append(moves2[i]);

	  moves2.clear();
  }
  */

  return moves;
}
