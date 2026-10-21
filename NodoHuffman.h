#ifndef NODO_HUFFMAN_H
#define NODO_HUFFMAN_H

template <class T>
class NodoHuffman {
protected:
    T dato;
    unsigned long frecuencia;
    NodoHuffman<T>* hijoIzq;
    NodoHuffman<T>* hijoDer;
    bool esHojaNodo;

public:
    // Constructor para hoja
    NodoHuffman(T val, unsigned long frec);

    // Constructor para nodo interno
    NodoHuffman(unsigned long frec, NodoHuffman<T>* izq, NodoHuffman<T>* der);

    ~NodoHuffman();

    T obtenerDato() const;
    unsigned long obtenerFrecuencia() const;
    NodoHuffman<T>* obtenerHijoIzq() const;
    NodoHuffman<T>* obtenerHijoDer() const;
    bool esHoja() const;
};

#include "NodoHuffman.hxx"
#endif
