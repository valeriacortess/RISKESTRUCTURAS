#ifndef __ARBOLGENERAL_H__
#define __ARBOLGENERAL_H__

#include "NodoGeneral.h"

template <class T>
class ArbolGeneral {
protected:
    NodoGeneral<T>* raiz;
public:
    ArbolGeneral();
    ArbolGeneral(T val);
    ~ArbolGeneral();
    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);
    bool insertarNodo(T padre, T n);
    bool eliminarNodo(T n);
    bool buscar(T n);
    unsigned int altura();
    unsigned int tamano();
    void preOrden();
    void posOrden();
    void nivelOrden();

private:
    // Funciones auxiliares recursivas
    bool insertarNodo(NodoGeneral<T>* nodo, T padre, T n);
    bool eliminarNodo(NodoGeneral<T>* nodo, T n);
    bool buscar(NodoGeneral<T>* nodo, T n);
};

#endif