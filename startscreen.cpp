#include "startscreen.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QApplication>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    fondo = QPixmap(":/images/startScreen.jpg");
    setFixedSize(820, 620);

    btnIniciarSesion = new QPushButton("Iniciar sesion", this);
    btnCrearCuenta = new QPushButton("Crear cuenta", this);
    btnSalir = new QPushButton("Salir", this);

    btnIniciarSesion->setFixedSize(220, 46);
    btnCrearCuenta->setFixedSize(220, 46);
    btnSalir->setFixedSize(220, 46);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(btnIniciarSesion, 0, Qt::AlignHCenter);
    layout->addSpacing(14);
    layout->addWidget(btnCrearCuenta, 0, Qt::AlignHCenter);
    layout->addSpacing(14);
    layout->addWidget(btnSalir, 0, Qt::AlignHCenter);
    layout->addSpacing(60);

    connect(btnIniciarSesion, &QPushButton::clicked, this, &StartScreen::loginClicked);
    connect(btnCrearCuenta, &QPushButton::clicked, this, &StartScreen::createAccountClicked);
    connect(btnSalir, &QPushButton::clicked, qApp, &QApplication::quit);
}

void StartScreen::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);
    QPainter painter(this);
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    }
}