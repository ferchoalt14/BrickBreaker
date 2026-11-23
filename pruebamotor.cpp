#include "pruebamotor.h"

pruebaMotor::pruebaMotor(QWidget *parent): QGraphicsView(parent){
    motor = new MotorJuego(this);
    setScene(motor->get_escena());
    setFixedSize(820, 620);
    setWindowTitle("Prueba de MotorJuego - Brick Breaker");

    motor->iniciar();

}

pruebaMotor::~pruebaMotor() {
    delete motor;
    motor = nullptr;
}

void pruebaMotor::keyPressEvent(QKeyEvent *event) {
    double mov = 20.0;

    if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
        motor->moverPaleta(-mov);
    } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
        motor->moverPaleta(mov);
    } else {
        QGraphicsView::keyPressEvent(event);
    }
}
