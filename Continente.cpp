#include "Continente.h"
using namespace std;

Continente::Continente(string nombre, int bonificacion) :
    nombre(nombre), bonificacion(bonificacion), territorios(vector<Territorio*>()) {
}

string Continente::getNombre() const { return nombre; }

int Continente::getBonificacion() const { return bonificacion; }

vector<Territorio*> Continente::getTerritorios() const { return territorios; }

void Continente::agregarTerritorio(Territorio* territorio) {
    territorios.push_back(territorio);
}

bool Continente::contieneTerritorio(string codigoTerritorio) const {
    for (size_t i = 0; i < territorios.size(); i++) {
        if (territorios[i]->getCodigo() == codigoTerritorio) {
            return true;
        }
    }
    return false;
}

bool Continente::esControladoPor(string color) const {
    if (territorios.empty()) {
        return false;
    }
    for (size_t i = 0; i < territorios.size(); i++) {
        if (territorios[i]->getColorOcupado() != color) {
            return false;
        }
    }
    return true;
}