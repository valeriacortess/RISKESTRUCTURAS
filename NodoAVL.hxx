#include "NodoAVL.h"

template <class T>
NodoAVL<T>::NodoAVL(){
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
}

template <class T>
NodoAVL<T>::NodoAVL(T val){
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
  this->dato = val;
}

template <class T>
NodoAVL<T>::~NodoAVL(){
  if (this->hijoIzq != NULL) {
    delete this->hijoIzq;
    this->hijoIzq = NULL;
  }
  if (this->hijoDer != NULL) {
    delete this->hijoDer;
    this->hijoDer = NULL;
  }
}

template <class T>
T NodoAVL<T>::obtenerDato(){
  return this->dato;
}

template<class T>
void NodoAVL<T>::fijarDato(T val){
  this->dato= val;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::obtenerHijoIzq(){
  return this->hijoIzq;
}

template <class T>
NodoAVL<T>* NodoAVL<T>::obtenerHijoDer(){
  return this->hijoDer;
}

template <class T>
void NodoAVL<T>::fijarHijoIzq(NodoAVL<T>* izq){
  this->hijoIzq = izq;
}

template <class T>
void NodoAVL<T>::fijarHijoDer(NodoAVL<T>* der){
  this->hijoDer = der;
}

template <class T>
bool NodoAVL<T>::esHoja(){
  return this->hijoIzq == NULL && this->hijoDer == NULL;
}

template <class T>
int NodoAVL<T>::altura (){
  int valt= -1;

  if (this->esHoja()){
    valt =0;
  }else {
    int valt_izq = -1;
    int valt_der = -1;
    if (this->hijoIzq != NULL) 
      valt_izq = (this->hijoIzq)->altura();
    if (this->hijoDer != NULL) 
      valt_der = (this->hijoDer)->altura();
    if (valt_izq > valt_der)
      valt = valt_izq + 1;
    else
      valt = valt_der + 1;
  }
  return valt;
}
template <class T>
int NodoAVL<T> ::factorBalance(){
 int alturaIzq =-1;
 int alturaDer = -1;
  if(this->hijoIzq != NULL){
    alturaIzq = (this->hijoIzq)->altura(); 
  }
  if(this->hijoDer != NULL){
    alturaDer = (this->hijoDer)->altura();
  }
  return alturaIzq - alturaDer;
  
}
template <class T>
 NodoAVL<T>* NodoAVL<T>::rotarDer(){
   NodoAVL<T>* n_padre = this->hijoIzq;
   this->hijoIzq = n_padre->hijoDer;
   n_padre->hijoDer = this;
   return n_padre;
  
}

template <class T>
 NodoAVL<T>* NodoAVL<T>::rotarIzq(){
   NodoAVL<T>* n_padre = this->hijoDer;
   this->hijoDer = n_padre->hijoIzq;
   n_padre->hijoIzq = this;
   return n_padre;
  
}

template <class T>
 NodoAVL<T>* NodoAVL<T>::rotarIzqDer(){
  NodoAVL<T>* aux = (this->hijoIzq)->rotarIzq();
  this->hijoIzq = aux;
   NodoAVL<T>* n_padre = this->rotarDer();
   return n_padre;
  
}
template <class T>
NodoAVL<T>* NodoAVL<T>::rotarDerIzq(){
  NodoAVL<T>* aux = (this->hijoDer)->rotarDer();
  this->hijoDer = aux;
  NodoAVL<T>* n_padre = this->rotarIzq();
  return n_padre;
  
}

template <class T>
void NodoAVL<T>::inOrden(){
  if(this->hijoIzq != NULL)
   (this->hijoIzq)->inOrden();
  std::cout << this->dato << " ";
  if(this->hijoDer != NULL)
   (this->hijoDer)->inOrden();
}

//Tamaño 
template <class T>
int NodoAVL<T>::tamano(){
  int tam = 1;                       // cuenta este nodo
  if (this->hijoIzq != NULL)
    tam += (this->hijoIzq)->tamano();
  if (this->hijoDer != NULL)
    tam += (this->hijoDer)->tamano();
  return tam;
}

//PREORDEN
template <class T>
void NodoAVL<T>::preOrden(){
  std::cout << this->dato << " ";        
  if (this->hijoIzq != NULL)
    (this->hijoIzq)->preOrden();
  if (this->hijoDer != NULL)
    (this->hijoDer)->preOrden();
}

//POSORDEN
template <class T>
void NodoAVL<T>::posOrden(){
  if (this->hijoIzq != NULL)
    (this->hijoIzq)->posOrden();
  if (this->hijoDer != NULL)
    (this->hijoDer)->posOrden();
  std::cout << this->dato << " ";       
}
