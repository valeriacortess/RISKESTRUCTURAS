#include <iostream>
#include <queue>
#include "ArbolGeneral.h"

template <class T>
ArbolGeneral<T>::ArbolGeneral() {
  this->raiz = NULL;
}

template <class T>
ArbolGeneral<T>::ArbolGeneral(T val) {
  NodoGeneral <T>* nodo = new NodoGeneral<T>;
  nodo->fijarDato(val);
  this->raiz = nodo;
}

template <class T>
ArbolGeneral<T>::~ArbolGeneral() {
  delete this->raiz;
  this->raiz = NULL;
}

template <class T>
bool ArbolGeneral<T>::esVacio() {
  return this->raiz == NULL;
}

template <class T>
NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
  return this->raiz;
}

template <class T>
void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
  this->raiz = nraiz;
}

template <class T>
bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
  //si el arbol es vacio
  //crear un nuevo nodo, asignar dato, poner ese nodo como una raiz
  if (this->esVacio()) {
    NodoGeneral<T>* nodo = new NodoGeneral<T>;
    nodo->fijarDato(n);
    this->raiz = nodo;
    return true;
  } 

  return this->insertarNodo(this->raiz, padre, n);
}

// Función auxiliar recursiva
template <class T>
bool ArbolGeneral<T>::insertarNodo(NodoGeneral<T>* nodo, T padre, T n) {
  //revisar el nodo donde estoy para ver si coincide con padre
  if (nodo->obtenerDato() == padre) {
    //si es padre , insertar nuevo hijo
    nodo->adicionarDesc(n);
    return true;
  }

  //si no es el padre, revisar cada nodo hijo y llamar a insertar alli 
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
    if (this->insertarNodo(*it, padre, n)) {
      return true;
    }
  }
  return false;
}



template <class T>
bool ArbolGeneral<T>::eliminarNodo(T n) {
  //si el arbol es vacio;
  //retornar
  if (this->esVacio()) {
    return false;
  }

  //si es la raiz la que quiero eliminar
  // hacerle delete a la raiz
  // poner raiz en nulo
  if (this->raiz->obtenerDato() == n) {
    delete this->raiz;
    this->raiz = NULL;
    return true;
  }

  return this->eliminarNodo(this->raiz, n);
}

// Función auxiliar recursiva
template <class T>
bool ArbolGeneral<T>::eliminarNodo(NodoGeneral<T>* nodo, T n) {
  //si alguno de los hijos es el que quiero eliminar 
  if (nodo->eliminarDesc(n)) {
    return true;
  }

  //si ninguno de los hijos es el que quiero eliminar 
  //revisar cada nodo hijo y llamar a eliminar alli
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
    if (this->eliminarNodo(*it, n)) {
      return true;
    }
  }
  return false;
}

template <class T>
bool ArbolGeneral<T>::buscar(T n) {
  //si el arbol no esta vacio
  if (this->esVacio()) {
    return false;
  }
  return this->buscar(this->raiz, n); 
}
  
// Función auxiliar recursiva
template <class T>
bool ArbolGeneral<T>::buscar(NodoGeneral<T>* nodo, T n) {
  //comparto el dato en el nodo actual con dato parametro
  //si es ese retorno que lo encontre 
  if (nodo->obtenerDato() == n) {
    return true;
  }

  //si no, para cada nodo hijo hacer el llamado a buscar 
  typename std::list<NodoGeneral<T>*>::iterator it;
  for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
    if (this->buscar(*it, n)) {
      return true;
    }
  }
  return false;
}

//parte 2 

/*template <class T>
int ArbolGeneral<T>::altura(){
  if (this->esVacio()){
    return -1;
  }else {
    return this->altura(this->raiz);
  }
}

template <class T>
ArbolGeneral<T>::altura(NodoGeneral <T>* nodo){
  int alt = -1;

  if (nodo->EsHoja()){
    alt = 0;
  } else {
    int alth;
    std::list<NodoGeneral<T>*>::iterator it;
    for (it = nodo->desc.begin(); it!= nodo->desc.end(); it++){
      alth = this->altura(*it);
      if(alt < alth+1)
        alt = alth+1;
    }
  }
 
  return alt;
} */

//hay dos formas en los videos no se cual poner 
//parte 3 

/////////////////////////
// Creo que esta porque esta mejor estructurada llamando la funcion que ya esta en nodo
template <class T>
unsigned int ArbolGeneral<T>::altura(){
  if (this->esVacio()){
    return -1;
  }else {
    return this->raiz->altura();
  }
}
//////////////////////////

template <class T>
unsigned int ArbolGeneral<T>::tamano() {
  if (this->esVacio()) {
    return 0;
  }
  return this->raiz->tamano();
}

template <class T>
void ArbolGeneral<T>::preOrden(){
  if(!this->esVacio())
    (this->raiz)->preOrden();
  
}
//////////////////////////////


template <class T>
void ArbolGeneral<T>::posOrden(){
  if(!this->esVacio())
    (this->raiz)->posOrden();
}

template <class T>
void ArbolGeneral<T>::nivelOrden() {
  // NO ES RECURRENTE (O RECURSIVO)
  if (this->esVacio()) {
    return;
  }
  std::queue<NodoGeneral<T>*> cola;
  cola.push(this->raiz);
  while (!cola.empty()) {
    NodoGeneral<T>* actual = cola.front();
    cola.pop();
    std::cout << actual->obtenerDato() << " ";
    typename std::list<NodoGeneral<T>*>::iterator it;
    for (it = actual->desc.begin(); it != actual->desc.end(); it++) {
      cola.push(*it);
    }
  }
}
