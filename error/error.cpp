#include "error.h"
#include "ui_error.h"

error::error(QWidget *parent, QString error) :
	QDialog(parent),
	ui(new Ui::error)
{
	ui->setupUi(this);
	ui->labelError->setText(error);
}

error::~error()
{
	delete ui;
}

void error::on_aceptar_clicked()
{
	this->accept();
}
