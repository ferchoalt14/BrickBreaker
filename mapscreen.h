#ifndef MAPSCREEN_H
#define MAPSCREEN_H

#include <QWidget>
#include <QPixmap>
#include <QPushButton>
#include <QLabel>


class MapScreen : public QWidget
{
    Q_OBJECT

public:
    explicit MapScreen(QWidget *parent = nullptr);

signals:
    void jugarNivel1Clicked();
    void jugarNivel2Clicked();
    void volverClicked();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap fondo;
    QPushButton *btnNivel1;
    QLabel *lblNivel1;
    QPushButton *btnNivel2;
    QLabel *lblNivel2;
    QPushButton *btnVolver;
};

#endif // MAPSCREEN_H
