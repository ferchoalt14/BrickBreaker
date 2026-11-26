#ifndef GESTORUSUARIOS_H
#define GESTORUSUARIOS_H

#include <QString>
#include "usuario.h"

enum class ResultadoRegistro {
    Ok,
    NombreInvalido,
    ClaveInvalida,
    UsuarioExistente,
    ErrorGuardado
};


class GestorUsuarios
{
private:
    Usuario *cabeza;
    Usuario *cola;
    int total;
    QString rutaArchivo;

    Usuario* buscar(const QString &nombre) const;
    void agregarAlFinal(Usuario *nuevo);
    void liberar();
    void cargar();
    bool guardar() const;

    static QString calcularHash(const QString &nombre, const QString &clave);
    static QString rutaPorDefecto();

public:
    GestorUsuarios();
    ~GestorUsuarios();


    GestorUsuarios(const GestorUsuarios&) = delete;
    GestorUsuarios& operator=(const GestorUsuarios&) = delete;

    ResultadoRegistro registrar(const QString &nombre, const QString &clave);
    bool validar(const QString &nombre, const QString &clave) const;
    bool existe(const QString &nombre) const;
    bool historiaVista(const QString &nombre) const;
    bool marcarHistoriaVista(const QString &nombre);
    int cantidad() const { return total; }

    static bool nombreValido(const QString &nombre);
    static bool claveValida(const QString &clave);
};

#endif
