#include "Validaciones.h"
#include <cctype>
#include <iostream>
#include <fstream>

using namespace std;

bool esNombreJugadorValido(string nombre_jugador) {
    if (nombre_jugador.empty()) {
        return false;
    }
    if (nombre_jugador.length() > 8) {
        return false;
    }
    for (char c : nombre_jugador) {
        if (isspace(c)) {
            return false;
        }
    }
    return true;
}

bool esNombreArchivoValido(string nombre_archivo) {
    if (nombre_archivo.empty()) {
        return false;
    }
    for (char c : nombre_archivo) {
        if (isspace(c)) {
            return false;
        }
    }
    return true;
}

bool esTerritorioValido(string territorio) {
    if (territorio.empty()) {
        return false;
    }
    for (char c : territorio) {
        if (isspace(c)) {
            return false;
        }
    }
    return true;
}

// Tabla interna: cuantos parametros exactos necesita cada comando.
// "ayuda" queda fuera porque acepta 0 O 1, no un numero fijo.
int obtenerCantidadEsperada(string comando) {
    if (comando == "inicializar") return 1;
    if (comando == "obtener_unidades") return 1;
    if (comando == "atacar") return 1;
    if (comando == "fortificar") return 1;
    if (comando == "estado_juego") return 0;
    if (comando == "guardar") return 1;
    if (comando == "guardar_comprimido") return 1;
    if (comando == "costo_conquista") return 2;
    if (comando == "conquista_mas_barata") return 1;
    if (comando == "salir") return 0;
    return -1;
}



// Recibe el vector de tokens completo (el mismo que produce tokenizar()) y extrae de ahi el comando y la cantidad de parametros.
bool esCantidadParametrosValida(const vector<string>& tokens) {
    if (tokens.empty()) {
        cout << "No se recibio ningun comando." << endl;
        return false;
    }

    string comando = tokens[0];
    int cantidadRecibida = tokens.size() - 1; // se resta el propio comando

    int cantidadEsperada = obtenerCantidadEsperada(comando);

    if (cantidadEsperada == -1) {
        cout << "No se pudo determinar la cantidad esperada de parametros para '"
             << comando << "'." << endl;
        return false;
    }

    cout << "Parametros recibidos: " << cantidadRecibida << endl;
    cout << "Parametros esperados: " << cantidadEsperada << endl;

    if (cantidadRecibida == cantidadEsperada) {
        cout << "La cantidad de parametros es correcta." << endl;
        return true;
    } else {
        cout << "Error La cantidad de parametros no coincide." << endl;
        return false;
    }
}

string aMinusculas(string texto) {
    for (char& c : texto) {
        c = tolower(c);
    }
    return texto;
}       

// Verifica que el nombre termine exactamente en ".txt"
bool esArchivoTxt(string nombre_archivo) {
    string extension = ".txt";
    if (nombre_archivo.length() < extension.length()) {
        return false;
    }
    string finalNombre = nombre_archivo.substr(nombre_archivo.length() - extension.length());
    return finalNombre == extension;
}
