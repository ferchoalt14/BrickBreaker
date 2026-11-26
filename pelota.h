#ifndef PELOTA_H
#define PELOTA_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QRectF>

// La bola. Guarda su vector de velocidad (vx, vy) y sabe rebotar.
// Para multipelota: cada Pelota es independiente (tiene su propio vector).
class Pelota
{
private:
    QGraphicsScene *escena;
    QGraphicsEllipseItem *item;
    double vx;
    double vy;
    double velocidad;                 // magnitud del vector (pixeles por cuadro)

    void fijarDireccion(double gradosDesdeVertical);

public:
    explicit Pelota(QGraphicsScene *escena);
    ~Pelota();
    Pelota(const Pelota&) = delete;
    Pelota& operator=(const Pelota&) = delete;

    void reiniciar(double x, double y);   // posicion inicial y direccion de salida
    void mover();                         // suma el vector de velocidad a la posicion

    // Rebotes (devuelven true si hubo choque)
    bool rebotarParedes();                // true = la pelota cayo por abajo
    bool rebotarContraRect(const QRectF &obstaculo);  // ladrillos
    bool rebotarConPaleta(const QRectF &paleta);      // angulo segun punto de impacto

    // >>> EXTENSION: velocidad extra y aceleracion progresiva (nivel 3)
    void setVelocidad(double nuevaVelocidad);
    double getVelocidad() const { return velocidad; }

    QRectF rect() const;
};

#endif // PELOTA_H
