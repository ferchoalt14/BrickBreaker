#ifndef PRUEBAMOTOR_H
#define PRUEBAMOTOR_H

#include <QGraphicsView>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include "motorjuego.h"

// La ventana del juego: muestra la escena y traduce teclado/mouse a ordenes para la paleta.
class pruebaMotor : public QGraphicsView
{
    Q_OBJECT
private:
    MotorJuego *motor;

    void manejarTecla(int tecla, bool presionada);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

public:
    explicit pruebaMotor(QWidget *parent = nullptr);
    ~pruebaMotor() override;
    void iniciar();
};

#endif // PRUEBAMOTOR_H
