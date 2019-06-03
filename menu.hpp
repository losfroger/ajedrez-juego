#ifndef MENU_HPP
#define MENU_HPP

#include <QDebug>
#include <QMainWindow>
#include <QPixmap>

#include "acerca/acercade.h"
#include "error/error.h"
#include "game/coronacionpeon.h"
#include "game/tablero.h"

namespace Ui {
class menu;
}

class menu : public QMainWindow
{
  Q_OBJECT

public:
  explicit menu(QWidget* parent = nullptr);
  ~menu();

private slots:
  ///Presionar salir
  void on_salir_clicked();
  ///Presionar "acerca de"
  void on_acerca_clicked();
  ///Presionar "Jugar!"
  void on_jugar_clicked();

private:
  Ui::menu* ui;
  acercaDe* acerca;
};

#endif // MENU_HPP
