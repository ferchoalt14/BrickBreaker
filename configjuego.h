#ifndef CONFIGJUEGO_H
#define CONFIGJUEGO_H

// ============================================================
//  PANEL DE CONTROL DEL JUEGO
//  Todos los numeros "magicos" estan aqui. Para cambiar tamanos,
//  velocidades o cantidad de ladrillos, se cambia SOLO este archivo.
// ============================================================
namespace Config {

    // ---- Escena ----
    constexpr int    ESCENA_ANCHO = 800;
    constexpr int    ESCENA_ALTO  = 600;
    constexpr int    FRAME_MS     = 16;          // ~60 cuadros por segundo

    // ---- Ladrillos (pequenos y muchos) ----
    constexpr int    FILAS               = 8;
    constexpr int    COLUMNAS            = 15;
    constexpr double BLOQUE_ANCHO        = 44.0;
    constexpr double BLOQUE_ALTO         = 16.0;
    constexpr double BLOQUE_SEPARACION   = 4.0;
    constexpr double BLOQUES_INICIO_Y    = 60.0;
    // Centra la grilla horizontalmente
    constexpr double BLOQUES_INICIO_X    =
        (ESCENA_ANCHO - (COLUMNAS * (BLOQUE_ANCHO + BLOQUE_SEPARACION) - BLOQUE_SEPARACION)) / 2.0;

    // ---- Paleta ----
    constexpr double PALETA_ANCHO        = 100.0;
    constexpr double PALETA_ALTO         = 14.0;
    constexpr double PALETA_Y            = 540.0;
    constexpr double PALETA_VELOCIDAD    = 10.0;  // pixeles por cuadro (mas alto = mas agil)

    // ---- Pelota ----
    constexpr double PELOTA_DIAMETRO       = 16.0;
    constexpr double PELOTA_VELOCIDAD      = 5.0;   // pixeles por cuadro
    constexpr double PELOTA_ANGULO_INICIAL = 25.0;  // grados respecto a la vertical
    constexpr double PELOTA_ANGULO_MAX     = 60.0;  // angulo maximo al rebotar en el borde de la paleta
    constexpr double PELOTA_INICIO_X       = ESCENA_ANCHO / 2.0 - PELOTA_DIAMETRO / 2.0;
    constexpr double PELOTA_INICIO_Y       = 350.0;

    // ---- INTERRUPTORES (activar/desactivar funciones) ----
    constexpr bool   PALETA_SIGUE_MOUSE       = false; // true: la paleta tambien sigue al mouse
    constexpr bool   REINICIAR_AL_COMPLETAR   = true;  // true: al romper todo, se arma el nivel otra vez
                                                       // (temporal, hasta tener pantalla de victoria)

    constexpr int NIVEL_1 = 1;
    constexpr int NIVEL_2 = 2;
    constexpr int NIVEL_3 = 3;
}

#endif // CONFIGJUEGO_H
