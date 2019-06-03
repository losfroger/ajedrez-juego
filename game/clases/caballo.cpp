#include "caballo.h"
#include "game/global.hpp"

piezas::caballo::caballo(QGraphicsItem *parent, QPoint coordI, colorP iColor, casillaBase ***nTablero) : casillaBase (parent, coordI, iColor, CABALLO, nTablero)
{
    QString routeImage;
    //Cargar diferente imagen dependiendo si es una pieza negra o blanca
    if (iColor == BLANCA)
        routeImage = QCoreApplication::applicationDirPath() + "/resources/0caballo.png";
    else {
        routeImage = QCoreApplication::applicationDirPath() + "/resources/1caballo.png";
    }
    qDebug() << routeImage;
    setPixmap(routeImage);
}

piezas::caballo::caballo(const piezas::casillaBase &other) : casillaBase(other)
{
    this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::caballo::movimientos()
{
    QList <QPoint> moves;

    int posx = getCoord().x();
    int posy = getCoord().y();

    if (posx >= 2)
    {
        if (posy >= 1)
        {
            if (tablero[posx - 2][posy - 1]->getColor() != this->getColor())
                moves.append(QPoint(posx - 2, posy - 1));
        }

        if (posy <= 6)
        {
            if (tablero[posx - 2][posy + 1]->getColor() != this->getColor())
                moves.append(QPoint(posx - 2, posy + 1));
        }
    }

    if (posx <= 5)
    {
        if (posy >= 1)
        {
            if (tablero[posx + 2][posy - 1]->getColor() != this->getColor())
                moves.append(QPoint(posx + 2, posy - 1));
        }

        if (posy <= 6)
        {
            if (tablero[posx + 2][posy + 1]->getColor() != this->getColor())
                moves.append(QPoint(posx + 2, posy + 1));
        }
    }

    if (posy >= 2)
    {
        if (posx >= 1)
        {
            if (tablero[posx - 1][posy - 2]->getColor() != this->getColor())
                moves.append(QPoint(posx - 1, posy - 2));
        }

        if (posx <= 6)
        {
            if (tablero[posx + 1][posy - 2]->getColor() != this->getColor())
                moves.append(QPoint(posx + 1, posy - 2));
        }
    }
    if (posy <= 5)
    {
        if (posx >= 1)
        {
            if (tablero[posx - 1][posy + 2]->getColor() != this->getColor())
                moves.append(QPoint(posx - 1, posy + 2));
        }

        if (posx <= 6)
        {
            if (tablero[posx + 1][posy + 2]->getColor() != this->getColor())
                moves.append(QPoint(posx + 1, posy + 2));
        }
    }

    if (this->getColor() == BLANCA)
    {
        if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque())
        {
            if (tablero[coord_rey_blanco.x()][coord_rey_blanco.y()]->getJaque() == 1)
            {
               QList <QPoint> moves2;

               moves2 = interseccion(moves, arreglo_jaque_blancas);

               moves.clear();

               for (int i = 0; i < moves2.size(); ++i)
                   moves.append(moves2[i]);

               moves2.clear();
            }
            else
                moves.clear();
        }
    }
    else
    {
        if (tablero[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque())
        {
            if (tablero[coord_rey_negro.x()][coord_rey_negro.y()]->getJaque() == 1)
            {
                QList <QPoint> moves2;

                moves2 = interseccion(moves, arreglo_jaque_negras);

                moves.clear();

                for (int i = 0; i < moves2.size(); ++i)
                    moves.append(moves2[i]);

                moves2.clear();
            }
            else
                moves.clear();
        }
    }

    return moves;
}
