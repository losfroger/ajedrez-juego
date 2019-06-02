#include "acercade.h"
#include "ui_acercade.h"

acercaDe::acercaDe(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::acercaDe)
{
	ui->setupUi(this);

	QString s = QCoreApplication::applicationDirPath() + "/resources/ug.png";
	QPixmap logo;

	if (logo.load(s) == true)
	{
		ui->logoUg->setPixmap(logo.scaled(ui->logoUg->width(),ui->logoUg->height(),Qt::KeepAspectRatio));
	}
	else
	{
		qDebug() << s;
	}
}

acercaDe::~acercaDe()
{
	delete ui;
}

void acercaDe::on_aceptar_clicked()
{
	this->accept();
}

void acercaDe::on_AboutQt_pressed()
{
	QApplication::aboutQt();
}
