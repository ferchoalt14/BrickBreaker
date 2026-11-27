#include "pruebamotor.h"
#include "configjuego.h"
#include <QApplication>
#include <QColor>
#include <QPainter>
#include <QPushButton>

pruebaMotor::pruebaMotor(QWidget *parent): QGraphicsView(parent){
    motor = new MotorJuego(this);
    setScene(motor->get_escena());
    setFixedSize(820, 620);
    setWindowTitle("Prueba de MotorJuego - Brick Breaker");

    setBackgroundBrush(QColor("#0b0f1e"));
    setRenderHint(QPainter::Antialiasing);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFocusPolicy(Qt::StrongFocus);
    viewport()->setMouseTracking(true);

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

void pruebaMotor::iniciar(int nivel) {
    motor->iniciar(nivel);
}

// Teclas de movimiento: se guarda si estan presionadas o no.
// La paleta se mueve cada cuadro mientras la tecla siga abajo (movimiento fluido).
// >>> EXTENSION: aqui se agregan mas teclas (pausa, disparo laser, etc.)
void pruebaMotor::manejarTecla(int tecla, bool presionada) {
    Paleta *paleta = motor->getPaleta();

    if (tecla == Qt::Key_Left || tecla == Qt::Key_A) {
        paleta->setIzquierda(presionada);
    } else if (tecla == Qt::Key_Right || tecla == Qt::Key_D) {
        paleta->setDerecha(presionada);
    }
}

void pruebaMotor::keyPressEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;                       // se ignora la repeticion automatica del teclado
    }
    manejarTecla(event->key(), true);
    QGraphicsView::keyPressEvent(event);
}

void pruebaMotor::keyReleaseEvent(QKeyEvent *event) {
    if (event->isAutoRepeat()) {
        return;
    }
    manejarTecla(event->key(), false);
    QGraphicsView::keyReleaseEvent(event);
}

// Si la ventana pierde el foco con una tecla presionada, la paleta se detiene
void pruebaMotor::focusOutEvent(QFocusEvent *event) {
    motor->getPaleta()->detener();
    QGraphicsView::focusOutEvent(event);
}

// Interruptor en configjuego.h: PALETA_SIGUE_MOUSE
void pruebaMotor::mouseMoveEvent(QMouseEvent *event) {
    if (Config::PALETA_SIGUE_MOUSE) {
        motor->getPaleta()->centrarEn(mapToScene(event->position().toPoint()).x());
    }
    QGraphicsView::mouseMoveEvent(event);
}
