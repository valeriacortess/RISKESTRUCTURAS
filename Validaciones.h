#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>
#include <vector>   //necesario para recibir el vector de tokens
using namespace std;

bool esNombreJugadorValido(string nombre_jugador);
bool esNombreArchivoValido(string nombre_archivo);
bool esTerritorioValido(string territorio);

// Recibe directamente el vector de tokens que devuelve tokenizar()
// tokens[0] se interpreta como el comando, y el resto (tokens.size()-1)
// como la cantidad de parametros recibidos.
bool esCantidadParametrosValida(const vector<string>& tokens);
string aMinusculas(string texto);
bool esArchivoTxt(string nombre_archivo);
#endif