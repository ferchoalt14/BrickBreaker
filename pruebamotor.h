#ifndef PRUEBAMOTOR_H
#define PRUEBAMOTOR_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "motorjuego.h"

class pruebaMotor : public QGraphicsView
{
    Q_OBJECT
private:
    MotorJuego *motor;
    void keyPressEvent(QKeyEvent *event) override;
public:
    explicit pruebaMotor(QWidget *parent = nullptr);
    ~pruebaMotor() override;
    void iniciar();
};

#endif // PRUEBAMOTOR_H
