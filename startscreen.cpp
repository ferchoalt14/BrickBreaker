#include "startscreen.h"
#include <QPainter>
#include <QVBoxLayout>
#include <QApplication>

StartScreen::StartScreen(QWidget *parent) : QWidget(parent) {
    fondo = QPixmap(":/images/startScreen.jpg");
    setFixedSize(820, 620);

    // Botones con fondo oscuro, borde neon y texto en negrita para que resalten.
    setStyleSheet(
        "QPushButton { background-color: rgba(8, 10, 30, 230); color: white;"
        "  border: 2px solid #00e5ff; border-radius: 8px;"
        "  font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #7a3cff; border-color: white; }"
        "QPushButton:pressed { background-color: #4b1fb8; }"
        "QPushButton#salir { border-color: #ff3c8e; }"
        "QPushButton#salir:hover { background-color: #ff3c8e; }"
    );

    btnIniciarSesion = new QPushButton("Iniciar sesion", this);
    btnCrearCuenta = new QPushButton("Crear cuenta", this);
    btnSalir = new QPushButton("Salir", this);
    btnSalir->setObjectName("salir");

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
