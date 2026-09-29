#ifndef TURNO_H
#define TURNO_H
#include <string>
#include <vector>
#include "Tablero.h"
#include "Jugador.h"
#include "Mano.h"
using namespace std;

enum ResultadoAtaque {
    ATAQUE_EXITO,
    ATAQUE_FUERA_DE_FASE,      
    ATAQUE_TERRITORIO_ORIGEN_INVALIDO,
    ATAQUE_TERRITORIO_DESTINO_INVALIDO,
    ATAQUE_ORIGEN_NO_ES_TUYO,
    ATAQUE_DESTINO_ES_TUYO,
    ATAQUE_ORIGEN_SIN_UNIDADES_SUFICIENTES,
    ATAQUE_NO_SON_VECINOS,
    ATAQUE_DADOS_INVALIDOS
};

class Turno {
    private:
        int estadoActual;
        Jugador* jugadorActual;
        Tablero *tablero;
        bool conquistoTerritorio;

    public: 

        Turno(Tablero* tablero);
        bool iniciarTurno(string nombreJugador);
        bool ejecutarObtenerUnidades();
        ResultadoAtaque ejecutarAtaque(string codigoAtacante, string codigoAtacado, int numeroDado);
        bool finalizarAtaque();
        bool ejecutarFortificar(string codigoAtacante, string codigoAtacado, int unidades);
        bool puedeObtenerUnidades() const;
        bool puedeAtacar() const;
        bool puedeFortificar()const;
        string getEstadoActual()const;
        int calcularUnidadesTerritorio(Jugador* jugador)const;
        int calculaUnidadesContinentes (Jugador* jugador)const;
        int calcularUnidadesCartas(const Mano& mano) const;
        bool ejecutarCanjeCartas(const vector<int>& indicesCartas);
        bool robarCartaTurno();


};

#endif
