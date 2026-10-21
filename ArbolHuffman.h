#ifndef ARBOL_HUFFMAN_H
#define ARBOL_HUFFMAN_H

#include "NodoHuffman.h"
#include <map>
#include <string>
#include <queue>
#include <vector>

template <class T>
class ArbolHuffman {
protected:
    NodoHuffman<T>* raiz;
    std::map<T, std::string> tablaCodigos;   // carácter -> código binario

    // Función auxiliar para generar los códigos recorriendo el árbol
    void generarCodigos(NodoHuffman<T>* nodo, std::string codigoActual);

public:
    ArbolHuffman();
    ~ArbolHuffman();

    // Construye el árbol a partir de un mapa de frecuencias
    void construir(const std::map<T, unsigned long>& frecuencias);

    // Devuelve la tabla de códigos generada
    const std::map<T, std::string>& obtenerTablaCodigos() const;

    // Codifica un texto completo y devuelve la cadena de bits (string de '0' y '1')
    std::string codificar(const std::string& texto) const;

    // Decodifica una cadena de bits y devuelve el texto original
    std::string decodificar(const std::string& bits) const;

    // Acceso a la raíz 
    NodoHuffman<T>* obtenerRaiz() const;
};

#include "ArbolHuffman.hxx"
#endif
