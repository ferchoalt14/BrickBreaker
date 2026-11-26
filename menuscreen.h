#ifndef MENUSCREEN_H
#define MENUSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QPushButton>


class MenuScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MenuScreen(QWidget *parent = nullptr);
    void setUsuario(const QString &usuario);

signals:
    void mapaClicked();
    void cerrarSesionClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void construirInterfaz();
    void mostrarProximamente();

    QPixmap fondo;
    QLabel *lblTitulo;
    QLabel *lblMensaje;
    QPushButton *btnMapa;
    QPushButton *btnConfiguracion;
    QPushButton *btnPerfil;
    QPushButton *btnCerrarSesion;
};

#endif
