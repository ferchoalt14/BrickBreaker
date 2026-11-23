#include <iostream>

#include <QApplication>
#include "pruebamotor.h"

using namespace std;

int main(int argc, char *argv[])
{
    cout << "Inicio de proyecto." << endl;
    QApplication app(argc, argv);

    pruebaMotor prueba;
    prueba.show();

    return app.exec();
}
