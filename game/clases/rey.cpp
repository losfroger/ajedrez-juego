#include "rey.h"
#include "game/global.hpp"

piezas::rey::rey(QGraphicsItem *parent, QPoint coordI, colorP iColor, casillaBase ***nTablero) : casillaBase (parent, coordI, iColor, REY, nTablero)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0rey.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1rey.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::rey::rey(const piezas::casillaBase &other) : casillaBase(other)
{
    this->setPixmap(other.pixmap());
}

void piezas::rey::positionChanged(QPoint nCoord)
{
    int posy = getCoord().y();

    qDebug() << "Enroque Size = " << Enroque.size();
    qDebug() << "Enroque = " << Enroque;

    for (int i = 0; i < Enroque.size(); i++)
    {
        qDebug() << "Enroque[" << i << "] = " << Enroque[i];
        qDebug() << "nCoord = " << nCoord;
        if (Enroque[i] == nCoord)
        {
            tablero[((Enroque[i].x() == 2)? 0 : 7)][posy]->setPos(TAM_SANGRIA + TAM_CUADRO * (((Enroque[i].x() == 2)? 3 : 5)), TAM_SANGRIA + TAM_CUADRO * posy);
            tablero[((Enroque[i].x() == 2)? 0 : 7)][posy]->setCoord(QPoint(((Enroque[i].x() == 2)? 3 : 5), posy));
            tablero[((Enroque[i].x() == 2)? 3 : 5)][posy] = tablero[((Enroque[i].x() == 2)? 0 : 7)][posy];
            tablero[((Enroque[i].x() == 2)? 0 : 7)][posy] = new casillaBase(nullptr, QPoint(((Enroque[i].x() == 2)? 0 : 7), posy), VACIA, BASE, tablero);

            break;
        }
    }

    this->fistMove = true;
}

QList<QPoint> piezas::rey::movimientos()
{
	QList <QPoint> moves;

    Enroque.clear();

    int posx = getCoord().x();
    int posy = getCoord().y();

    //checamos si podemos hacer enroque largo
    if (!this->fistMove && tablero[0][posy]->getSpecialA() == false)
    {
        if (tablero[0][posy]->getPieza() == TORRE && tablero[0][posy]->getColor() == this->getColor())
        {
            bool libre = true;

            for (int i = posx - 1; i >= 1; --i)
            {
                if (tablero[i][posy]->getPieza() != BASE)
                {
                    libre = false;
                    break;
                }
            }

            if (libre)
            {
                Enroque.append(QPoint(posx - 2, posy));
                moves.append(QPoint(posx - 2, posy));
            }
        }
    }

    //checamos si podemos hacer enroque corto
    if (!this->fistMove && tablero[7][posy]->getSpecialA() == false)
    {
        if (tablero[7][posy]->getPieza() == TORRE && tablero[7][posy]->getColor() == this->getColor())
        {
            bool libre = true;

            for (int i = posx + 1; i <= 6; ++i)
            {
                if (tablero[i][posy]->getPieza() != BASE)
                {
                    libre = false;
                    break;
                }
            }

            if (libre)
            {
                Enroque.append(QPoint(posx + 2, posy));
                moves.append(QPoint(posx + 2, posy));
            }
        }
    }

    //checamos los movimientos basicos del rey
    if (posy >= 1)
    {
        if (tablero[posx][posy - 1]->getColor() != this->getColor())
        {
            if (!check(tablero, QPoint(posx, posy - 1), this->getColor())) //cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                moves.append(QPoint(posx, posy - 1));
        }

        if (posx >= 1)
        {
            if (tablero[posx - 1][posy -1]->getColor() != this->getColor())
            {
                if (!check(tablero, QPoint(posx - 1, posy - 1), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                    moves.append(QPoint(posx - 1, posy - 1));
            }
        }

        if (posx <= 6)
        {
            if (tablero[posx + 1][posy - 1]->getColor() != this->getColor())
            {
                if (!check(tablero, QPoint(posx + 1, posy - 1), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                    moves.append(QPoint(posx + 1, posy - 1));
            }
        }
    }

    if (posy <= 6)
    {
        if (tablero[posx][posy + 1]->getColor() != this->getColor())
        {
            if (!check(tablero, QPoint(posx, posy + 1), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                moves.append(QPoint(posx, posy + 1));
        }

        if(posx >= 1)
        {
            if (tablero[posx - 1][posy + 1]->getColor() != this->getColor())
            {
                if (!check(tablero, QPoint(posx - 1, posy + 1), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                    moves.append(QPoint(posx - 1, posy + 1));
            }
        }

        if (posx <= 6)
        {
            if (tablero[posx + 1][posy + 1]->getColor() != this->getColor())
            {
                if (!check(tablero, QPoint(posx + 1, posy + 1), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                    moves.append(QPoint(posx + 1, posy + 1));
            }
        }
    }

    if (posx >= 1)
    {
        if (tablero[posx - 1][posy]->getColor() != this->getColor())
        {
            if (!check(tablero, QPoint(posx - 1, posy), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                moves.append(QPoint(posx - 1, posy));
        }
    }

    if (posx <= 6)
    {
        if (tablero[posx + 1][posy]->getColor() != this->getColor())
        {
            if (!check(tablero, QPoint(posx + 1, posy), this->getColor()))//cambiar false por la condicion de jaque, donde la condicion debe ser false para cuando no se ponga en jaque en esa casilla, para que con la negacion entre al if
                moves.append(QPoint(posx + 1, posy));
        }
    }

	return moves;
}
