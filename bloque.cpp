#include "bloque.h"
#include "configjuego.h"
#include <QBrush>
#include <QColor>
#include <QLinearGradient>
#include <QPen>

Bloque::Bloque()
    : escena(nullptr), item(nullptr), tipo(TipoBloque::Normal),
      golpesRestantes(0), activo(false)
{
}

Bloque::~Bloque()
{
    destruir();
}

void Bloque::crear(QGraphicsScene *nuevaEscena, double x, double y, TipoBloque nuevoTipo)
{
    destruir();   // por si la celda ya tenia un ladrillo

    escena = nuevaEscena;
    tipo = nuevoTipo;
    golpesRestantes = (tipo == TipoBloque::Reforzado) ? 2 : 1;

    item = escena->addRect(0, 0, Config::BLOQUE_ANCHO, Config::BLOQUE_ALTO);
    item->setPos(x, y);
    activo = true;
    aplicarEstilo();
}

// >>> EXTENSION: aqui se cambian los colores de cada tipo de ladrillo.
void Bloque::aplicarEstilo()
{
    QColor claro, oscuro, borde;

    switch (tipo) {
    case TipoBloque::Normal:            // acero gris
        claro = QColor("#9aa7b4");
        oscuro = QColor("#4d5963");
        borde = QColor("#262d34");
        break;
    case TipoBloque::Reforzado:         // azul acero; naranja oxidado cuando ya esta daniado
        if (golpesRestantes >= 2) {
            claro = QColor("#6f9bc4");
            oscuro = QColor("#2f4f6e");
            borde = QColor("#16293b");
        } else {
            claro = QColor("#d08a4a");
            oscuro = QColor("#7a3f1b");
            borde = QColor("#3d1d0a");
        }
        break;
    case TipoBloque::Indestructible:    // titanio oscuro con borde neon
        claro = QColor("#4a5058");
        oscuro = QColor("#1b1e23");
        borde = QColor("#00e5ff");
        break;
    }

    // Degradado vertical para dar efecto metalico
    QLinearGradient degradado(0, 0, 0, 1);
    degradado.setCoordinateMode(QGradient::ObjectBoundingMode);
    degradado.setColorAt(0.0, claro);
    degradado.setColorAt(1.0, oscuro);

    item->setBrush(QBrush(degradado));
    item->setPen(QPen(borde, 1));
}

// >>> EXTENSION: aqui se define que le pasa al ladrillo cuando la pelota lo golpea.
bool Bloque::recibirGolpe()
{
    if (!activo) {
        return false;
    }

    switch (tipo) {
    case TipoBloque::Normal:
        destruir();
        return true;
    case TipoBloque::Reforzado:
        --golpesRestantes;
        if (golpesRestantes <= 0) {
            destruir();
            return true;
        }
        aplicarEstilo();            // cambia de color por el dano
        return false;
    case TipoBloque::Indestructible:
        return false;
    }
    return false;
}

void Bloque::destruir()
{
    if (item) {
        escena->removeItem(item);
        delete item;
        item = nullptr;
    }
    activo = false;
}

QRectF Bloque::rect() const
{
    if (!item) {
        return QRectF();
    }
    return QRectF(item->x(), item->y(), Config::BLOQUE_ANCHO, Config::BLOQUE_ALTO);
}
