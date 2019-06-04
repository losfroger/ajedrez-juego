#ifndef CORONACIONPEON_H
#define CORONACIONPEON_H

#include "game/global.hpp"
#include <QDialog>
#include <QPoint>

namespace Ui {
  class coronacionPeon;
}

class coronacionPeon : public QDialog{
  Q_OBJECT

  public:
    explicit coronacionPeon(QWidget* parent = nullptr,
  						  int team = 1,
  						  QPoint oldCoord = QPoint(0, 0),
  						  QPoint newCoord = QPoint(0, 0));
    ~coronacionPeon();

  private slots:
    /// Cuando se cambia la seleccion
    void on_selector_currentIndexChanged(int index);
    /// Al dar click en aceptar
    void on_aceptar_pressed();

  signals:
    /// Regresar la seleccion al tablero
    int returnSelect(int selection, QPoint oldCoord, QPoint newCoord);

  private:
    Ui::coronacionPeon* ui;
    QPixmap* imagen;       //!< Imagen que se muestra
    int color;             //!< Color de la pieza
    int selection;         //!< Seleccion del tipo de pieza
    QPoint oCoord, nCoord; //!< Coordenadas
};

#endif // CORONACIONPEON_H
