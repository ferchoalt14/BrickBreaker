#include "loginscreen.h"
#include <QPainter>
#include <QFrame>
#include <QVBoxLayout>

LoginScreen::LoginScreen(GestorUsuarios *gestor, QWidget *parent)
    : QWidget(parent), gestor(gestor), modo(Modo::IniciarSesion)
{
    fondo = QPixmap(":/images/loginScreen.jpg");
    setFixedSize(820, 620);
    construirInterfaz();
    setModo(Modo::IniciarSesion);
}

void LoginScreen::construirInterfaz()
{
    setStyleSheet(
        "QFrame#panel { background-color: rgba(8, 10, 30, 215);"
        "  border: 2px solid #00e5ff; border-radius: 14px; }"
        "QLabel { background: transparent; color: #e8f6ff; font-size: 14px; }"
        "QLabel#titulo { color: #00e5ff; font-size: 26px; font-weight: bold; }"
        "QLineEdit { background-color: #0d1233; color: white; border: 1px solid #7a3cff;"
        "  border-radius: 6px; padding: 8px; font-size: 14px; }"
        "QLineEdit:focus { border: 1px solid #00e5ff; }"
        "QCheckBox { background: transparent; color: #e8f6ff; font-size: 13px; spacing: 8px; }"
        "QCheckBox::indicator { width: 16px; height: 16px; border: 1px solid #00e5ff;"
        "  border-radius: 3px; background-color: #0d1233; }"
        "QCheckBox::indicator:checked { background-color: #00e5ff; }"
        "QPushButton { background-color: #7a3cff; color: white; border: none;"
        "  border-radius: 6px; padding: 10px; font-size: 14px; font-weight: bold; }"
        "QPushButton:hover { background-color: #9a63ff; }"
        "QPushButton#volver { background-color: #1b2150; }"
        "QPushButton#volver:hover { background-color: #2a3280; }"
    );

    QVBoxLayout *externo = new QVBoxLayout(this);
    externo->setContentsMargins(0, 0, 0, 0);

    QFrame *panel = new QFrame(this);
    panel->setObjectName("panel");
    panel->setFixedWidth(360);

    QVBoxLayout *layout = new QVBoxLayout(panel);
    layout->setContentsMargins(28, 24, 28, 24);
    layout->setSpacing(12);

    lblTitulo = new QLabel(panel);
    lblTitulo->setObjectName("titulo");
    lblTitulo->setAlignment(Qt::AlignCenter);

    editUsuario = new QLineEdit(panel);
    editUsuario->setPlaceholderText("Usuario");
    editUsuario->setMaxLength(16);

    editClave = new QLineEdit(panel);
    editClave->setPlaceholderText("Contraseña");
    editClave->setEchoMode(QLineEdit::Password);
    editClave->setMaxLength(32);

    editConfirmar = new QLineEdit(panel);
    editConfirmar->setPlaceholderText("Confirmar contraseña");
    editConfirmar->setEchoMode(QLineEdit::Password);
    editConfirmar->setMaxLength(32);

    chkMostrar = new QCheckBox("Mostrar contraseña", panel);

    lblMensaje = new QLabel(panel);
    lblMensaje->setWordWrap(true);
    lblMensaje->setAlignment(Qt::AlignCenter);
    lblMensaje->setMinimumHeight(40);

    btnAccion = new QPushButton(panel);
    btnVolver = new QPushButton("Volver", panel);
    btnVolver->setObjectName("volver");

    layout->addWidget(lblTitulo);
    layout->addWidget(editUsuario);
    layout->addWidget(editClave);
    layout->addWidget(editConfirmar);
    layout->addWidget(chkMostrar);
    layout->addWidget(lblMensaje);
    layout->addWidget(btnAccion);
    layout->addWidget(btnVolver);

    externo->addStretch();
    externo->addWidget(panel, 0, Qt::AlignHCenter);
    externo->addStretch();

    connect(btnAccion, &QPushButton::clicked, this, &LoginScreen::alPresionarAccion);
    connect(editUsuario, &QLineEdit::returnPressed, this, &LoginScreen::alPresionarAccion);
    connect(editClave, &QLineEdit::returnPressed, this, &LoginScreen::alPresionarAccion);
    connect(editConfirmar, &QLineEdit::returnPressed, this, &LoginScreen::alPresionarAccion);
    connect(btnVolver, &QPushButton::clicked, this, &LoginScreen::volverClicked);
    connect(chkMostrar, &QCheckBox::toggled, this, [this](bool visible) {
        QLineEdit::EchoMode modoEco = visible ? QLineEdit::Normal : QLineEdit::Password;
        editClave->setEchoMode(modoEco);
        editConfirmar->setEchoMode(modoEco);
    });
}

void LoginScreen::setModo(Modo nuevoModo)
{
    modo = nuevoModo;

    editUsuario->clear();
    editClave->clear();
    editConfirmar->clear();
    lblMensaje->clear();
    chkMostrar->setChecked(false);

    if (modo == Modo::IniciarSesion) {
        lblTitulo->setText("Iniciar sesión");
        btnAccion->setText("Entrar");
        editConfirmar->hide();
    } else {
        lblTitulo->setText("Crear cuenta");
        btnAccion->setText("Crear cuenta");
        editConfirmar->show();
    }
    editUsuario->setFocus();
}

void LoginScreen::mostrarMensaje(const QString &texto, bool esError)
{
    lblMensaje->setStyleSheet(esError ? "color: #ff5c7a;" : "color: #5cff9d;");
    lblMensaje->setText(texto);
}

void LoginScreen::alPresionarAccion()
{
    const QString usuario = editUsuario->text().trimmed();
    const QString clave = editClave->text();

    if (modo == Modo::IniciarSesion) {
        if (usuario.isEmpty() || clave.isEmpty()) {
            mostrarMensaje("Escribe tu usuario y contraseña.", true);
            return;
        }
        if (!gestor->validar(usuario, clave)) {
            mostrarMensaje("Usuario o contraseña incorrectos.", true);
            return;
        }
        editClave->clear();
        lblMensaje->clear();
        emit loginExitoso(usuario);
        return;
    }

    // Modo crear cuenta
    if (clave != editConfirmar->text()) {
        mostrarMensaje("Las contraseñas no coinciden.", true);
        return;
    }

    switch (gestor->registrar(usuario, clave)) {
    case ResultadoRegistro::Ok:
        // Inicio de sesion automatico: deja la pantalla lista en modo login
        // (por si se vuelve) y entra directo al juego.
        setModo(Modo::IniciarSesion);
        emit loginExitoso(usuario);
        break;
    case ResultadoRegistro::NombreInvalido:
        mostrarMensaje("El usuario debe tener de 3 a 16 caracteres: letras, números o _.", true);
        break;
    case ResultadoRegistro::ClaveInvalida:
        mostrarMensaje("La contraseña debe tener entre 4 y 32 caracteres.", true);
        break;
    case ResultadoRegistro::UsuarioExistente:
        mostrarMensaje("Ese usuario ya existe. Elige otro.", true);
        break;
    case ResultadoRegistro::ErrorGuardado:
        mostrarMensaje("No se pudo guardar la cuenta en el archivo.", true);
        break;
    }
}

void LoginScreen::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    if (!fondo.isNull()) {
        painter.drawPixmap(rect(), fondo);
    }
}
