#ifndef USUARIO_H
#define USUARIO_H

#include <QString>

// Nodo de la lista enlazada de usuarios (cada cuenta registrada).
class Usuario
{
private:
    QString nombre;
    QString hashClave;      // SHA-256 de la clave, nunca la clave en texto plano
    bool historiaVista;     // true cuando ya vio (o salto) la historia inicial
    Usuario *siguiente;

public:
    Usuario(const QString &nombre, const QString &hashClave, bool historiaVista = false);

    QString getNombre() const { return nombre; }
    QString getHashClave() const { return hashClave; }
    bool getHistoriaVista() const { return historiaVista; }
    void setHistoriaVista(bool v) { historiaVista = v; }
    Usuario* getSiguiente() const { return siguiente; }
    void setSiguiente(Usuario *s) { siguiente = s; }
};

#endif // USUARIO_H
