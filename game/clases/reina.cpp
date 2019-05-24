#include "reina.h"


piezas::reina::reina(QGraphicsItem *parent, QPoint coordI, colorP iColor,piezaBase ***nTablero) : piezaBase (parent, coordI, iColor, REINA,nTablero)
{
	QString routeImage;
	//Cargar diferente imagen dependiendo si es una pieza negra o blanca
	if (iColor == BLANCA)
		routeImage = QCoreApplication::applicationDirPath() + "/resources/0reina.png";
	else {
		routeImage = QCoreApplication::applicationDirPath() + "/resources/1reina.png";
	}
	qDebug() << routeImage;
	setPixmap(routeImage);
}

piezas::reina::reina(const piezas::piezaBase &other) : piezaBase(other)
{
	this->setPixmap(other.pixmap());
}

QList<QPoint> piezas::reina::movimientos()
{
	QList <QPoint> moves;
	int posx=getCoord().x();
	int posy=getCoord().y();
	//Movimiento en forma de cruz
	{
		//Mivimiento hacia abajo
	bool aux=true;
	int x=posx;
	int y=posy;
	while(aux==true)
	{
		y+=1;
		if (y<=7)
		{
			if(tablero[x][y]->getColor() == VACIA)
			{
				moves.append(QPoint(x,y));
			}
			else
			{
                if (tablero[x][y]->getColor() != this->getColor())
				{
					moves.append(QPoint(x,y));
					aux=false;
				}
				else
				{
					aux=false;
				}
			}
		}
		else
		{
			aux=false;
		}
	}

	//Mivimiento hacia arriba
    aux=true;
    x=posx;
    y=posy;
	while(aux==true)
	{
		y-=1;
		if (y>=0)
		{
			if(tablero[x][y]->getColor() == VACIA)
			{
				moves.append(QPoint(x,y));
			}
			else
			{
                if (tablero[x][y]->getColor() != this->getColor())
				{
					moves.append(QPoint(x,y));
					aux=false;
				}
				else
				{
					aux=false;
				}
			}
		}
		else
		{
			aux=false;
		}
	}

	//Mivimiento hacia la derecha
    aux=true;
    x=posx;
    y=posy;
	while(aux==true)
	{
		x+=1;
		if (x<=7)
		{
			if(tablero[x][y]->getColor() == VACIA)
			{
				moves.append(QPoint(x,y));
			}
			else
			{
                if (tablero[x][y]->getColor() != this->getColor())
				{
					moves.append(QPoint(x,y));
					aux=false;
				}
				else
				{
					aux=false;
				}
			}
		}
		else
		{
			aux=false;
		}
	}

	//Mivimiento hacia la izquierda
    aux=true;
    x=posx;
    y=posy;
	while(aux==true)
	{
		x-=1;
		if (x>=0)
		{
			if(tablero[x][y]->getColor() == VACIA)
			{
				moves.append(QPoint(x,y));
			}
			else
			{
                if (tablero[x][y]->getColor() != this->getColor())
				{
					moves.append(QPoint(x,y));
					aux=false;
				}
				else
				{
					aux=false;
				}
			}
		}
		else
		{
			aux=false;
		}
	}
	}
	//Movimientos en forma de diagonal
	{
	bool aux=true;
    int x=posx, y=posy;
    while(aux==true){
        x+=1;
        y+=1;
        if(x<=7 && y<=7){
            if(tablero[x][y]->getColor() == VACIA){
                moves.append(QPoint(x,y));
            }else{
                if(tablero[x][y]->getColor() != this->getColor()){
                    moves.append(QPoint(x,y));
                    aux=false;
                }else{
                    aux=false;
                }
            }
        }else{
            aux=false;
        }
    }
    //Movimiento hacia abajo a la izquierda
    aux=true;
    x=posx;
    y=posy;
    while(aux==true){
        x-=1;
        y+=1;
        if(x>=0 && y<=7){
            if(tablero[x][y]->getColor() == VACIA){
                moves.append(QPoint(x,y));
            }else{
                if(tablero[x][y]->getColor() != this->getColor()){
                    moves.append(QPoint(x,y));
                    aux=false;
                }else{
                    aux=false;
                }
            }
        }else{
            aux=false;
        }
    }
    //Movimiento hacia arriba a la derecha
    aux=true;
    x=posx;
    y=posy;
    while(aux==true){
        x+=1;
        y-=1;
        if(x<=7 && y>=0){
            if(tablero[x][y]->getColor() == VACIA){
                moves.append(QPoint(x,y));
            }else{
                if(tablero[x][y]->getColor() != this->getColor()){
                    moves.append(QPoint(x,y));
                    aux=false;
                }else{
                    aux=false;
                }
            }
        }else{
            aux=false;
        }
    }
    //Movimiento hacia arriba a la izquierda
    aux=true;
    x=posx;
    y=posy;
    while(aux==true){
        x-=1;
        y-=1;
        if(x>=0 && y>=0){
            if(tablero[x][y]->getColor() == VACIA){
                moves.append(QPoint(x,y));
            }else{
                if(tablero[x][y]->getColor() != this->getColor()){
                    moves.append(QPoint(x,y));
                    aux=false;
                }else{
                    aux=false;
                }
            }
        }else{
            aux=false;
        }
    }
	}

	return moves;
}
