#ifndef ARISTA_H
#define ARISTA_H

// TAD Arista
template <class T>
class Arista {
protected:
    T destino;
    int costo;

public:
    Arista();
    Arista(const T& destino, int costo);
    T obtenerDestino() const;
    int obtenerCosto() const;
    void fijarDestino(const T& destino);
    void fijarCosto(int costo);
};

#include "Arista.hxx"
#endif
