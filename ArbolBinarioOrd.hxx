#include <iostream>
#include <queue>
#include "ArbolBinarioOrd.h"

template<class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd() {
  this->raiz = NULL;
}

template <class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

template <class T>
bool ArbolBinarioOrd<T>::esVacio() {
  return this->raiz == NULL;
}

template <class T>
T ArbolBinarioOrd<T>::datoRaiz() {
  return (this->raiz)->obtenerDato();
}

// Recurente
/*template <class T>
int ArbolBinarioOrd::altura() {
  if (this->esVacio()) {
    return -1;
  } else {
    return this->altura(this->raiz);
  }
}

template <class T>
int ArbolBinarioOrd::altura(NodoBinario<T>* nodo){
  int valt;

  if ( nodo->EsHoja()){
    valt = 0;
  } else {
    int valt_izq = -1;
    int valt_der = -1;
    if (nodo->obtenerHijoIzq() != NULL) 
      valt_izq = this->altura(nodo->obtenerHijoIzq());
    if (nodo->obtenerHijoDer() != NULL) 
      valt_der = this->altura(nodo->obtenerHijoDer());
    if (valt_izq > valt_der)
      valt = valt_izq + 1;
    else
      valt = valt_der + 1;
  }
 
  return valt;
} */

// Forma 2 - llama a funcin en NodoBinario
template <class T>
int ArbolBinarioOrd<T>::altura(){
  if (this->esVacio()){
    return -1;
  }else {
    return (this->raiz)->altura();
  }
}

// recurrente
template <class T>
int ArbolBinarioOrd<T>::tamano() {
  if (this->esVacio())
    return 0;
  return (this->raiz)->tamano();
}

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::insertar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  NodoBinario<T>* padre = this->raiz;

  bool insertado = false;
  bool duplicado = false;

  while (nodo != NULL) {
    padre = nodo;
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      duplicado = true;
      break;
    }
  }

  if (!duplicado) {
    NodoBinario<T>* nuevo = new NodoBinario<T>(val);
    if (nuevo != NULL) {
      if (padre == NULL)
        this->raiz = nuevo;
      else if (val < padre->obtenerDato())
        padre->fijarHijoIzq(nuevo);
      else
        padre->fijarHijoDer(nuevo);
    }
    insertado = true;
  }

  return insertado;
}

// iterativa

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::eliminar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  NodoBinario<T>* padre = NULL;

  // 1. buscar el nodo y guardar su padre
  while (nodo != NULL && nodo->obtenerDato() != val) {
    padre = nodo;
    if (val < nodo->obtenerDato())
      nodo = nodo->obtenerHijoIzq();
    else
      nodo = nodo->obtenerHijoDer();
  }

  if (nodo == NULL)
    return false;  // no esta en el arbol

  // 2. dos hijos: copiar el maximo del subarbol izquierdo en el nodo
  //    y pasar a eliminar ese maximo (que tiene a lo sumo un hijo)
  if (nodo->obtenerHijoIzq() != NULL && nodo->obtenerHijoDer() != NULL) {
    NodoBinario<T>* padreMax = nodo;
    NodoBinario<T>* max = nodo->obtenerHijoIzq();
    while (max->obtenerHijoDer() != NULL) {
      padreMax = max;
      max = max->obtenerHijoDer();
    }
    nodo->fijarDato(max->obtenerDato());
    nodo = max;
    padre = padreMax;
  }

  // 3. hoja o un solo hijo: el hijo (o NULL) ocupa su lugar
  NodoBinario<T>* hijo = nodo->obtenerHijoIzq();
  if (hijo == NULL)
    hijo = nodo->obtenerHijoDer();

  if (padre == NULL)
    this->raiz = hijo;
  else if (padre->obtenerHijoIzq() == nodo)
    padre->fijarHijoIzq(hijo);
  else
    padre->fijarHijoDer(hijo);

  // desconectar antes de borrar para que el destructor no borre al hijo
  nodo->fijarHijoIzq(NULL);
  nodo->fijarHijoDer(NULL);
  delete nodo;

  return true;
}

// iterativa
template <class T>
bool ArbolBinarioOrd<T>::buscar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  bool encontrado = false;

  while (nodo != NULL && !encontrado) {
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      encontrado = true;
    }
  }
  
  return encontrado;
}

// Recurrente
template <class T>
void ArbolBinarioOrd<T>::preOrden(){
  if (!this->esVacio())
    (this->raiz)->preOrden();
}

// Recurrente
// Forma 1
/*template <class T>
void ArbolBinarioOrd::inOrden(){
  if (!this->esVacio())
    this->inOrden(this->raiz);
}

template <class T>
void ArbolBinarioOrd::inOrden(NodoBinario<T>* nodo){
  if (nodo != NULL) {
  this->inOrden(nodo->obtenerHijoIzq());
  std::cout << nodo->obtenerDato() << " ";
  this->inOrden(nodo->obtenerHijoDer());
  }
}*/


// Forma 2 - Llama a función en NodoBinario
template <class T>
void ArbolBinarioOrd<T>::inOrden(){
  if (!this->esVacio())
    (this->raiz)->inOrden();
}

// Recurrente
template <class T>
void ArbolBinarioOrd<T>::posOrden(){
  if (!this->esVacio())
    (this->raiz)->posOrden();
}



// iterativa
template <class T>
void ArbolBinarioOrd<T>::nivelOrden(){
  if (!this->esVacio()) {
    std::queue<NodoBinario<T>*> cola;
    cola.push(this->raiz);
    NodoBinario<T>* nodo;
    while (!cola.empty()) {
      nodo = cola.front();
      cola.pop();
      std::cout << nodo->obtenerDato() << " ";
      if (nodo->obtenerHijoIzq() != NULL)
        cola.push(nodo->obtenerHijoIzq());
      if (nodo->obtenerHijoDer() != NULL)
        cola.push(nodo->obtenerHijoDer());
    }
  }
}

