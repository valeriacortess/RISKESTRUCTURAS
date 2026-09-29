#ifndef CONTINENTE_H
#define CONTINENTE_H
#include <string>
#include <vector>
#include "Territorio.h"
using namespace std;

class Continente {
    private:

    string nombre;
    int bonificacion;
    vector<Territorio*> territorios;

    public:

    Continente(string nombre, int bonificacion);
    string getNombre() const;
    int getBonificacion() const;
    vector<Territorio*> getTerritorios() const;
    void agregarTerritorio(Territorio* territorio);
    bool contieneTerritorio(string codigoTerritorio) const;
    bool esControladoPor(string color) const;
};

#endif