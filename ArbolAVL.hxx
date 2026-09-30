#include <iostream>
#include <queue>
#include "ArbolAVL.h"

template<class T>
ArbolAVL<T>::ArbolAVL() {
  this->raiz = NULL;
}

template <class T>
ArbolAVL<T>::~ArbolAVL() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

template <class T>
bool ArbolAVL<T>::esVacio() {
  return this->raiz == NULL;
}

template <class T>
T ArbolAVL<T>::datoRaiz() {
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
int ArbolAVL<T>::altura(){
  if (this->esVacio()){
    return -1;
  }else {
    return (this->raiz)->altura();
  }
}

// recurrente
template <class T>
int ArbolAVL<T>::tamano() {
  if (this->esVacio())
    return 0;
  return (this->raiz)->tamano();
}

/* iterativa 
 template <class T>
bool ArbolAVL<T>::insertar(T val) {
  NodoAVL<T>* nodo = this->raiz;
  NodoAVL<T>* padre = this->raiz;

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
    NodoAVL<T>* nuevo = new NodoAVL<T>(val);
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
} */



/* iterativa
template <class T>
bool ArbolAVL<T>::eliminar(T val) {
  NodoAVL<T>* nodo = this->raiz;
  NodoAVL<T>* padre = NULL;

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
    NodoAVL<T>* padreMax = nodo;
    NodoAVL<T>* max = nodo->obtenerHijoIzq();
    while (max->obtenerHijoDer() != NULL) {
      padreMax = max;
      max = max->obtenerHijoDer();
    }
    nodo->fijarDato(max->obtenerDato());
    nodo = max;
    padre = padreMax;
  }

  // 3. hoja o un solo hijo: el hijo (o NULL) ocupa su lugar
  NodoAVL<T>* hijo = nodo->obtenerHijoIzq();
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
} */

//insertar recursivo
// Función pública que inicia la recursión
template <class T>
bool ArbolAVL<T>::insertar(T val) {
    bool insertado = false;
    this->raiz = insertarRecursivo(this->raiz, val, insertado);
    return insertado;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::insertarRecursivo(NodoAVL<T>* nodo, T val, bool& insertado) {
    //llegamos a un espacio vacío, creamos el nodo
    if (nodo == NULL) {
        insertado = true;
        return new NodoAVL<T>(val);
    }

    // Buscamos dónde insertar
    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(insertarRecursivo(nodo->obtenerHijoIzq(), val, insertado));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(insertarRecursivo(nodo->obtenerHijoDer(), val, insertado));
    } else {
    
        insertado = false; 
        return nodo;
    }
    //balanceamos
    return balancear(nodo);
}

//eliminar recursivo
template <class T>
bool ArbolAVL<T>::eliminar(T val) {
    bool eliminado = false;
    this->raiz = eliminarRecursivo(this->raiz, val, eliminado);
    return eliminado;
}

template <class T>
NodoAVL<T>* ArbolAVL<T>::eliminarRecursivo(NodoAVL<T>* nodo, T val, bool& eliminado) {
    if (nodo == NULL) {
        eliminado = false;
        return NULL;
    }

    if (val < nodo->obtenerDato()) {
        nodo->fijarHijoIzq(eliminarRecursivo(nodo->obtenerHijoIzq(), val, eliminado));
    } else if (val > nodo->obtenerDato()) {
        nodo->fijarHijoDer(eliminarRecursivo(nodo->obtenerHijoDer(), val, eliminado));
    } else {
        eliminado = true;

        if (nodo->obtenerHijoIzq() == NULL) {
            NodoAVL<T>* temp = nodo->obtenerHijoDer();
            nodo->fijarHijoIzq(NULL);
            nodo->fijarHijoDer(NULL);
            delete nodo;
            nodo = temp;
        } else if (nodo->obtenerHijoDer() == NULL) {
            NodoAVL<T>* temp = nodo->obtenerHijoIzq();
            nodo->fijarHijoIzq(NULL);
            nodo->fijarHijoDer(NULL);
            delete nodo;
            nodo = temp;
        } else {
            NodoAVL<T>* temp = nodo->obtenerHijoIzq();
            while (temp->obtenerHijoDer() != NULL) {
                temp = temp->obtenerHijoDer();
            }

            nodo->fijarDato(temp->obtenerDato());

            bool dummy = false;
            nodo->fijarHijoIzq(eliminarRecursivo(nodo->obtenerHijoIzq(), temp->obtenerDato(), dummy));
        }
    }

    if (nodo == NULL) {
        return NULL;
    }
    //balanceamos
    return balancear(nodo);
}

// iterativa
template <class T>
bool ArbolAVL<T>::buscar(T val) {
  NodoAVL<T>* nodo = this->raiz;
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
void ArbolAVL<T>::preOrden(){
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
void ArbolAVL<T>::inOrden(){
  if (!this->esVacio())
    (this->raiz)->inOrden();
}

// Recurrente
template <class T>
void ArbolAVL<T>::posOrden(){
  if (!this->esVacio())
    (this->raiz)->posOrden();
}



// iterativa
template <class T>
void ArbolAVL<T>::nivelOrden(){
  if (!this->esVacio()) {
    std::queue<NodoAVL<T>*> cola;
    cola.push(this->raiz);
    NodoAVL<T>* nodo;
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

template <class T>
NodoAVL<T>* ArbolAVL<T> :: balancear(NodoAVL<T>* nodo){
  if (nodo == NULL){
    return NULL;
  }
  
  int balance = nodo->factorBalance();

  //izquierdo más alto que derecho
  if (balance == 2){
    int difHijo = nodo->obtenerHijoIzq()->factorBalance();
    if(difHijo > 0){
      return nodo->rotarDer();
    } else if (difHijo < 0){
      return nodo->rotarIzqDer();
    }
      
    } 
  //derecho más alto que izquierdo
  if (balance == -2){
    int difHijo = nodo->obtenerHijoDer()->factorBalance();
    if(difHijo < 0){
      return nodo->rotarIzq();
    } else if(difHijo > 0){
      return nodo->rotarDerIzq();
    }
  }
return nodo;
  }
  


