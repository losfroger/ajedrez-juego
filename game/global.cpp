#include "game/global.hpp"
#include <QString>

QPoint coord_rey_blanco = QPoint(0, 0);
QPoint coord_rey_negro = QPoint(0, 0);
QList <QPoint> arreglo_jaque_blancas;
QList <QPoint> arreglo_jaque_negras;
bool jaque_blancas = false;
bool jaque_negras = false;
bool jaque_mate_blancas = false;
bool jaque_mate_negras = false;
bool ahogado = false;
