#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "Mano.h"
#include "Carta.h"
#include "Territorio.h"
using namespace std;

class Jugador {
    private : 
    string nombre; 
    string color; 
    int unidadInicial;
    int unidadDisponible;
    vector <string> territorios; 
    bool turno_realizado; 
    bool ataque_realizado;
    Mano mano ; 
    bool eliminado;

    public: 

    Jugador ();
    Jugador (string nombre, string color, int unidades);
    
    string getNombre() const;
    string getColor () const;
    Mano& getMano();
    int getUnidadesDisponibles() const;
    vector<string> getTerritorios() const;
    bool obtenerUnidades () const;
    bool atacado() const; 
    void setUnidadesDisponibles (int unidades); 
    void agregarTerritorioConquista (string territorio);
    void eliminarTerritorioConquista(string territorio);
    bool dominaTerritorio (string territorio) const;
    int contarTerritorio () const;
    void unidadesObtenidasMarcado ();
    void ataqueRealizadoMarcado ();
    void reiniciarEstadoTurno (); 
    void sumaUnidades (int cantidad); 
    void restaUnidades(int cantidad);
    void asignarUnidadesTerritorio (Territorio& territorio ,int  cantidad);
    void agregarCarta(Carta carta );
    vector <Carta> getCarta() const;
    void eliminarCarta (vector <Carta> cartas_para_eliminar);
    bool estaEliminado() const;   
    void marcarEliminado();      
};

#endif