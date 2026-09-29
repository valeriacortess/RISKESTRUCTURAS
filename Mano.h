#ifndef MANO_H
#define MANO_H
#include <string>
#include <vector>
#include "Carta.h"
using namespace std;

class Mano{ 
    private:

        vector<Carta> cartas;

    public:

        Mano();
        vector<Carta> getCartas() const;
        void agregarCarta(Carta carta);
        void eliminarCarta(Carta carta);
        void eliminarCartas(const vector<Carta> cartas_para_eliminar);
        bool tieneCartaTerritorio(string territorio) const;
        bool puedeCanjear() const;
        int calcularUnidadesCanje(int numeroIntercambio) const;
};

#endif