#ifndef BLOQUE_H
#define BLOQUE_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QRectF>

// Tipos de ladrillo. Para un tipo nuevo: agregarlo aqui y en
// Bloque::aplicarEstilo() y Bloque::recibirGolpe() (ambos en bloque.cpp).
enum class TipoBloque {
    Normal,          // se rompe con 1 golpe
    Reforzado,       // se rompe con 2 golpes (cambia de color al daniarse)
    Indestructible   // obstaculo fijo
};

// Un ladrillo de la matriz. La matriz del nivel es Bloque** (punteros dobles).
class Bloque
{
private:
    QGraphicsScene *escena;
    QGraphicsRectItem *item;   // objeto grafico (se elimina al destruir el ladrillo)
    TipoBloque tipo;
    int golpesRestantes;
    bool activo;

    void aplicarEstilo();      // color metalico segun tipo y dano

public:
    Bloque();
    ~Bloque();
    Bloque(const Bloque&) = delete;             // evita copiar punteros por error
    Bloque& operator=(const Bloque&) = delete;

    void crear(QGraphicsScene *escena, double x, double y, TipoBloque tipo);
    bool recibirGolpe();       // devuelve true si el ladrillo se destruyo
    void destruir();           // libera SOLO este ladrillo (objeto grafico)

    bool estaActivo() const { return activo; }
    bool esDestructible() const { return tipo != TipoBloque::Indestructible; }
    QRectF rect() const;       // posicion y tamanio en la escena
};

#endif // BLOQUE_H
