#include "pruebamotor.h"
#include "configjuego.h"
#include <QApplication>
#include <QColor>
#include <QPainter>
#include <QPushButton>
#include <QLabel>

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

    btnSalir = new QPushButton("Salir", viewport());
    btnSalir->setFixedSize(80, 30);
    btnSalir->move(730, 8);
    btnSalir->setFocusPolicy(Qt::NoFocus);
    btnSalir->setStyleSheet(
        "QPushButton { background-color: rgba(8, 10, 30, 230); color: white;"
        "  border: 2px solid #ff3c8e; border-radius: 6px; font-weight: bold; }"
        "QPushButton:hover { background-color: #ff3c8e; }");

    lblTimer = crearlblTimer();
    lblTimer->show();

    //connect(btnSalir, &QPushButton::clicked, qApp, &QApplication::quit);
    connect(btnSalir, &QPushButton::clicked, this, &pruebaMotor::salirPresionado);
    connect(motor, &MotorJuego::segundoTranscurrido, this, &pruebaMotor::actualizarTimer);

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

QLabel* pruebaMotor::crearlblTimer(){
    QLabel *label = new QLabel("00:00", viewport());
    label->setObjectName("lblTimer");
    label->setStyleSheet(
        "QLabel#lblTimer { color: #00e5ff; background-color: rgba(8, 10, 30, 200);"
        "  border: 1px solid #00e5ff; border-radius: 6px;"
        "  padding: 4px 10px; font-size: 16px; font-weight: bold; }"
        );
    label->move(20, 8);
    label->adjustSize();
    label->show();
    return label;
}

void pruebaMotor::actualizarTimer(int tiempoRestante){
    if (tiempoRestante < 0) {
        tiempoRestante = 0;
    }

    int minutos = tiempoRestante / 60;
    int segundos = tiempoRestante % 60;

    QString texto = QString("%1:%2").arg(minutos, 2, 10, QChar('0')).arg(segundos, 2, 10, QChar('0'));

    if (lblTimer) {
        lblTimer->setText(texto);
        lblTimer->adjustSize();
    }

}
