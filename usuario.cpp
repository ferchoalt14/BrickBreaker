#include "usuario.h"

Usuario::Usuario(const QString &nombre, const QString &hashClave, bool historiaVista)
    : nombre(nombre), hashClave(hashClave), historiaVista(historiaVista), siguiente(nullptr)
{
}
