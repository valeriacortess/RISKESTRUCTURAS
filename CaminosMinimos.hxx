#include "CaminosMinimos.h"

template <class T>
CaminosMinimos<T>::CaminosMinimos() {
}

template <class T>
bool CaminosMinimos<T>::esAlcanzable(const T& vertice) const {
    return this->costos.find(vertice) != this->costos.end();
}

template <class T>
bool CaminosMinimos<T>::esOrigen(const T& vertice) const {
    return this->origenes.find(vertice) != this->origenes.end();
}

template <class T>
int CaminosMinimos<T>::obtenerCosto(const T& vertice) const {
    typename std::map<T, int>::const_iterator it = this->costos.find(vertice);
    if (it == this->costos.end()) {
        return -1;
    }
    return it->second;
}

template <class T>
int CaminosMinimos<T>::obtenerSaltos(const T& vertice) const {
    typename std::map<T, int>::const_iterator it = this->saltos.find(vertice);
    if (it == this->saltos.end()) {
        return -1;
    }
    return it->second;
}

template <class T>
T CaminosMinimos<T>::obtenerPredecesor(const T& vertice) const {
    typename std::map<T, T>::const_iterator it = this->predecesores.find(vertice);
    if (it == this->predecesores.end()) {
        return T();
    }
    return it->second;
}

template <class T>
void CaminosMinimos<T>::fijarOrigen(const T& vertice) {
    this->origenes.insert(vertice);
    this->costos[vertice] = 0;
    this->saltos[vertice] = 0;
    this->predecesores[vertice] = vertice;
}

template <class T>
void CaminosMinimos<T>::fijarResultado(const T& vertice, int costo, int saltos, const T& predecesor) {
    this->costos[vertice] = costo;
    this->saltos[vertice] = saltos;
    this->predecesores[vertice] = predecesor;
}

template <class T>
std::vector<T> CaminosMinimos<T>::reconstruirCamino(const T& vertice) const {
    std::vector<T> camino;
    if (!this->esAlcanzable(vertice)) {
        return camino;
    }
    // Se recorre hacia atras desde el vertice hasta llegar a un origen.
    T actual = vertice;
    camino.push_back(actual);
    while (!this->esOrigen(actual)) {
        actual = this->obtenerPredecesor(actual);
        camino.push_back(actual);
    }
    // Se invierte para dejar el camino de origen a destino.
    std::vector<T> ordenado;
    for (int i = (int) camino.size() - 1; i >= 0; i--) {
        ordenado.push_back(camino[i]);
    }
    return ordenado;
}
