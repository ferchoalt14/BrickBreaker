#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>

class StartScreen : public QWidget {
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);

signals:
    void loginClicked();
    void createAccountClicked();
    void exitClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap fondo;
    QPushButton *btnIniciarSesion;
    QPushButton *btnCrearCuenta;
    QPushButton *btnSalir;
};

#endif // STARTSCREEN_H