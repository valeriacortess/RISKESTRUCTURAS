#include "Grafo.h"

template <class T>
Grafo<T>::Grafo() : totalAristas(0) {
}

template <class T>
int Grafo<T>::obtenerCantidadVertices() const {
    return (int) this->vertices.size();
}

template <class T>
int Grafo<T>::obtenerCantidadAristas() const {
    return this->totalAristas;
}

template <class T>
std::vector<T> Grafo<T>::obtenerVertices() const {
    return this->vertices;
}

template <class T>
std::vector<Arista<T> > Grafo<T>::obtenerVecinos(const T& vertice) const {
    typename std::map<T, std::vector<Arista<T> > >::const_iterator it = this->adyacencia.find(vertice);
    if (it == this->adyacencia.end()) {
        return std::vector<Arista<T> >();
    }
    return it->second;
}

template <class T>
bool Grafo<T>::existeVertice(const T& vertice) const {
    return this->indiceVertice.find(vertice) != this->indiceVertice.end();
}

template <class T>
bool Grafo<T>::existeArista(const T& origen, const T& destino) const {
    return this->obtenerCosto(origen, destino) != -1;
}

template <class T>
int Grafo<T>::obtenerCosto(const T& origen, const T& destino) const {
    typename std::map<T, std::vector<Arista<T> > >::const_iterator it = this->adyacencia.find(origen);
    if (it == this->adyacencia.end()) {
        return -1;
    }
    for (size_t i = 0; i < it->second.size(); i++) {
        if (it->second[i].obtenerDestino() == destino) {
            return it->second[i].obtenerCosto();
        }
    }
    return -1;
}

template <class T>
bool Grafo<T>::insertarVertice(const T& vertice) {
    if (this->existeVertice(vertice)) {
        return false;
    }
    this->indiceVertice[vertice] = (int) this->vertices.size();
    this->vertices.push_back(vertice);
    this->adyacencia[vertice] = std::vector<Arista<T> >();
    return true;
}

template <class T>
bool Grafo<T>::insertarArista(const T& origen, const T& destino, int costo) {
    if (!this->existeVertice(origen) || !this->existeVertice(destino) || costo < 0) {
        return false;
    }
    if (this->existeArista(origen, destino)) {
        return false;
    }
    this->adyacencia[origen].push_back(Arista<T>(destino, costo));
    this->totalAristas++;
    return true;
}

template <class T>
bool Grafo<T>::fijarCosto(const T& origen, const T& destino, int costo) {
    typename std::map<T, std::vector<Arista<T> > >::iterator it = this->adyacencia.find(origen);
    if (it == this->adyacencia.end() || costo < 0) {
        return false;
    }
    for (size_t i = 0; i < it->second.size(); i++) {
        if (it->second[i].obtenerDestino() == destino) {
            it->second[i].fijarCosto(costo);
            return true;
        }
    }
    return false;
}

// Algoritmo de Dijkstra 
template <class T>
CaminosMinimos<T> Grafo<T>::caminosMinimos(const std::vector<T>& origenes) const {
    CaminosMinimos<T> resultado;
    std::priority_queue<EntradaCola, std::vector<EntradaCola>, CompararEntradas> cola;

    for (size_t i = 0; i < origenes.size(); i++) {
        if (this->existeVertice(origenes[i]) && !resultado.esAlcanzable(origenes[i])) {
            resultado.fijarOrigen(origenes[i]);
            EntradaCola entrada;
            entrada.costo = 0;
            entrada.saltos = 0;
            entrada.orden = this->indiceVertice.find(origenes[i])->second;
            entrada.vertice = origenes[i];
            cola.push(entrada);
        }
    }

    while (!cola.empty()) {
        EntradaCola actual = cola.top();
        cola.pop();

        
        if (actual.costo > resultado.obtenerCosto(actual.vertice)) {
            continue;
        }
        if (actual.costo == resultado.obtenerCosto(actual.vertice) &&
            actual.saltos > resultado.obtenerSaltos(actual.vertice)) {
            continue;
        }

        std::vector<Arista<T> > vecinos = this->obtenerVecinos(actual.vertice);
        for (size_t i = 0; i < vecinos.size(); i++) {
            T destino = vecinos[i].obtenerDestino();
            int nuevoCosto = actual.costo + vecinos[i].obtenerCosto();
            int nuevosSaltos = actual.saltos + 1;

            bool mejora = false;
            if (!resultado.esAlcanzable(destino)) {
                mejora = true;
            } else if (nuevoCosto < resultado.obtenerCosto(destino)) {
                mejora = true;
            } else if (nuevoCosto == resultado.obtenerCosto(destino) &&
                       nuevosSaltos < resultado.obtenerSaltos(destino)) {
                mejora = true;
            }

            if (mejora) {
                resultado.fijarResultado(destino, nuevoCosto, nuevosSaltos, actual.vertice);
                EntradaCola entrada;
                entrada.costo = nuevoCosto;
                entrada.saltos = nuevosSaltos;
                entrada.orden = this->indiceVertice.find(destino)->second;
                entrada.vertice = destino;
                cola.push(entrada);
            }
        }
    }
    return resultado;
}
