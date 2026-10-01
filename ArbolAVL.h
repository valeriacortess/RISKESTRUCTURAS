#ifndef __ARBOLAVL__
#define __ARBOLAVL__


#include "NodoAVL.h"

template <class T>
class ArbolAVL{
protected:

    NodoAVL<T>* raiz;
    NodoAVL<T>* balancear(NodoAVL<T>* nodo);
    NodoAVL<T>* insertarRecursivo(NodoAVL<T>* nodo, T val, bool& insertado);
    NodoAVL<T>* eliminarRecursivo(NodoAVL<T>* nodo, T val, bool& eliminado);


public:
    ArbolAVL();
    ~ArbolAVL();
    bool esVacio();
    T datoRaiz();
    int altura();
    int tamano();
    bool insertar(T val);
    bool eliminar(T val);
    bool buscar(T val);
    void preOrden();
    void inOrden();
    void posOrden();
    void nivelOrden();

};

#include "ArbolAVL.hxx"

#endif
