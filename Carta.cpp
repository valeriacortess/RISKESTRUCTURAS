#include "Carta.h"
using namespace std;

// Constructor para cartas normales: fija comodin en falso,
Carta::Carta(string territorio, string tipo_ejercito) :
    territorio(territorio), tipo_ejercito(tipo_ejercito), comodin(false) {
}

// Constructor para comodines: no recibe parametros, ya que un
// comodin no tiene territorio ni tipo de ejercito fijo.
Carta::Carta() : territorio(""), tipo_ejercito(""), comodin(true) {
}

string Carta::getTerritorio() const { return territorio; }

string Carta::getTipoEjercito() const { return tipo_ejercito; }

bool Carta::esComodin() const { return comodin; }

// Si alguna de las dos cartas es comodin, siempre
// hace match (retorna verdadero). Si ninguna es comodin, compara
// directamente el tipo_ejercito de ambas.
bool Carta::mismoTipo(Carta carta1) const {
    if (comodin || carta1.esComodin()) {
        return true;
    }
    return tipo_ejercito == carta1.getTipoEjercito();
}

// Verifica si un conjunto de 3 cartas forma una combinacion valida
// para canjear, segun las reglas del enunciado:
//   - 3 cartas del mismo tipo
//   - 1 carta de cada tipo (infanteria, caballeria, artilleria)
//   - cualquier combinacion que incluya 1 o mas comodines
bool Carta::esCombinacionValida(vector<Carta> cartas) {
    if (cartas.size() != 3) {
        return false;
    }

    int cantidadComodines = 0;
    vector<string> tiposNoComodin;

    for (size_t i = 0; i < cartas.size(); i++) {
        if (cartas[i].esComodin()) {
            cantidadComodines++;
        } else {
            tiposNoComodin.push_back(cartas[i].getTipoEjercito());
        }
    }

    // Con 2 o 3 comodines, siempre se puede completar una combinacion
    // valida (el o los comodines rellenan lo que haga falta).
    if (cantidadComodines >= 2) {
        return true;
    }

    // Con exactamente 1 comodin, quedan 2 cartas reales: sean iguales
    // (se completan a 3 del mismo tipo) o distintas (el comodin
    // rellena el tercer tipo), ambos casos son validos.
    if (cantidadComodines == 1) {
        return true;
    }

    // Sin comodines: deben ser 3 del mismo tipo, o 3 tipos distintos (uno de cada uno).
    bool tresIguales = (tiposNoComodin[0] == tiposNoComodin[1]) && (tiposNoComodin[1] == tiposNoComodin[2]);
    bool tresDistintos = (tiposNoComodin[0] != tiposNoComodin[1]) && (tiposNoComodin[1] != tiposNoComodin[2]) && (tiposNoComodin[0] != tiposNoComodin[2]);

    return tresIguales || tresDistintos;
}