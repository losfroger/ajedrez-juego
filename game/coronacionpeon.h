#ifndef CORONACIONPEON_H
#define CORONACIONPEON_H

#include <QDialog>
#include <QPoint>
#include "game/global.hpp"

namespace Ui {
class coronacionPeon;
}

class coronacionPeon : public QDialog
{
		Q_OBJECT

	public:
		explicit coronacionPeon(QWidget *parent = nullptr, int team = 1, QPoint oldCoord = QPoint(0,0), QPoint newCoord = QPoint(0,0));
		~coronacionPeon();

	private slots:
		void on_selector_currentIndexChanged(int index);

		void on_aceptar_pressed();

	signals:
		int returnSelect(int selection, QPoint oldCoord, QPoint newCoord);

	private:
		Ui::coronacionPeon *ui;
		QPixmap *imagen;
		int color;
		int selection;
		QPoint oCoord, nCoord;
};

#endif // CORONACIONPEON_H
