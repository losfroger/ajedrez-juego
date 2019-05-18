#ifndef CUADROSELECT_H
#define CUADROSELECT_H

#include <QObject>

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class cuadroSelect : public QObject, public QGraphicsRectItem
{
	Q_OBJECT

	public:
		/**
		@param [in] parent Objeto padre
		@param [in] coordI Coordenada del tablero a donde se puede mover la pieza*/
		cuadroSelect(QGraphicsItem *parent = nullptr, QPoint coordI = QPoint(0,0));
		~cuadroSelect();
	private:
		QPoint coordT; //!Coordenada del tablero
		///Evento al hacer click con el mouse
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		///Señal que emite la coordenada del tablero
		void selected(QPoint coordT);
};

#endif // CUADROSELECT_H
