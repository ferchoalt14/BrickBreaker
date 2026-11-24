#include <QApplication>
#include <QStackedWidget>
#include "startscreen.h"
#include "loginscreen.h"
#include "storyscreen.h"
#include "pruebamotor.h"
#include "gestorusuarios.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Se crea antes que la ventana: se destruye despues de ella.
    GestorUsuarios gestor;

    QStackedWidget stack;
    stack.setWindowTitle("Brick Breaker");
    stack.setFixedSize(820, 620);
    // Sin boton de cerrar (X): la unica forma de salir es el boton "Salir".
    stack.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint |
                         Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);

    StartScreen *startScreen = new StartScreen(&stack);
    LoginScreen *loginScreen = new LoginScreen(&gestor, &stack);
    StoryScreen *storyScreen = new StoryScreen(&stack);
    pruebaMotor *gameView = new pruebaMotor(&stack);

    stack.addWidget(startScreen);
    stack.addWidget(loginScreen);
    stack.addWidget(storyScreen);
    stack.addWidget(gameView);
    stack.setCurrentWidget(startScreen);

    // "Iniciar sesion" y "Crear cuenta" van a la misma pantalla, en distinto modo.
    QObject::connect(startScreen, &StartScreen::loginClicked, [&stack, loginScreen]() {
        loginScreen->setModo(LoginScreen::Modo::IniciarSesion);
        stack.setCurrentWidget(loginScreen);
    });

    QObject::connect(startScreen, &StartScreen::createAccountClicked, [&stack, loginScreen]() {
        loginScreen->setModo(LoginScreen::Modo::CrearCuenta);
        stack.setCurrentWidget(loginScreen);
    });

    QObject::connect(loginScreen, &LoginScreen::volverClicked, [&stack, startScreen]() {
        stack.setCurrentWidget(startScreen);
    });

    QString usuarioActual;

    auto irAlJuego = [&stack, gameView]() {
        stack.setCurrentWidget(gameView);
        gameView->iniciar();
        gameView->setFocus();
    };

    // Primera vez de la cuenta -> historia; si ya la vio -> directo al juego.
    QObject::connect(loginScreen, &LoginScreen::loginExitoso,
                     [&](const QString &usuario) {
        usuarioActual = usuario;
        if (gestor.historiaVista(usuario)) {
            irAlJuego();
        } else {
            storyScreen->iniciar();
            stack.setCurrentWidget(storyScreen);
        }
    });

    // Al terminar o saltar la historia se recuerda para no mostrarla otra vez.
    QObject::connect(storyScreen, &StoryScreen::historiaTerminada, [&]() {
        gestor.marcarHistoriaVista(usuarioActual);
        irAlJuego();
    });

    stack.show();
    return app.exec();
}
