#include "paleta.h"
#include "configjuego.h"
#include <QBrush>
#include <QColor>
#include <QLinearGradient>
#include <QPen>

Paleta::Paleta(QGraphicsScene *nuevaEscena)
    : escena(nuevaEscena), item(nullptr), izquierda(false), derecha(false),
      velocidad(Config::PALETA_VELOCIDAD)
{
    item = escena->addRect(0, 0, Config::PALETA_ANCHO, Config::PALETA_ALTO);

    // Acero con borde neon cyan
    QLinearGradient degradado(0, 0, 0, 1);
    degradado.setCoordinateMode(QGradient::ObjectBoundingMode);
    degradado.setColorAt(0.0, QColor("#b9c6d3"));
    degradado.setColorAt(1.0, QColor("#56626e"));
    item->setBrush(QBrush(degradado));
    item->setPen(QPen(QColor("#00e5ff"), 2));

    reiniciar();
}

Paleta::~Paleta()
{
    if (item) {
        escena->removeItem(item);
        delete item;
        item = nullptr;
    }
}

void Paleta::detener()
{
    izquierda = false;
    derecha = false;
}

void Paleta::actualizar()
{
    int direccion = (derecha ? 1 : 0) - (izquierda ? 1 : 0);
    if (direccion == 0) {
        return;
    }
    item->setX(item->x() + direccion * velocidad);
    limitarAPantalla();
}

void Paleta::limitarAPantalla()
{
    double maximo = escena->width() - item->rect().width();
    if (item->x() < 0) {
        item->setX(0);
    } else if (item->x() > maximo) {
        item->setX(maximo);
    }
}

void Paleta::centrarEn(double x)
{
    item->setX(x - item->rect().width() / 2.0);
    limitarAPantalla();
}

void Paleta::reiniciar()
{
    item->setPos((Config::ESCENA_ANCHO - item->rect().width()) / 2.0, Config::PALETA_Y);
}

void Paleta::setAncho(double ancho)
{
    double centro = item->x() + item->rect().width() / 2.0;
    item->setRect(0, 0, ancho, Config::PALETA_ALTO);
    centrarEn(centro);   // mantiene el centro y respeta los bordes
}

QRectF Paleta::rect() const
{
    return QRectF(item->x(), item->y(), item->rect().width(), item->rect().height());
}
