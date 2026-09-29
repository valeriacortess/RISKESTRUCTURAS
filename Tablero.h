#ifndef TABLERO_H
#define TABLERO_H
#include <string>
#include <vector>
#include "Territorio.h"
#include "Jugador.h"
#include "Continente.h"
#include "Carta.h"
using namespace std;

class Tablero {
    private:

    vector <Territorio> territorios; 
    vector <Jugador> jugadores; 
    vector <Continente> continentes;
    vector<Carta> mazoCartas;
    vector<Carta> descarteCartas;
    int turno_actual; 
    bool inicializado; 
    bool terminado; 
    string ganador;
    int intercambiosRealizados; 

    public: 

    Tablero (); 
    vector<Continente> getContinentes() const; 
    bool inicializarJuego(string archivo);
    bool estaInicializado() const;
    bool juegoFinalizado() const;
    vector <Territorio> getTerritorios()const;
    vector <Jugador> getJugadores () const; 
    Jugador* getJugadorActual ();
    Jugador* getJugadorPorNombre(string nombre);
    Jugador* getJugadorPorColor(string color);
    Territorio* getTerritorioCodigo (string codigo);
    string getGanador()const;
    void avanzarTurno();
    bool esTurnoDe (string nombre_jugador) const;
    void mostrarEstado() const;
    string getEstadoResumen() const ;
    bool validaColores(vector<string> colores_usados) const;
    bool validarUnidadesJugador() const;
    bool usoTerritoriosOcupados() const;
    void declararGanador(string nombreGanador);
    void inicializarMazo();
    bool robarCarta(Carta& cartaSalida);
    void recibirDescarte(const vector<Carta>& cartas);
    int getIntercambiosRealizados() const;
    void incrementarIntercambios();
};

#endif