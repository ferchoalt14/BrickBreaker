#include <QApplication>
#include <QStackedWidget>
#include "startscreen.h"
#include "pruebamotor.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stack;
    stack.setWindowTitle("Brick Breaker");
    stack.setFixedSize(820, 620);

    StartScreen *startScreen = new StartScreen(&stack);
    pruebaMotor *gameView = new pruebaMotor(&stack);

    stack.addWidget(startScreen);
    stack.addWidget(gameView);
    stack.setCurrentIndex(0);

    QObject::connect(startScreen, &StartScreen::loginClicked, [&stack, gameView]() {
        stack.setCurrentIndex(1);
        gameView->setFocus();
    });

    QObject::connect(startScreen, &StartScreen::createAccountClicked, [&stack, gameView]() {
        stack.setCurrentIndex(1);
        gameView->setFocus();
    });

    stack.show();
    return app.exec();
}