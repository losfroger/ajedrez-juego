#include "coronacionpeon.h"
#include "ui_coronacionpeon.h"

coronacionPeon::coronacionPeon(QWidget* parent,
							   int team,
							   QPoint oldCoord,
							   QPoint newCoord)
  : QDialog(parent)
  , ui(new Ui::coronacionPeon)
{
  ui->setupUi(this);
  // Cargar la imagen default
  QString filepath = QCoreApplication::applicationDirPath() + "/resources/" +
					 QString::number(team) + "reina.png";
  imagen = new QPixmap(filepath);
  // Guardar el color del equipo
  color = team;
  // Poner la imagen en pantalla
  int w = ui->imageLabel->width(), h = ui->imageLabel->height();
  ui->imageLabel->setPixmap(imagen->scaled(w, h, Qt::KeepAspectRatio));
  selection = 0;

  oCoord = oldCoord;
  nCoord = newCoord;
}

coronacionPeon::~coronacionPeon()
{
  delete imagen;
  delete ui;
}

void
coronacionPeon::on_selector_currentIndexChanged(int index)
{
  // Cambiar la imagen al cambiar la seleccion
  QString filepath;
  switch (index) {
	case 0:
	  filepath = QCoreApplication::applicationDirPath() + "/resources/" +
				 QString::number(color) + "reina.png";
	  imagen->load(filepath);
	  break;
	case 1:
	  filepath = QCoreApplication::applicationDirPath() + "/resources/" +
				 QString::number(color) + "torre.png";
	  imagen->load(filepath);
	  break;
	case 2:
	  filepath = QCoreApplication::applicationDirPath() + "/resources/" +
				 QString::number(color) + "alfil.png";
	  imagen->load(filepath);
	  break;
	case 3:
	  filepath = QCoreApplication::applicationDirPath() + "/resources/" +
				 QString::number(color) + "caballo.png";
	  imagen->load(filepath);
	  break;
	default:
	  filepath = QCoreApplication::applicationDirPath() + "/resources/" +
				 QString::number(color) + "peon.png";
	  imagen->load(filepath);
	  break;
  }
  int w = ui->imageLabel->width(), h = ui->imageLabel->height();
  ui->imageLabel->setPixmap(imagen->scaled(w, h, Qt::KeepAspectRatio));
  selection = index;
}

void
coronacionPeon::on_aceptar_pressed()
{
  // Mandar la seleccion al tablero
  emit returnSelect(selection, oCoord, nCoord);
  QDialog::accept();
}
