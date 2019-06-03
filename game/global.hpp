#ifndef GLOBAL_HPP
#define GLOBAL_HPP

#include "game/tablero.h"
#include <QPoint>
#include <QtGlobal>

QT_BEGIN_NAMESPACE
class QString;
QT_END_NAMESPACE

extern QPoint coord_rey_blanco;
extern QPoint coord_rey_negro;
extern QList<QPoint> arreglo_jaque_blancas;
extern QList<QPoint> arreglo_jaque_negras;
extern bool jaque_blancas;
extern bool jaque_negras;
extern bool jaque_mate_blancas;
extern bool jaque_mate_negras;
extern bool ahogado;
extern tablero* juego;

#endif // GLOBAL_HPP
