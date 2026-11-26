#ifndef LOGINSCREEN_H
#define LOGINSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QPushButton>
#include "gestorusuarios.h"


class LoginScreen : public QWidget
{
    Q_OBJECT

public:
    enum class Modo { IniciarSesion, CrearCuenta };

    explicit LoginScreen(GestorUsuarios *gestor, QWidget *parent = nullptr);
    void setModo(Modo nuevoModo);

signals:
    void loginExitoso(const QString &usuario);
    void volverClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void alPresionarAccion();

private:
    void construirInterfaz();
    void mostrarMensaje(const QString &texto, bool esError);

    GestorUsuarios *gestor;
    Modo modo;
    QPixmap fondo;

    QLabel *lblTitulo;
    QLabel *lblMensaje;
    QLineEdit *editUsuario;
    QLineEdit *editClave;
    QLineEdit *editConfirmar;
    QCheckBox *chkMostrar;
    QPushButton *btnAccion;
    QPushButton *btnVolver;
};

#endif // LOGINSCREEN_H
