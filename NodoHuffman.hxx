#include "NodoHuffman.h"

template <class T>
NodoHuffman<T>::NodoHuffman(T val, unsigned long frec) {
    this->dato = val;
    this->frecuencia = frec;
    this->hijoIzq = NULL;
    this->hijoDer = NULL;
    this->esHojaNodo = true;
}

template <class T>
NodoHuffman<T>::NodoHuffman(unsigned long frec, NodoHuffman<T>* izq, NodoHuffman<T>* der) {
    this->frecuencia = frec;
    this->hijoIzq = izq;
    this->hijoDer = der;
    this->esHojaNodo = false;
}

template <class T>
NodoHuffman<T>::~NodoHuffman() {
    if (this->hijoIzq != NULL) {
        delete this->hijoIzq;
        this->hijoIzq = NULL;
    }
    if (this->hijoDer != NULL) {
        delete this->hijoDer;
        this->hijoDer = NULL;
    }
}

template <class T>
T NodoHuffman<T>::obtenerDato() const {
    return this->dato;
}

template <class T>
unsigned long NodoHuffman<T>::obtenerFrecuencia() const {
    return this->frecuencia;
}

template <class T>
NodoHuffman<T>* NodoHuffman<T>::obtenerHijoIzq() const {
    return this->hijoIzq;
}

template <class T>
NodoHuffman<T>* NodoHuffman<T>::obtenerHijoDer() const {
    return this->hijoDer;
}

template <class T>
bool NodoHuffman<T>::esHoja() const {
    return this->esHojaNodo;
}
