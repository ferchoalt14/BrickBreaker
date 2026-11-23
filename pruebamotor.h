#ifndef PRUEBAMOTOR_H
#define PRUEBAMOTOR_H

#include <QGraphicsView>
#include <QKeyEvent>
#include "MotorJuego.h"

class pruebaMotor : public QGraphicsView
{
    Q_OBJECT
private:
    MotorJuego *motor;
    void keyPressEvent(QKeyEvent *event) override;
public:
    pruebaMotor(QWidget *parent = nullptr);
    ~pruebaMotor() override;
};

#endif // PRUEBAMOTOR_H
