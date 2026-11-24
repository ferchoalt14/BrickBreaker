#include "pruebamotor.h"
#include <QApplication>
#include <QPushButton>

pruebaMotor::pruebaMotor(QWidget *parent): QGraphicsView(parent){
    motor = new MotorJuego(this);
    setScene(motor->get_escena());
    setFixedSize(820, 620);
    setWindowTitle("Prueba de MotorJuego - Brick Breaker");

    // Boton para cerrar el programa desde el juego (no roba el foco del teclado).
    QPushButton *btnSalir = new QPushButton("Salir", viewport());
    btnSalir->setFixedSize(80, 30);
    btnSalir->move(730, 8);
    btnSalir->setFocusPolicy(Qt::NoFocus);
    btnSalir->setStyleSheet(
        "QPushButton { background-color: rgba(8, 10, 30, 230); color: white;"
        "  border: 2px solid #ff3c8e; border-radius: 6px; font-weight: bold; }"
        "QPushButton:hover { background-color: #ff3c8e; }");
    connect(btnSalir, &QPushButton::clicked, qApp, &QApplication::quit);
}

pruebaMotor::~pruebaMotor() {
    delete motor;
    motor = nullptr;
}

void pruebaMotor::iniciar() {
    motor->iniciar();
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
