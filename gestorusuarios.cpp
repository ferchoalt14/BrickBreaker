#include "gestorusuarios.h"

#include <QCryptographicHash>
#include <QDir>
#include <QFileInfo>
#include <QRegularExpression>
#include <QStandardPaths>

#include <filesystem>
#include <fstream>
#include <string>

GestorUsuarios::GestorUsuarios()
    : cabeza(nullptr), cola(nullptr), total(0), rutaArchivo(rutaPorDefecto())
{
    cargar();
}

GestorUsuarios::~GestorUsuarios()
{
    liberar();
}


QString GestorUsuarios::rutaPorDefecto()
{
    QString carpeta = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    return carpeta + "/usuarios.txt";
}

QString GestorUsuarios::calcularHash(const QString &nombre, const QString &clave)
{

    QByteArray datos = (nombre.toLower() + ":" + clave).toUtf8();
    QByteArray hash = QCryptographicHash::hash(datos, QCryptographicHash::Sha256);
    return QString::fromLatin1(hash.toHex());
}

bool GestorUsuarios::nombreValido(const QString &nombre)
{

    static const QRegularExpression patron("^[A-Za-z0-9_]{3,16}$");
    return patron.match(nombre).hasMatch();
}

bool GestorUsuarios::claveValida(const QString &clave)
{
    return clave.length() >= 4 && clave.length() <= 32;
}

Usuario* GestorUsuarios::buscar(const QString &nombre) const
{
    Usuario *actual = cabeza;
    while (actual != nullptr) {
        if (QString::compare(actual->getNombre(), nombre, Qt::CaseInsensitive) == 0) {
            return actual;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

void GestorUsuarios::agregarAlFinal(Usuario *nuevo)
{
    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
    } else {
        cola->setSiguiente(nuevo);
        cola = nuevo;
    }
    ++total;
}

void GestorUsuarios::liberar()
{
    Usuario *actual = cabeza;
    while (actual != nullptr) {
        Usuario *siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    total = 0;
}


void GestorUsuarios::cargar()
{
    std::ifstream archivo{std::filesystem::path(rutaArchivo.toStdWString())};
    if (!archivo.is_open()) {
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        if (!linea.empty() && linea.back() == '\r') {
            linea.pop_back();
        }
        std::size_t pos = linea.find(';');
        if (pos == std::string::npos || pos == 0 || pos + 1 >= linea.size()) {
            continue;
        }
        QString nombre = QString::fromStdString(linea.substr(0, pos));
        std::string resto = linea.substr(pos + 1);


        std::size_t pos2 = resto.find(';');
        bool vista = false;
        if (pos2 != std::string::npos) {
            vista = (resto.substr(pos2 + 1) == "1");
            resto = resto.substr(0, pos2);
        }
        QString hash = QString::fromStdString(resto);
        if (buscar(nombre) == nullptr) {
            agregarAlFinal(new Usuario(nombre, hash, vista));
        }
    }
}

bool GestorUsuarios::guardar() const
{
    QDir().mkpath(QFileInfo(rutaArchivo).absolutePath());

    std::ofstream archivo{std::filesystem::path(rutaArchivo.toStdWString()),
                          std::ios::out | std::ios::trunc};
    if (!archivo.is_open()) {
        return false;
    }

    Usuario *actual = cabeza;
    while (actual != nullptr) {
        archivo << actual->getNombre().toStdString() << ';'
                << actual->getHashClave().toStdString() << ';'
                << (actual->getHistoriaVista() ? '1' : '0') << '\n';
        actual = actual->getSiguiente();
    }
    archivo.flush();
    return archivo.good();
}

ResultadoRegistro GestorUsuarios::registrar(const QString &nombre, const QString &clave)
{
    if (!nombreValido(nombre)) {
        return ResultadoRegistro::NombreInvalido;
    }
    if (!claveValida(clave)) {
        return ResultadoRegistro::ClaveInvalida;
    }
    if (buscar(nombre) != nullptr) {
        return ResultadoRegistro::UsuarioExistente;
    }

    Usuario *nuevo = new Usuario(nombre, calcularHash(nombre, clave));
    agregarAlFinal(nuevo);

    if (!guardar()) {

        if (cabeza == nuevo) {
            cabeza = nullptr;
            cola = nullptr;
        } else {
            Usuario *previo = cabeza;
            while (previo->getSiguiente() != nuevo) {
                previo = previo->getSiguiente();
            }
            previo->setSiguiente(nullptr);
            cola = previo;
        }
        delete nuevo;
        --total;
        return ResultadoRegistro::ErrorGuardado;
    }
    return ResultadoRegistro::Ok;
}

bool GestorUsuarios::existe(const QString &nombre) const
{
    return buscar(nombre) != nullptr;
}

bool GestorUsuarios::validar(const QString &nombre, const QString &clave) const
{
    Usuario *u = buscar(nombre);
    if (u == nullptr) {
        return false;
    }
    return u->getHashClave() == calcularHash(u->getNombre(), clave);
}

bool GestorUsuarios::historiaVista(const QString &nombre) const
{
    Usuario *u = buscar(nombre);
    return u != nullptr && u->getHistoriaVista();
}

bool GestorUsuarios::marcarHistoriaVista(const QString &nombre)
{
    Usuario *u = buscar(nombre);
    if (u == nullptr) {
        return false;
    }
    u->setHistoriaVista(true);
    return guardar();
}
