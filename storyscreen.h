#ifndef STORYSCREEN_H
#define STORYSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QString>
#include <QLabel>
#include <QPushButton>

// Historia introductoria: 4 paginas (imagen + texto) sobre el fondo basicScreen.
class StoryScreen : public QWidget
{
    Q_OBJECT

public:
    explicit StoryScreen(QWidget *parent = nullptr);
    void iniciar();     // vuelve a la primera pagina

signals:
    void historiaTerminada();   // se emite al terminar o al saltar

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

#endif // STORYSCREEN_H
