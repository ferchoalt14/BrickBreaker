#ifndef MOTORJUEGO_H
#define MOTORJUEGO_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include "bloque.h"
#include "paleta.h"
#include "pelota.h"

// Coordina las piezas: la escena, la paleta, la pelota y la matriz de ladrillos.
// Cada pieza vive en su propia clase; aqui solo se decide que pasa en cada cuadro.
class MotorJuego : public QObject
{
    Q_OBJECT
private:
    QGraphicsScene *escena;
    QTimer *timer;
    Paleta *paleta;
    Pelota *pelota;

    int filas;
    int columnas;
    Bloque **matriz;           // matriz dinamica con punteros dobles (new / delete[])
    int bloquesRestantes;      // ladrillos destructibles que quedan

    void crearNivelBasico();
    TipoBloque tipoParaCelda(int fila, int columna) const;
    void liberarBloques();
    void procesarBloques();
    void reiniciarPelota();

private slots:
    void actualizarFrame();    // se ejecuta cada FRAME_MS milisegundos

signals:
    // >>> EXTENSION: conectar estas senales para puntaje, vidas y pantallas de fin
    void bloqueDestruido();
    void pelotaPerdida();
    void nivelCompletado();

public:
    explicit MotorJuego(QObject *padre = nullptr);
    ~MotorJuego() override;

    QGraphicsScene* get_escena() const { return escena; }
    Paleta* getPaleta() const { return paleta; }
    Pelota* getPelota() const { return pelota; }

    void iniciar();
    void detener();
};

#endif // MOTORJUEGO_H
