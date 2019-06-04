#ifndef casillaBase_H
#define casillaBase_H

/*Libreria que uso para saber donde se encuentra
la aplicacion y poder cargar las imagenes*/
#include <QCoreApplication>
// Libreria para señales y slots
#include <QObject>
// Librerias graficas
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
// Libreria de evento de mouse
#include <QGraphicsSceneMouseEvent>
// Librerias de tipos de datos
#include <QList>
#include <QPoint>
#include <QString>

#include <QDebug>

#include "game/clases/cuadroselect.h"

enum tipoPieza
{
  BASE,
  PEON,
  CABALLO,
  ALFIL,
  TORRE,
  REINA,
  REY
};

enum colorP
{
  VACIA,
  BLANCA,
  NEGRA
};

namespace piezas {

  using namespace piezas;

  /// Pieza base
  /**
  BLANCA = blanco , NEGRA = negro

  Implementa:
  - El click en el objeto
  - El evento cuando se mueve la pieza
  - La señal de cuando se mueve la pieza*/
  class casillaBase : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    public:
      /// Constructor
      /**
      @param [in] parent Padre del objeto
      @param [in] coordI Coordenada inicial en el tablero (va de 0,0 a 7,7)
      @param [in] iColor Color inicial de la pieza (0 = blanca, 1 = negra)*/
      casillaBase(QGraphicsItem* parent = nullptr,
    			  QPoint coordI = QPoint(0, 0),
    			  colorP iColor = VACIA,
    			  tipoPieza iPieza = BASE,
    			  casillaBase*** nTablero = nullptr);
      /// Constructor copia
      casillaBase(const casillaBase& other);

      /// Destructor
      virtual ~casillaBase();
      /// Lista de movimientos de la pieza
      /**
      @return Una QList de los movimientos posibles de la pieza
      (expresados en coordenadas del tablero)*/
      virtual QList<QPoint> movimientos();

      /// Evento de click con el mouse en la pieza
      /**
      Manda a llamar la funcion de movimientos y a partir de eso
      genera los cuadrados de a donde se puede llamar la pieza.

      - Click izquierdo para seleccionar una pieza
      - Click derecho para deseleccionarla

      Si una pieza esta seleccionada, no se pueden escoger las demas piezas*/
      void mousePressEvent(QGraphicsSceneMouseEvent* event);

      /// Funcion llamada cuando se movio la pieza
      /**
      Util en casos como el del peon, que necesita saber cuando ya se ha movido*/
      virtual void positionChanged(QPoint nCoord);

      /// Funcion que se manda a llamar en cada turno
      virtual void update();

      // SETTERS AND GETTERS
      /// Cambiar el valor del tipo de pieza
      void setPieza(tipoPieza newPieza) { pieza = newPieza; }
      /// Conseguir el valor del tipo de pieza
      tipoPieza getPieza() const { return pieza; }

      /// Cambiar las coordenadas en el tablero
      void setCoord(QPoint newPos) { coordTablero = newPos; }
      /// Conseguir las coordenadas en el tablero
      QPoint getCoord() const { return coordTablero; }

      /// Cambiar el color de la pieza (0 = blanco, 1 = negro)
      void setColor(colorP newColor) { color = newColor; }
      /// Conseguir el color de la pieza
      colorP getColor() const { return color; }

      /// Cambiar si la pieza se puede seleccionar o no
      void setSelectable(bool newS) { selectable = newS; }
      /// Conseguir si la pieza se puede seleccionar o no
      bool getSelectable() const { return selectable; }

      /// Cambiar si la pieza se puede seleccionar o no
      void setSpecialA(bool newSA) { specialA = newSA; }
      /// Conseguir si la pieza se puede seleccionar o no
      bool getSpecialA() const { return specialA; }

      /// Cambiar si el rey esta en jaque
      void setJaque(unsigned int newJaque) { jaque = newJaque; }
      /// Conseguir si el rey esta en jaque
      unsigned int getJaque(void) { return jaque; }

      void setTurno(bool newT) { turno = newT; }

    public slots:
      /// Se activa cuando se escoge una de las cajas de movimiento
      /**
      Elimina todas las cajas de seleccion y establece la nueva posicion de la pieza
      @param [in] coordT las nuevas coordenadas en el tablero de la pieza*/
      void move(QPoint coordT);

      // void promocion(int type);
    signals:
      /// Mandar señal al tablero de que se movio la pieza
      /**
      Manda las coordenadas viejas y nuevas de la pieza*/
      void piezaMoved(QPoint oldCoord, QPoint newCoord);
      /// Hacer que todas las piezas del mismo equipo se puedan seleccionar
      /**
      @param [in] team Equipo el cual se debe hacer seleccionable
      @param [in] changeT Si se quiere cambiar de turno*/
      void teamSelect(colorP team, bool changeT);
      /// Hacer que todas las piezas del mismo equipo NO se puedan seleccionar
      /**
      @param [in] team Equipo el cual se debe hacer no seleccionable
      @param [in] changeT Si se quiere cambiar de turno*/
      void teamUnselect(colorP team, bool changeT);

    protected:
      casillaBase***
    	tablero; //!< Apuntador a la matriz de piezas, usada para poder consultar la
    			 //!< posicion de otras piezas desde una pieza

    private:
      bool specialA; //!< Booleano usado en condiciones especiales, como el enroque
    				 //!< o la captura al paso
      unsigned int jaque; // para saber si esta en jaque las piezas blancas

      bool turno; //!< Si es el turno de la pieza

      tipoPieza pieza;     //!< Tipo de pieza
      QPoint coordTablero; //!< Posicion de la pieza en el tablero
      colorP color;        //!< El equipo de la pieza: Negra, blanca o vacia
      bool selectable;     //!< Si se puede seleccionar la pieza
      bool lastClicked;
    };

  /// Funcion de jaque
  /**
  @param [in] ntablero es la matriz de las piezas
  @param [in] coordI coordenada en donde se va a revisar
  @param [in] colorpieza el color de la pieza
  @param [in] moves_check*/
  unsigned int
  check(casillaBase*** ntablero = nullptr,
  	  QPoint coordI = QPoint(8, 8),
  	  colorP colorpieza = BLANCA,
  	  QList<QPoint>* moves_check = nullptr);

  /// Interseccion entre dos listas
  /**
  @param [in] ListaA primera lista
  @param [in] ListaB segunda lista*/
  QList<QPoint>
  interseccion(QList<QPoint> ListaA, QList<QPoint> ListaB);
  QList<QPoint>
  legal_mov(casillaBase*** ntablero = nullptr,
  		  QPoint posact = QPoint(0, 0),
  		  QList<QPoint> ListaA = QList<QPoint>(),
		  colorP equipo = BLANCA);
}

#endif // casillaBase_H
