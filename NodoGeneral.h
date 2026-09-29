#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__
#include <list>

template <class T> class ArbolGeneral;

template< class T >
class NodoGeneral {
        friend class ArbolGeneral<T>;
    protected:
        T dato;
        std::list< NodoGeneral<T>* > desc;
    public:
        NodoGeneral();
        ~NodoGeneral();
        T& obtenerDato();
        void fijarDato(T& val);
        void limpiarLista();
        void adicionarDesc(T& nval);
        bool eliminarDesc(T& val);
        bool esHoja();
        int altura();
        void preOrden();
        void posOrden();
        unsigned int tamano();
};
#include "NodoGeneral.hxx"

#endif