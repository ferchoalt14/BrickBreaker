#include "motorjuego.h"
#include "configjuego.h"
#include <QColor>

MotorJuego::MotorJuego(QObject *parent) : QObject(parent),
    escena(nullptr), timer(nullptr), paleta(nullptr), pelota(nullptr),
    filas(0), columnas(0), matriz(nullptr), bloquesRestantes(0)
{
    escena = new QGraphicsScene(this);
    escena->setSceneRect(0, 0, Config::ESCENA_ANCHO, Config::ESCENA_ALTO);
    escena->setBackgroundBrush(QColor("#0b0f1e"));

    paleta = new Paleta(escena);
    pelota = new Pelota(escena);
    crearNivelBasico();

    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);   // temporizador de alta precision
    connect(timer, &QTimer::timeout, this, &MotorJuego::actualizarFrame);
}

// Orden importante: la escena (hija de este objeto) sigue viva mientras
// se liberan ladrillos, pelota y paleta.
MotorJuego::~MotorJuego()
{
    if (timer) {
        timer->stop();
    }
    liberarBloques();
    delete pelota;
    pelota = nullptr;
    delete paleta;
    paleta = nullptr;
}

// >>> EXTENSION (niveles 2 y 3): aqui se decide que tipo de ladrillo va en cada celda.
// Ejemplo nivel 2: fila 0 -> Reforzado; columna 7 -> Indestructible.
TipoBloque MotorJuego::tipoParaCelda(int fila, int columna) const
{
    Q_UNUSED(fila);
    Q_UNUSED(columna);
    return TipoBloque::Normal;
}

void MotorJuego::crearNivelBasico()
{
    liberarBloques();

    filas = Config::FILAS;
    columnas = Config::COLUMNAS;
    bloquesRestantes = 0;

    // Matriz dinamica: arreglo de filas, y cada fila es un arreglo de Bloque
    matriz = new Bloque*[filas];
    for (int f = 0; f < filas; ++f) {
        matriz[f] = new Bloque[columnas];
    }

    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            double x = Config::BLOQUES_INICIO_X + c * (Config::BLOQUE_ANCHO + Config::BLOQUE_SEPARACION);
            double y = Config::BLOQUES_INICIO_Y + f * (Config::BLOQUE_ALTO + Config::BLOQUE_SEPARACION);
            TipoBloque tipo = tipoParaCelda(f, c);

            matriz[f][c].crear(escena, x, y, tipo);
            if (tipo != TipoBloque::Indestructible) {
                ++bloquesRestantes;
            }
        }
    }
}

// delete[] de cada fila llama al destructor de cada Bloque (que libera su objeto grafico)
void MotorJuego::liberarBloques()
{
    if (!matriz) {
        return;
    }
    for (int f = 0; f < filas; ++f) {
        delete[] matriz[f];
        matriz[f] = nullptr;
    }
    delete[] matriz;
    matriz = nullptr;
}

void MotorJuego::reiniciarPelota()
{
    pelota->reiniciar(Config::PELOTA_INICIO_X, Config::PELOTA_INICIO_Y);
}

void MotorJuego::iniciar()
{
    timer->start(Config::FRAME_MS);
}

void MotorJuego::detener()
{
    timer->stop();
}

// Un cuadro del juego: mover paleta, mover pelota, revisar choques.
void MotorJuego::actualizarFrame()
{
    paleta->actualizar();
    pelota->mover();

    if (pelota->rebotarParedes()) {
        emit pelotaPerdida();        // >>> EXTENSION: aqui se resta una vida
        reiniciarPelota();
        return;
    }

    pelota->rebotarConPaleta(paleta->rect());
    procesarBloques();
}

// Revisa la pelota contra cada ladrillo activo. Un ladrillo por cuadro.
void MotorJuego::procesarBloques()
{
    for (int f = 0; f < filas; ++f) {
        for (int c = 0; c < columnas; ++c) {
            Bloque &b = matriz[f][c];
            if (!b.estaActivo()) {
                continue;
            }
            if (!pelota->rebotarContraRect(b.rect())) {
                continue;
            }

            if (b.recibirGolpe()) {          // true = el ladrillo se destruyo
                --bloquesRestantes;
                emit bloqueDestruido();      // >>> EXTENSION: aqui se suma puntaje / suelta power-up
                if (bloquesRestantes == 0) {
                    emit nivelCompletado();  // >>> EXTENSION: aqui va la pantalla de victoria
                    if (Config::REINICIAR_AL_COMPLETAR) {
                        crearNivelBasico();
                        reiniciarPelota();
                    }
                }
            }
            return;
        }
    }
}
