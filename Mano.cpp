#include "Mano.h"
#include <iostream>
using namespace std;


Mano::Mano() {}
vector<Carta> Mano::getCartas() const{
    return cartas;
};

void Mano::agregarCarta(Carta carta) {
    if (cartas.size() >= 5) {
        cout << "no se puede agregar, ya tiene en mano el maximo de cartas" << endl;
        return;
    }

    vector<Carta>::iterator it01;
    for (it01 = cartas.begin(); it01 != cartas.end(); it01++) {
        bool ambasComodin = it01->esComodin() && carta.esComodin();
        bool mismaCartaNormal = (!it01->esComodin() && !carta.esComodin() && 
                                 it01->getTerritorio() == carta.getTerritorio() && 
                                 it01->getTipoEjercito() == carta.getTipoEjercito());

        if (ambasComodin || mismaCartaNormal) {
            cout << "ya tienes esta carta agregada en tu mano" << endl;
            return;
        }
    }

    cartas.push_back(carta);
}

void Mano::eliminarCarta(Carta carta) {
    vector<Carta>::iterator it02;
    for (it02 = cartas.begin(); it02 != cartas.end(); it02++) {
        bool ambasComodin = it02->esComodin() && carta.esComodin();
        bool mismaCartaNormal = (!it02->esComodin() && !carta.esComodin() && 
                                 it02->getTerritorio() == carta.getTerritorio() && 
                                 it02->getTipoEjercito() == carta.getTipoEjercito());

        if (ambasComodin || mismaCartaNormal) {
            cartas.erase(it02);
            return; 
        }
    }
}

void Mano::eliminarCartas(const vector<Carta> cartas_para_eliminar) {
    vector<Carta>::const_iterator it03;
    for (it03 = cartas_para_eliminar.begin(); it03 != cartas_para_eliminar.end(); it03++) {
        vector<Carta>::iterator it04;
        for (it04 = cartas.begin(); it04 != cartas.end(); it04++) {
            bool ambasComodin = it04->esComodin() && it03->esComodin();
            bool mismaCartaNormal = (!it04->esComodin() && !it03->esComodin() && 
                                     it04->getTerritorio() == it03->getTerritorio() && 
                                     it04->getTipoEjercito() == it03->getTipoEjercito());

            if (ambasComodin || mismaCartaNormal) {
                cartas.erase(it04);
                break;
            }
        }
    }
}

bool Mano::tieneCartaTerritorio(string codigoTerritorio) const{
    vector<Carta>::const_iterator it05;
    for (it05 = cartas.begin(); it05!= cartas.end(); it05++){
        if (!it05->esComodin() && it05->getTerritorio() == codigoTerritorio){
            return true;
        }
    }

    return false;
};

bool Mano::puedeCanjear() const{
    if (cartas.size()>=3){
        return true;
    }

    return false; 
};

// recibe el numero de intercambio como parametro, ya no incrementa ningun contador propio (eso lo hace Tablero).
int Mano::calcularUnidadesCanje(int numeroIntercambio) const {
    switch (numeroIntercambio) {
        case 1: return 4;
        case 2: return 6;
        case 3: return 8;
        case 4: return 10;
        case 5: return 12;
        case 6: return 15;
        default: return 15 + (numeroIntercambio - 6) * 5;
    }
}