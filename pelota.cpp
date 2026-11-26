#include "pelota.h"
#include "configjuego.h"
#include <QBrush>
#include <QColor>
#include <QPen>
#include <QRadialGradient>
#include <QtMath>

Pelota::Pelota(QGraphicsScene *nuevaEscena)
    : escena(nuevaEscena), item(nullptr), vx(0), vy(0),
      velocidad(Config::PELOTA_VELOCIDAD)
{
    const double d = Config::PELOTA_DIAMETRO;
    item = escena->addEllipse(0, 0, d, d);

    // color de la pelota
    QRadialGradient degradado(0.35, 0.35, 0.8);
    degradado.setCoordinateMode(QGradient::ObjectBoundingMode);
    degradado.setColorAt(0.0, QColor("#ffffff"));
    degradado.setColorAt(1.0, QColor("#00bcd4"));
    item->setBrush(QBrush(degradado));
    item->setPen(QPen(QColor("#00e5ff"), 1));

    reiniciar(Config::PELOTA_INICIO_X, Config::PELOTA_INICIO_Y);
}

Pelota::~Pelota()
{
    if (item) {
        escena->removeItem(item);
        delete item;
        item = nullptr;
    }
}

// Convierte el angulo y la velocidad en el vector (vx, vy). 0 grados = hacia arriba.
void Pelota::fijarDireccion(double gradosDesdeVertical)
{
    double a = qDegreesToRadians(gradosDesdeVertical);
    vx = velocidad * qSin(a);
    vy = -velocidad * qCos(a);
}

void Pelota::reiniciar(double x, double y)
{
    velocidad = Config::PELOTA_VELOCIDAD;
    item->setPos(x, y);
    fijarDireccion(Config::PELOTA_ANGULO_INICIAL);
}

void Pelota::mover()
{
    item->setPos(item->x() + vx, item->y() + vy);
}

// Paredes :true si cayo abajo
bool Pelota::rebotarParedes()
{
    const double d = Config::PELOTA_DIAMETRO;

    if (item->x() <= 0) {
        item->setX(0);
        vx = qAbs(vx);
    } else if (item->x() + d >= Config::ESCENA_ANCHO) {
        item->setX(Config::ESCENA_ANCHO - d);
        vx = -qAbs(vx);
    }

    if (item->y() <= 0) {
        item->setY(0);
        vy = qAbs(vy);
    }

    return item->y() + d >= Config::ESCENA_ALTO;
}


bool Pelota::rebotarContraRect(const QRectF &obstaculo)
{
    QRectF r = rect();
    if (!r.intersects(obstaculo)) {
        return false;
    }

    double solapeX = qMin(r.right(), obstaculo.right()) - qMax(r.left(), obstaculo.left());
    double solapeY = qMin(r.bottom(), obstaculo.bottom()) - qMax(r.top(), obstaculo.top());

    if (solapeX < solapeY) {
        vx = (r.center().x() < obstaculo.center().x()) ? -qAbs(vx) : qAbs(vx);
    } else {
        vy = (r.center().y() < obstaculo.center().y()) ? -qAbs(vy) : qAbs(vy);
    }
    return true;
}


bool Pelota::rebotarConPaleta(const QRectF &paleta)
{
    if (vy <= 0) {
        return false;                       // solo cuando la pelota baja
    }
    QRectF r = rect();
    if (!r.intersects(paleta)) {
        return false;
    }
    if (r.center().y() > paleta.center().y()) {
        return false;                       // golpe por debajo: ya se paso la paleta
    }


    double offset = (r.center().x() - paleta.center().x()) / (paleta.width() / 2.0);
    offset = qBound(-1.0, offset, 1.0);

    fijarDireccion(offset * Config::PELOTA_ANGULO_MAX);
    item->setY(paleta.top() - Config::PELOTA_DIAMETRO);
    return true;
}

void Pelota::setVelocidad(double nuevaVelocidad)
{
    double actual = qHypot(vx, vy);
    if (actual > 0) {
        vx *= nuevaVelocidad / actual;
        vy *= nuevaVelocidad / actual;
    }
    velocidad = nuevaVelocidad;
}

QRectF Pelota::rect() const
{
    return QRectF(item->x(), item->y(), Config::PELOTA_DIAMETRO, Config::PELOTA_DIAMETRO);
}
