#ifndef __NODOBINARIO_H__
#define __NODOBINARIO_H__
#include <list>
#include <iostream>

template< class T >
class NodoBinario {
    protected:
        T dato;
        NodoBinario<T>* hijoIzq;
        NodoBinario<T>* hijoDer;
    public:
        NodoBinario();
        NodoBinario(T val);
        ~NodoBinario();
        T obtenerDato();
        void fijarDato(T val);
        NodoBinario<T>* obtenerHijoIzq();
        NodoBinario<T>* obtenerHijoDer();
        void fijarHijoIzq(NodoBinario<T>* hijo);
        void fijarHijoDer(NodoBinario<T>* hijo);
        bool esHoja();
        int altura();
        void inOrden();
        int tamano();
        void preOrden();
        void posOrden();
};
#include "NodoBinario.hxx"

#endif