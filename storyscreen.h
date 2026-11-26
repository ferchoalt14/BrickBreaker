#ifndef STORYSCREEN_H
#define STORYSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QPushButton>


class StoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StoryScreen(QWidget *parent = nullptr);
    void iniciar();

signals:
    void historiaTerminada();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void alPresionarSiguiente();

private:
    static constexpr int TOTAL_PAGINAS = 4;

    void construirInterfaz();
    void mostrarPagina(int indice);

    QPixmap fondo;
    QPixmap imagenes[TOTAL_PAGINAS];
    QString textos[TOTAL_PAGINAS];
    int paginaActual;

    QLabel *lblImagen;
    QLabel *lblTexto;
    QLabel *lblPagina;
    QPushButton *btnSiguiente;
    QPushButton *btnSaltar;
};

#endif
