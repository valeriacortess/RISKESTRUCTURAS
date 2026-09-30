#ifndef __NODOAVL__
#define __NODOAVL__
#include <list>
#include <iostream>

template< class T >
class NodoAVL{
    protected:
        T dato;
    NodoAVL<T>* hijoIzq;
    NodoAVL<T>* hijoDer;
    public:
        NodoAVL();
        NodoAVL(T val);
        ~NodoAVL();
        T obtenerDato();
        void fijarDato(T val);
        NodoAVL<T>* obtenerHijoIzq();
        NodoAVL<T>* obtenerHijoDer();
        void fijarHijoIzq(NodoAVL<T>* hijo);
        void fijarHijoDer(NodoAVL<T>* hijo);
        bool esHoja();
        int altura();
        int factorBalance();
        NodoAVL<T>* rotarDer();
        NodoAVL<T>* rotarIzq();
        NodoAVL<T>* rotarIzqDer();
        NodoAVL<T>* rotarDerIsq();
        void inOrden();
        int tamano();
        void preOrden();
        void posOrden();
};
#include "NodoAVL.hxx"

#endif