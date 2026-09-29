#include "NodoBinario.h"

template <class T>
NodoBinario<T>::NodoBinario(){
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
}

template <class T>
NodoBinario<T>::NodoBinario(T val){
  this->hijoIzq = NULL;
  this->hijoDer = NULL;
  this->dato = val;
}

template <class T>
NodoBinario<T>::~NodoBinario(){
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
T NodoBinario<T>::obtenerDato(){
  return this->dato;
}

template<class T>
void NodoBinario<T>::fijarDato(T val){
  this->dato= val;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoIzq(){
  return this->hijoIzq;
}

template <class T>
NodoBinario<T>* NodoBinario<T>::obtenerHijoDer(){
  return this->hijoDer;
}

template <class T>
void NodoBinario<T>::fijarHijoIzq(NodoBinario<T>* izq){
  this->hijoIzq = izq;
}

template <class T>
void NodoBinario<T>::fijarHijoDer(NodoBinario<T>* der){
  this->hijoDer = der;
}

template <class T>
bool NodoBinario<T>::esHoja(){
  return this->hijoIzq == NULL && this->hijoDer == NULL;
}

template <class T>
int NodoBinario<T>::altura (){
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
void NodoBinario<T>::inOrden(){
  if(this->hijoIzq != NULL)
   (this->hijoIzq)->inOrden();
  std::cout << this->dato << " ";
  if(this->hijoDer != NULL)
   (this->hijoDer)->inOrden();
}

//Tamaño 
template <class T>
int NodoBinario<T>::tamano(){
  int tam = 1;                       // cuenta este nodo
  if (this->hijoIzq != NULL)
    tam += (this->hijoIzq)->tamano();
  if (this->hijoDer != NULL)
    tam += (this->hijoDer)->tamano();
  return tam;
}

//PREORDEN
template <class T>
void NodoBinario<T>::preOrden(){
  std::cout << this->dato << " ";        
  if (this->hijoIzq != NULL)
    (this->hijoIzq)->preOrden();
  if (this->hijoDer != NULL)
    (this->hijoDer)->preOrden();
}

//POSORDEN
template <class T>
void NodoBinario<T>::posOrden(){
  if (this->hijoIzq != NULL)
    (this->hijoIzq)->posOrden();
  if (this->hijoDer != NULL)
    (this->hijoDer)->posOrden();
  std::cout << this->dato << " ";       
}
