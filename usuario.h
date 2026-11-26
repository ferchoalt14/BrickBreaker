#ifndef USUARIO_H
#define USUARIO_H

#include <QString>


class Usuario
{
private:
    QString nombre;
    QString hashClave;
    bool historiaVista;
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

#endif
