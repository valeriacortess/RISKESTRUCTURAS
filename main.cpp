#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "Comandos.h"
#include "Validaciones.h"
using namespace std;

int main()
{
    cout << "==================================================" << endl;
    cout << "               BIENVENIDO A RISK                  " << endl;
    cout << "==================================================" << endl;
    cout << endl;
    cout << "Risk es un juego de conquista de territorios por turnos." << endl;
    cout << "El objetivo es controlar todos los territorios del tablero," << endl;
    cout << "eliminando a los demas jugadores en el proceso." << endl;
    cout << endl;
    cout << "En cada turno, un jugador puede:" << endl;
    cout << "  1. Obtener y ubicar nuevas unidades de ejercito." << endl;
    cout << "  2. Atacar territorios vecinos para intentar conquistarlos." << endl;
    cout << "  3. Fortificar su posicion moviendo unidades entre territorios propios." << endl;
    cout << endl;
    cout << "Para comenzar, inicializa una partida con:" << endl;
    cout << "  inicializar <archivo_inicio>" << endl;
    cout << endl;
    cout << "Escribe 'ayuda' para ver todos los comandos disponibles," << endl;
    cout << "o 'ayuda <comando>' para ver el uso de uno especifico." << endl;
    cout << endl;
    cout << "==================================================" << endl;
    cout << endl;

    bool continuar = true;
    bool juegoInicializado = false;
    string linea;

    while (continuar){
        cout << "$ ";
        getline (cin, linea);

        vector<string> tokens = tokenizar(linea);

        if (tokens.empty()){
            continue;
        }

        tokens[0] = aMinusculas(tokens[0]);
        string comando = tokens[0];

        if(comando == "inicializar"){
            if (juegoInicializado) {
                cout << "El juego ya ha sido inicializado" << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreArchivoValido(tokens[1])) {
                cout << "Error: el nombre de archivo no tiene un formato valido" << endl;
            }
            else if (!esArchivoTxt(tokens[1])) {
                cout << "Error: el archivo debe tener extension .txt" << endl;
            }
            else {
                bool exito = inicializar(tokens[1]);
                if (exito) {
                    juegoInicializado = true;
                }
            }
        }

        else if(comando == "obtener_unidades"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreJugadorValido(tokens[1])) {
                cout << "Error: el nombre de jugador no tiene un formato valido" << endl;
            }
            else { 
                obtener_unidades(tokens[1]);
            }
        }

        else if(comando == "atacar"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreJugadorValido(tokens[1])) {
                cout << "Error: el nombre de jugador no tiene un formato valido" << endl;
            }
            else { 
                atacar(tokens[1]);
            }
        }

        else if(comando == "fortificar"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreJugadorValido(tokens[1])) {
                cout << "Error: el nombre de jugador no tiene un formato valido" << endl;
            }
            else { 
                fortificar(tokens[1]);
            }
        }

        else if(comando == "estado_juego"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else { 
                estado_juego();
            }
        }

        else if(comando == "guardar"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreArchivoValido(tokens[1])) {
                cout << "Error: el nombre de archivo no tiene un formato valido" << endl;
            }
            else if (!esArchivoTxt(tokens[1])) {
                cout << "Error: el archivo debe tener extension .txt" << endl;
            }
            else { 
                guardar(tokens[1]);
            }
        }

        else if(comando == "guardar_comprimido"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreArchivoValido(tokens[1])) {
                cout << "Error: el nombre de archivo no tiene un formato valido" << endl;
            }
            else { 
                guardar_comprimido(tokens[1]);
            }
        }

        else if(comando == "costo_conquista"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreJugadorValido(tokens[1])) {
                cout << "Error: el nombre de jugador no tiene un formato valido" << endl;
            }
            else if (!esTerritorioValido(tokens[2])) {
                cout << "Error: el territorio no tiene un formato valido" << endl;
            }
            else { 
                costo_conquista(tokens[1], tokens[2]);
            }
        }

        else if (comando == "conquista_mas_barata"){
            if (!juegoInicializado) {
                cout << "Error: Esta partida no ha sido inicializada correctamente." << endl;
            }
            else if (!esCantidadParametrosValida(tokens)) {
            }
            else if (!esNombreJugadorValido(tokens[1])) {
                cout << "Error: el nombre de jugador no tiene un formato valido" << endl;
            }
            else {
                conquista_mas_barata(tokens[1]);
            }
        }

        else if (comando == "ayuda"){
            int cantidadParametros = tokens.size() - 1;
            if (cantidadParametros > 1){
                cout << "Error el comando ayuda solo puede recibir un parametro" << endl;
            }
            else if (cantidadParametros == 1){
                ayuda(tokens[1]);
            }
            else {
                ayuda();
            }
        }

        else if (comando == "salir") {
            continuar = false;
            salir();
        }

        else {
            cout << "Este comando no existe" << endl;
        }

    }

    return 0;
};