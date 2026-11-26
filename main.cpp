#include <QApplication>
#include <QStackedWidget>
#include "startscreen.h"
#include "loginscreen.h"
#include "storyscreen.h"
#include "menuscreen.h"
#include "mapscreen.h"
#include "pruebamotor.h"
#include "gestorusuarios.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);


    GestorUsuarios gestor;

    QStackedWidget stack;
    stack.setWindowTitle("Brick Breaker");
    stack.setFixedSize(820, 620);

    stack.setWindowFlags(Qt::Window | Qt::CustomizeWindowHint |
                         Qt::WindowTitleHint | Qt::WindowMinimizeButtonHint);

    StartScreen *startScreen = new StartScreen(&stack);
    LoginScreen *loginScreen = new LoginScreen(&gestor, &stack);
    StoryScreen *storyScreen = new StoryScreen(&stack);
    MenuScreen *menuScreen = new MenuScreen(&stack);
    MapScreen *mapScreen = new MapScreen(&stack);
    pruebaMotor *gameView = new pruebaMotor(&stack);

    stack.addWidget(startScreen);
    stack.addWidget(loginScreen);
    stack.addWidget(storyScreen);
    stack.addWidget(menuScreen);
    stack.addWidget(mapScreen);
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


    QObject::connect(loginScreen, &LoginScreen::loginExitoso,
                     [&](const QString &usuario) {
        usuarioActual = usuario;
        menuScreen->setUsuario(usuario);
        if (gestor.historiaVista(usuario)) {
            stack.setCurrentWidget(menuScreen);
        } else {
            storyScreen->iniciar();
            stack.setCurrentWidget(storyScreen);
        }
    });


    QObject::connect(storyScreen, &StoryScreen::historiaTerminada, [&]() {
        gestor.marcarHistoriaVista(usuarioActual);
        stack.setCurrentWidget(menuScreen);
    });

    // Menu principal
    QObject::connect(menuScreen, &MenuScreen::mapaClicked, [&stack, mapScreen]() {
        stack.setCurrentWidget(mapScreen);
    });

    QObject::connect(menuScreen, &MenuScreen::cerrarSesionClicked, [&]() {
        usuarioActual.clear();
        stack.setCurrentWidget(startScreen);
    });

    // Mapa de misiones
    QObject::connect(mapScreen, &MapScreen::volverClicked, [&stack, menuScreen]() {
        stack.setCurrentWidget(menuScreen);
    });

    QObject::connect(mapScreen, &MapScreen::jugarNivel1Clicked, [&stack, gameView]() {
        stack.setCurrentWidget(gameView);
        gameView->iniciar();
        gameView->setFocus();
    });

    stack.show();
    return app.exec();
}
