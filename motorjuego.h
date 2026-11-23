#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QTimer>

class MotorJuego : public QObject //herencia
{
    Q_OBJECT
private:
    QGraphicsScene *escena;
    QGraphicsRectItem *paleta;
    QGraphicsEllipseItem *pelota;
    QTimer *timer;

    int filas;
    int columnas;
    QGraphicsRectItem ***matriz_bloques; //Reemplazar cuando tengamos clase bloque

    double vx;
    double vy;

    void crearNivelBasico();
    void liberarBloques();

private slots:
    void actualizarFrame();

public:
    MotorJuego(QObject *padre = nullptr);
    ~MotorJuego() override;

    QGraphicsScene* get_escena() const { return escena; }
    void iniciar();
    void moverPaleta(double mov);
};

#endif // MOTORJUEGO_H
