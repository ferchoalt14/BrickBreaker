#include "menuscreen.h"
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QTimer>

MenuScreen::MenuScreen(QWidget *parent) : QWidget(parent)
{
    fondo = QPixmap(":/images/basicScreen.jpg");
    setFixedSize(820, 620);
    construirInterfaz();
}

void MenuScreen::construirInterfaz()
{
    setStyleSheet(
        "QFrame#panel { background-color: rgba(0, 0, 0, 220);"
        "  border: 2px solid #00e5ff; border-radius: 14px; }"
        "QLabel { background: transparent; color: #e8f6ff; font-size: 14px; }"
        "QLabel#titulo { color: #00e5ff; font-size: 24px; font-weight: bold; }"
        "QPushButton { background-color: #7a3cff; color: white; border: none;"
        "  border-radius: 8px; font-size: 16px; font-weight: bold; }"
        "QPushButton:hover { background-color: #9a63ff; }"
        "QPushButton#cerrar { background-color: #1b2150; border: 2px solid #ff3c8e; }"
        "QPushButton#cerrar:hover { background-color: #ff3c8e; }"
    );

    QVBoxLayout *externo = new QVBoxLayout(this);
    externo->setContentsMargins(0, 0, 0, 0);

    QFrame *panel = new QFrame(this);
    panel->setObjectName("panel");
    panel->setFixedWidth(360);

    QVBoxLayout *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(40, 28, 40, 28);
    layout->setSpacing(14);

    lblTitulo = new QLabel("Menú principal", panel);
    lblTitulo->setObjectName("titulo");
    lblTitulo->setAlignment(Qt::AlignCenter);
    lblTitulo->setWordWrap(true);

    btnMapa = new QPushButton("Mapa de misiones", panel);
    btnConfiguracion = new QPushButton("Configuración", panel);
    btnPerfil = new QPushButton("Perfil", panel);
    btnCerrarSesion = new QPushButton("Cerrar sesión", panel);
    btnCerrarSesion->setObjectName("cerrar");

    QPushButton *botones[4] = { btnMapa, btnConfiguracion, btnPerfil, btnCerrarSesion };
    for (int i = 0; i < 4; ++i) {
        botones[i]->setFixedHeight(46);
    }

    lblMensaje = new QLabel(panel);
    lblMensaje->setAlignment(Qt::AlignCenter);
    lblMensaje->setMinimumHeight(20);

    layout->addWidget(lblTitulo);
    layout->addSpacing(6);
    layout->addWidget(btnMapa);
    layout->addWidget(btnConfiguracion);
    layout->addWidget(btnPerfil);
    layout->addWidget(btnCerrarSesion);
    layout->addWidget(lblMensaje);

    externo->addStretch();
    externo->addWidget(panel, 0, Qt::AlignHCenter);
    externo->addStretch();

    connect(btnMapa, &QPushButton::clicked, this, &MenuScreen::mapaClicked);
    connect(btnCerrarSesion, &QPushButton::clicked, this, &MenuScreen::cerrarSesionClicked);
    // Configuracion y Perfil todavia no estan hechos.
    connect(btnConfiguracion, &QPushButton::clicked, this, &MenuScreen::mostrarProximamente);
    connect(btnPerfil, &QPushButton::clicked, this, &MenuScreen::mostrarProximamente);
}

void MenuScreen::setUsuario(const QString &usuario)
{
    lblTitulo->setText("Bienvenido, " + usuario);
    lblMensaje->clear();
}

void MenuScreen::mostrarProximamente()
{
    lblMensaje->setStyleSheet("color: #ffd24a;");
    lblMensaje->setText("Disponible próximamente.");
    QTimer::singleShot(2000, this, [this]() { lblMensaje->clear(); });
}

void MenuScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    }
}
