#include "storyscreen.h"
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

StoryScreen::StoryScreen(QWidget *parent)
    : QWidget(parent), paginaActual(0)
{
    fondo = QPixmap(":/images/basicScreen.jpg");
    for (int i = 0; i < TOTAL_PAGINAS; ++i) {
        imagenes[i] = QPixmap(QString(":/images/rulesScreen%1.jpg").arg(i + 1));
    }

    textos[0] = "Synth Pedro Sula, año 2098. Figura entre las ciudades más peligrosas "
                "y contaminadas del mundo, pero aquí a nadie le falta tecnología, "
                "aunque se viva en la miseria.";
    textos[1] = "Las megacorporaciones se adueñaron de la ciudad. Hoy es más fácil "
                "costearse una pieza robótica para el cuerpo que un hogar. Mientras la "
                "gente humilde sobrevive entre la basura, las corporaciones viven en "
                "el cielo, rodeadas de la mejor tecnología.";
    textos[2] = "Ahora todo está cambiando. El gobierno dejó de intervenir y las "
                "corporaciones más poderosas intentan cerrar la ciudad con muros de "
                "ladrillo. Sus robots sellan calle por calle para aislar a los pobres "
                "del resto de las zonas y dejarlos a su suerte.";
    textos[3] = "Nosotros somos la rebelión. Romperemos esos muros ladrillo por "
                "ladrillo, liberaremos Synth Pedro Sula y derrocaremos a las "
                "megacorporaciones. La ciudad volverá a ser libre.";

    setFixedSize(820, 620);
    construirInterfaz();
    mostrarPagina(0);
}

void StoryScreen::construirInterfaz()
{
    setStyleSheet(
        "QFrame#panel { background-color: rgba(0, 0, 0, 220);"
        "  border: 2px solid #00e5ff; border-radius: 14px; }"
        "QLabel { background: transparent; color: #e8f6ff; font-size: 15px; }"
        "QLabel#imagen { border: 1px solid #7a3cff; }"
        "QLabel#pagina { color: #8fb8cc; font-size: 13px; }"
        "QPushButton { background-color: #7a3cff; color: white; border: none;"
        "  border-radius: 6px; padding: 10px 22px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #9a63ff; }"
        "QPushButton#saltar { background-color: #1b2150; }"
        "QPushButton#saltar:hover { background-color: #2a3280; }"
        );

    QVBoxLayout *externo = new QVBoxLayout(this);
    externo->setContentsMargins(0, 0, 0, 0);

    QFrame *panel = new QFrame(this);
    panel->setObjectName("panel");
    panel->setFixedWidth(620);

    QVBoxLayout *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(28, 22, 28, 22);
    layout->setSpacing(14);

    lblImagen = new QLabel(panel);
    lblImagen->setObjectName("imagen");
    lblImagen->setFixedSize(562, 315);
    lblImagen->setAlignment(Qt::AlignCenter);

    lblTexto = new QLabel(panel);
    lblTexto->setWordWrap(true);
    lblTexto->setAlignment(Qt::AlignCenter);
    lblTexto->setMinimumHeight(110);

    lblPagina = new QLabel(panel);
    lblPagina->setObjectName("pagina");
    lblPagina->setAlignment(Qt::AlignCenter);

    btnSaltar = new QPushButton("Saltar historia", panel);
    btnSaltar->setObjectName("saltar");
    btnSiguiente = new QPushButton(panel);

    QHBoxLayout *botones = new QHBoxLayout();
    botones->addWidget(btnSaltar);
    botones->addStretch();
    botones->addWidget(lblPagina);
    botones->addStretch();
    botones->addWidget(btnSiguiente);

    layout->addWidget(lblImagen, 0, Qt::AlignHCenter);
    layout->addWidget(lblTexto);
    layout->addLayout(botones);

    externo->addStretch();
    externo->addWidget(panel, 0, Qt::AlignHCenter);
    externo->addStretch();

    connect(btnSiguiente, &QPushButton::clicked, this, &StoryScreen::alPresionarSiguiente);
    connect(btnSaltar, &QPushButton::clicked, this, &StoryScreen::historiaTerminada);
}

void StoryScreen::mostrarPagina(int indice)
{
    paginaActual = indice;

    // La imagen se escala completa al recuadro (sin recortar), aunque el archivo
    // original sea mucho mas grande. Se escala a los pixeles reales de la
    // pantalla (zoom de Windows) para que se vea nitida.
    if (!imagenes[indice].isNull()) {
        const qreal dpr = devicePixelRatioF();
        QPixmap escalada = imagenes[indice].scaled(QSize(560, 313) * dpr,
                                                   Qt::KeepAspectRatio,
                                                   Qt::SmoothTransformation);
        escalada.setDevicePixelRatio(dpr);
        lblImagen->setPixmap(escalada);
    }
    lblTexto->setText(textos[indice]);
    lblPagina->setText(QString("%1 / %2").arg(indice + 1).arg(TOTAL_PAGINAS));
    btnSiguiente->setText(indice == TOTAL_PAGINAS - 1 ? "Comenzar" : "Siguiente");
}

void StoryScreen::iniciar()
{
    mostrarPagina(0);
}

void StoryScreen::alPresionarSiguiente()
{
    if (paginaActual < TOTAL_PAGINAS - 1) {
        mostrarPagina(paginaActual + 1);
    } else {
        emit historiaTerminada();
    }
}

void StoryScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    }
}