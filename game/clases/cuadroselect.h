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
		cuadroSelect(QGraphicsItem *parent = nullptr, QPoint coordI = QPoint(0,0));
		~cuadroSelect();
	private:
		void mousePressEvent(QGraphicsSceneMouseEvent *event);
	signals:
		void selected();
};

#endif // CUADROSELECT_H
