#include "mapscreen.h"
#include <QPainter>

MapScreen::MapScreen(QWidget *parent) : QWidget(parent)
{
    fondo = QPixmap(":/images/levelsScreen.jpg");
    setFixedSize(820, 620);

    setStyleSheet(
        "QPushButton#nivel1 { background-color: rgba(0, 229, 255, 45); color: #e8f6ff;"
        "  border: 3px solid #00e5ff; border-radius: 35px;"
        "  font-size: 30px; font-weight: bold; }"
        "QPushButton#nivel1:hover { background-color: rgba(0, 229, 255, 140); }"
        "QPushButton#nivel2 { background-color: rgba(0, 229, 255, 45); color: #e8f6ff;"
        "  border: 3px solid #00e5ff; border-radius: 35px;"
        "  font-size: 30px; font-weight: bold; }"
        "QPushButton#nivel2:hover { background-color: rgba(0, 229, 255, 140); }"
        "QLabel#etiqueta { background: transparent; color: #00e5ff;"
        "  font-size: 14px; font-weight: bold; }"
        "QPushButton#volver { background-color: rgba(0, 0, 0, 220); color: white;"
        "  border: 2px solid #ff3c8e; border-radius: 8px;"
        "  font-size: 14px; font-weight: bold; }"
        "QPushButton#volver:hover { background-color: #ff3c8e; }"
    );

    // Se coloca encima del primer circulo de la imagen (centro aprox. 122, 334).
    btnNivel1 = new QPushButton("1", this);
    btnNivel1->setObjectName("nivel1");
    btnNivel1->setFixedSize(71, 94);
    btnNivel1->move(87, 288);
    btnNivel1->setCursor(Qt::PointingHandCursor);

    lblNivel1 = new QLabel("Jugar nivel 1", this);
    lblNivel1->setObjectName("etiqueta");
    lblNivel1->setAlignment(Qt::AlignCenter);
    lblNivel1->setFixedSize(140, 24);
    lblNivel1->move(52, 392);

    btnNivel2 = new QPushButton("2", this);
    btnNivel2->setObjectName("nivel2");
    btnNivel2->setFixedSize(71, 94);
    btnNivel2->move(211, 288);
    btnNivel2->setCursor(Qt::PointingHandCursor);

    lblNivel2 = new QLabel("Jugar nivel 2", this);
    lblNivel2->setObjectName("etiqueta");
    lblNivel2->setAlignment(Qt::AlignCenter);
    lblNivel2->setFixedSize(140, 24);
    lblNivel2->move(176, 392);

    btnVolver = new QPushButton("Volver al menú", this);
    btnVolver->setObjectName("volver");
    btnVolver->setFixedSize(190, 40);
    btnVolver->move((820 - 190) / 2, 495);

    connect(btnNivel1, &QPushButton::clicked, this, &MapScreen::jugarNivel1Clicked);
    connect(btnNivel2, &QPushButton::clicked, this, &MapScreen::jugarNivel2Clicked);
    connect(btnVolver, &QPushButton::clicked, this, &MapScreen::volverClicked);
}

void MapScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    }
}
