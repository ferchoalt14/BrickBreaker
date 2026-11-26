#ifndef PALETA_H
#define PALETA_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRectF>

// La plataforma del jugador. Se mueve cada cuadro segun las teclas que esten
// presionadas (movimiento fluido, no "casilla por casilla").
class Paleta
{
private:
    QGraphicsScene *escena;
    QGraphicsRectItem *item;
    bool izquierda;
    bool derecha;
    double velocidad;

    void limitarAPantalla();

public:
    explicit Paleta(QGraphicsScene *escena);
    ~Paleta();
    Paleta(const Paleta&) = delete;
    Paleta& operator=(const Paleta&) = delete;

    // Entrada (la llama la vista al presionar/soltar teclas)
    void setIzquierda(bool presionada) { izquierda = presionada; }
    void setDerecha(bool presionada) { derecha = presionada; }
    void detener();                      // suelta todas las teclas

    // Se llama una vez por cuadro desde MotorJuego
    void actualizar();

    void centrarEn(double x);            // para seguir al mouse
    void reiniciar();                    // vuelve al centro

    // >>> EXTENSION (power-ups): alargar / reducir paleta y velocidad extra
    void setAncho(double ancho);
    void setVelocidad(double nuevaVelocidad) { velocidad = nuevaVelocidad; }
    double getVelocidad() const { return velocidad; }

    QRectF rect() const;
};

#endif // PALETA_H
