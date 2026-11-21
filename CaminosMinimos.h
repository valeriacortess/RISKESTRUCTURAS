#ifndef CAMINOS_MINIMOS_H
#define CAMINOS_MINIMOS_H

#include <map>
#include <set>
#include <vector>

// TAD CaminosMinimos: resultado de buscar, desde un conjunto de vertices de origen,

class CaminosMinimos {
protected:
    std::map<T, int> costos;
    std::map<T, int> saltos;
    std::map<T, T> predecesores;
    std::set<T> origenes;

public:
    CaminosMinimos();
    bool esAlcanzable(const T& vertice) const;
    bool esOrigen(const T& vertice) const;
    int obtenerCosto(const T& vertice) const;
    int obtenerSaltos(const T& vertice) const;
    T obtenerPredecesor(const T& vertice) const;
    void fijarOrigen(const T& vertice);
    void fijarResultado(const T& vertice, int costo, int saltos, const T& predecesor);
    // Devuelve el camino [origen, ..., vertice]. Vacio si el vertice no es alcanzable.
    std::vector<T> reconstruirCamino(const T& vertice) const;
};

#include "CaminosMinimos.hxx"
#endif
