#ifndef ACERCADE_H
#define ACERCADE_H

#include <QDialog>
#include <QPixmap>
#include <QDebug>

#include "error/error.h"

namespace Ui {
class acercaDe;
}

class acercaDe : public QDialog
{
		Q_OBJECT

	public:
		explicit acercaDe(QWidget *parent = nullptr);
		~acercaDe();

	private slots:
		void on_aceptar_clicked();

		void on_AboutQt_pressed();

	private:
		Ui::acercaDe *ui;
};

#endif // ACERCADE_H
