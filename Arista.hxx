#include "Arista.h"

template <class T>
Arista<T>::Arista() : destino(), costo(0) {
}

template <class T>
Arista<T>::Arista(const T& destino, int costo) : destino(destino), costo(costo) {
}

template <class T>
T Arista<T>::obtenerDestino() const {
    return this->destino;
}

template <class T>
int Arista<T>::obtenerCosto() const {
    return this->costo;
}

template <class T>
void Arista<T>::fijarDestino(const T& destino) {
    this->destino = destino;
}

template <class T>
void Arista<T>::fijarCosto(int costo) {
    this->costo = costo;
}
