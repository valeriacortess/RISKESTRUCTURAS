#include "NodoGeneral.h"

template <class T>
NodoGeneral<T>::NodoGeneral(){
  this->desc.clear();
}

template <class T>
NodoGeneral<T>::~NodoGeneral(){
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = this->desc.begin(); it !=this->desc.end(); it++)
    delete *it;
  this->desc.clear();
}

template <class T>
T& NodoGeneral<T>::obtenerDato(){
  return this->dato;
}

template<class T>
void NodoGeneral<T>::fijarDato(T& val){
  this->dato= val;
}

template <class T>
void NodoGeneral<T>::limpiarLista(){
  this->desc.clear();
}

template< class T >
void NodoGeneral<T>::adicionarDesc(T& nval) {
    NodoGeneral<T> *nodo = new NodoGeneral<T>;
    nodo->fijarDato(nval);
    this->desc.push_back(nodo);
}

template< class T >
bool NodoGeneral<T>::eliminarDesc(T& val){
  //buscar el nodo con el valor dado
  typename std::list<NodoGeneral <T>*>::iterator it;
  NodoGeneral<T> * aux;
  bool eliminado = false;

  for (it = this->desc.begin(); it != this->desc.end(); it++){
    aux = *it;
    if (aux->obtenerDato() == val)
      break;
  }
  //si lo encontramos eliminarlo
  if (it != this->desc.end()){
    delete *it;
    this->desc.erase(it);
    eliminado = true;
  }
  return eliminado;
}

template< class T >
bool NodoGeneral<T>::esHoja(){
  return this->desc.size() == 0;
}

template< class T >
int NodoGeneral<T>::altura (){
  int alt= -1;

  if (this->esHoja()){
    alt =0;
  }else {
    int alth;
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = this->desc.begin(); it != this->desc.end(); it++){
      alth = (*it)->altura();
      if(alt < alth+1)
        alt = alth+1;
    }
  }
  return alt;
}



template <class T>
void NodoGeneral<T>::preOrden(){
  std:: cout << this->dato << " ";
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = this->desc.begin(); it != this->desc.end(); it++){
    (*it)->preOrden();
  }
}

template <class T>
void NodoGeneral<T>::posOrden(){
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = this->desc.begin(); it != this->desc.end(); it++){
    (*it)->posOrden();
  }
  std::cout << this->dato << " ";
}

template <class T>
unsigned int NodoGeneral<T>::tamano(){
  unsigned int tamanoActual = 0;
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = this->desc.begin(); it != this->desc.end(); it++){
    tamanoActual += (*it)->tamano();
  }
  return tamanoActual + 1;
}
