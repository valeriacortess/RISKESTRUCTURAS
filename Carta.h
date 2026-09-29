#ifndef CARTA_H
#define CARTA_H
#include <string>
#include <vector>
using namespace std;

class Carta {
    private:

    string territorio;
    string tipo_ejercito;
    bool comodin;

    public:

    // Constructor para las 42 cartas normales (con territorio y tipo fijo).
    Carta(string territorio, string tipo_ejercito);

    // Constructor para las 2 cartas comodin (sin territorio ni tipo fijo).
    Carta();

    string getTerritorio() const;
    string getTipoEjercito() const;
    bool esComodin() const;

    bool mismoTipo(Carta carta1) const;

    // No es un metodo de instancia: evalua un CONJUNTO de cartas,
    // no una carta individual, asi que se declara aparte (no recibe
    // "this" como una de las cartas a comparar).
    static bool esCombinacionValida(vector<Carta> cartas);
};

#endif