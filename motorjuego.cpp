#include "motorjuego.h"
#include <QBrush>
#include <QPen>

MotorJuego::MotorJuego(QObject *parent): QObject(parent){
    escena = new QGraphicsScene(this);
    paleta = nullptr;
    pelota = nullptr;
    timer = new QTimer(this);
    filas = 4;
    columnas = 6;
    matriz_bloques = nullptr;
    vx = 2.5;
    vy = -3.0;

    escena->setSceneRect(0,0,800,600);

    paleta = escena->addRect(0,0,100,14);
    paleta->setBrush(QBrush(Qt::cyan));
    paleta->setPos(350, 530);

    pelota = escena->addEllipse(0, 0, 20, 20);
    pelota->setBrush(QBrush(Qt::yellow));
    pelota->setPos(390, 350);

    crearNivelBasico();

    connect(timer, &QTimer::timeout, this, &MotorJuego::actualizarFrame);
}

MotorJuego::~MotorJuego() {
    liberarBloques();
}

void MotorJuego::crearNivelBasico() {
    liberarBloques();

    matriz_bloques = new QGraphicsRectItem**[filas];

    double anchoBloque = 100.0;
    double altoBloque = 25.0;
    double separacion = 10.0;
    double inicioX = 75.0;
    double inicioY = 60.0;

    for (int f = 0; f < filas; ++f) {
        matriz_bloques[f] = new QGraphicsRectItem*[columnas];
        for (int c = 0; c < columnas; ++c) {
            QGraphicsRectItem *bloque = escena->addRect(0, 0, anchoBloque, altoBloque);
            bloque->setBrush(QBrush(f%2 == 0 ? Qt::red : Qt::green));
            bloque->setPen(QPen(Qt::white, 1));
            bloque->setPos(inicioX + c * (anchoBloque + separacion),inicioY + f * (altoBloque + separacion));
            matriz_bloques[f][c] = bloque;
        }
    }
}

void MotorJuego::liberarBloques() {
    if (!matriz_bloques) {
        return;
    }

    for (int f = 0; f < filas; ++f) {
        if (matriz_bloques[f]) {
            for (int c = 0; c < columnas; ++c) {
                if (matriz_bloques[f][c]) {
                    escena->removeItem(matriz_bloques[f][c]);
                    delete matriz_bloques[f][c];
                    matriz_bloques[f][c] = nullptr;
                }
            }
            delete[] matriz_bloques[f];
            matriz_bloques[f] = nullptr;
        }
    }
    delete[] matriz_bloques;
    matriz_bloques = nullptr;
}

void MotorJuego::iniciar() {
    timer->start(16);
}

void MotorJuego::moverPaleta(double mov) {
    if (!paleta) {
        return;
    }
    qreal nuevaX = paleta->x() + mov;
    qreal limiteDer = escena->width() - paleta->rect().width();

    if (nuevaX < 0) {
        nuevaX = 0;
    } else if (nuevaX > limiteDer) {
        nuevaX = limiteDer;
    }
    paleta->setX(nuevaX);
}

void MotorJuego::actualizarFrame() {
    qreal nx = pelota->x() + vx;
    qreal ny = pelota->y() + vy;
    qreal w = pelota->rect().width();
    qreal h = pelota->rect().height();

    if (nx <= 0) {
        nx = 0;
        vx = -vx;
    } else if (nx + w >= escena->width()) {
        nx = escena->width() - w;
        vx = -vx;
    }

    if (ny <= 0) {
        ny = 0;
        vy = -vy;
    } else if (ny + h >= escena->height()) {
        // Proximamente game over
        nx = 390;
        ny = 350;
        vy = -3.0;
    }

    bool chocaX = (nx + w >= paleta->x()) && (nx <= paleta->x() + paleta->rect().width());
    bool chocaY = (vy > 0) && (pelota->y() + h <= paleta->y() + paleta->rect().height()) && (ny + h >= paleta->y());
    if (chocaX && chocaY) {
        ny = paleta->y() - h;
        vy = -vy;
    }

    if (matriz_bloques) {
        for (int f = 0; f < filas; ++f) {
            for (int c = 0; c < columnas; ++c) {
                QGraphicsRectItem *b = matriz_bloques[f][c];
                if (!b) {
                    continue;
                }

                bool golpeaBloque = (nx + w >= b->x()) && (nx <= b->x() + b->rect().width()) && (ny + h >= b->y()) && (ny <= b->y() + b->rect().height());

                if (golpeaBloque) {
                    escena->removeItem(b);
                    delete b;
                    matriz_bloques[f][c] = nullptr;
                    vy = -vy;
                    break;
                }
            }
        }
    }

    pelota->setPos(nx, ny);
}
