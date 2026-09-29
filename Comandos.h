#ifndef COMANDOS_H
#define COMANDOS_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> tokenizar(const string& linea);
bool inicializar (string archivo_inicial);
void obtener_unidades (string nombre_jugador);
void atacar (string nombre_jugador);
void fortificar(string nombre_jugador);
void estado_juego ();
void guardar (string nombre_archivo);
void guardar_comprimido (string nombre_archivo);
void costo_conquista (string nombre_jugador, string territorio);
void conquista_mas_barata (string nombre_jugador);
void ayuda ();
void ayuda (string comando);
void salir ();

#endif 