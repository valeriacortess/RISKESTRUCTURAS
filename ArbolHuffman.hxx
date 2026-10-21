#include "ArbolHuffman.h"
#include <functional>

// Comparador para la cola de prioridad (min-heap por frecuencia)
template <class T>
struct CompararNodos {
    bool operator()(NodoHuffman<T>* a, NodoHuffman<T>* b) {
        return a->obtenerFrecuencia() > b->obtenerFrecuencia();
    }
};

template <class T>
ArbolHuffman<T>::ArbolHuffman() {
    this->raiz = NULL;
}

template <class T>
ArbolHuffman<T>::~ArbolHuffman() {
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
}

template <class T>
void ArbolHuffman<T>::construir(const std::map<T, unsigned long>& frecuencias) {
    // Limpiar árbol anterior si existe
    if (this->raiz != NULL) {
        delete this->raiz;
        this->raiz = NULL;
    }
    this->tablaCodigos.clear();

    if (frecuencias.empty()) {
        return;
    }

    // Cola de prioridad (min-heap)
    std::priority_queue<NodoHuffman<T>*, std::vector<NodoHuffman<T>*>, CompararNodos<T> > cola;

    // Crear un nodo hoja por cada carácter y meterlo en la cola
    typename std::map<T, unsigned long>::const_iterator it;
    for (it = frecuencias.begin(); it != frecuencias.end(); ++it) {
        NodoHuffman<T>* nodo = new NodoHuffman<T>(it->first, it->second);
        cola.push(nodo);
    }

    // Caso especial: solo hay un carácter distinto
    if (cola.size() == 1) {
        this->raiz = cola.top();
        this->tablaCodigos[this->raiz->obtenerDato()] = "0";
        return;
    }

    // Algoritmo de Huffman: mientras haya más de un nodo
    while (cola.size() > 1) {
        NodoHuffman<T>* izq = cola.top();
        cola.pop();

        NodoHuffman<T>* der = cola.top();
        cola.pop();

        unsigned long frecCombinada = izq->obtenerFrecuencia() + der->obtenerFrecuencia();
        NodoHuffman<T>* padre = new NodoHuffman<T>(frecCombinada, izq, der);

        cola.push(padre);
    }

    // El último nodo que queda es la raíz
    this->raiz = cola.top();

    // Generar la tabla de códigos
    this->generarCodigos(this->raiz, "");
}

template <class T>
void ArbolHuffman<T>::generarCodigos(NodoHuffman<T>* nodo, std::string codigoActual) {
    if (nodo == NULL) {
        return;
    }

    if (nodo->esHoja()) {
        this->tablaCodigos[nodo->obtenerDato()] = codigoActual;
        return;
    }

    // Izquierda = 0, Derecha = 1
    this->generarCodigos(nodo->obtenerHijoIzq(), codigoActual + "0");
    this->generarCodigos(nodo->obtenerHijoDer(), codigoActual + "1");
}

template <class T>
const std::map<T, std::string>& ArbolHuffman<T>::obtenerTablaCodigos() const {
    return this->tablaCodigos;
}

template <class T>
std::string ArbolHuffman<T>::codificar(const std::string& texto) const {
    std::string resultado = "";
    for (size_t i = 0; i < texto.size(); ++i) {
        T caracter = texto[i];
        typename std::map<T, std::string>::const_iterator it = this->tablaCodigos.find(caracter);
        if (it != this->tablaCodigos.end()) {
            resultado += it->second;
        }
    }
    return resultado;
}

template <class T>
std::string ArbolHuffman<T>::decodificar(const std::string& bits) const {
    std::string resultado = "";
    if (this->raiz == NULL) {
        return resultado;
    }

    NodoHuffman<T>* actual = this->raiz;

    for (size_t i = 0; i < bits.size(); ++i) {
        if (bits[i] == '0') {
            actual = actual->obtenerHijoIzq();
        } else {
            actual = actual->obtenerHijoDer();
        }

        if (actual != NULL && actual->esHoja()) {
            resultado += actual->obtenerDato();
            actual = this->raiz;   // volver a la raíz para el siguiente carácter
        }
    }
    return resultado;
}

template <class T>
NodoHuffman<T>* ArbolHuffman<T>::obtenerRaiz() const {
    return this->raiz;
}
