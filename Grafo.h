#ifndef GRAFO_H
#define GRAFO_H

#include <map>
#include <queue>
#include <vector>
#include "Arista.h"
#include "CaminosMinimos.h"

// TAD Grafo: grafo dirigido y ponderado implementado con listas de adyacencia.
// Los vertices conservan el orden en que se insertaron.
template <class T>
class Grafo {
protected:
    std::vector<T> vertices;
    std::map<T, int> indiceVertice;
    std::map<T, std::vector<Arista<T> > > adyacencia;
    int totalAristas;

    // Entrada de la cola de prioridad usada al buscar caminos minimos.
    struct EntradaCola {
        int costo;
        int saltos;
        int orden;
        T vertice;
    };

    // Menor prioridad = menor costo; ante empate, menos saltos; luego, el vertice insertado primero.
    struct CompararEntradas {
        bool operator()(const EntradaCola& a, const EntradaCola& b) const {
            if (a.costo != b.costo) {
                return a.costo > b.costo;
            }
            if (a.saltos != b.saltos) {
                return a.saltos > b.saltos;
            }
            return a.orden > b.orden;
        }
    };

public:
    Grafo();
    int obtenerCantidadVertices() const;
    int obtenerCantidadAristas() const;
    std::vector<T> obtenerVertices() const;
    std::vector<Arista<T> > obtenerVecinos(const T& vertice) const;
    bool existeVertice(const T& vertice) const;
    bool existeArista(const T& origen, const T& destino) const;
    // Devuelve el costo de la arista, o -1 si no existe.
    int obtenerCosto(const T& origen, const T& destino) const;
    bool insertarVertice(const T& vertice);
    bool insertarArista(const T& origen, const T& destino, int costo);
    bool fijarCosto(const T& origen, const T& destino, int costo);
    // Camino de menor costo desde cualquiera de los vertices de origen hacia todos los demas.
    CaminosMinimos<T> caminosMinimos(const std::vector<T>& origenes) const;
};

#include "Grafo.hxx"
#endif
