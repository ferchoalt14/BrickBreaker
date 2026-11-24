#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>

// Mapa de misiones (fondo levelsScreen). Por ahora solo el nivel 1 esta disponible.
class MapScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MapScreen(QWidget *parent = nullptr);

signals:
    void jugarNivel1Clicked();
    void volverClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap fondo;
    QPushButton *btnNivel1;
    QLabel *lblNivel1;
    QPushButton *btnVolver;
};

#endif // MAPSCREEN_H
