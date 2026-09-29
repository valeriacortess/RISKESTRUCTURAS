#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador() : nombre(""), color(""), unidadInicial(0), unidadDisponible(0), turno_realizado(false), ataque_realizado(false), eliminado(false) {};
Jugador::Jugador(string nombre, string color, int unidades): nombre(nombre), color(color), unidadInicial(unidades), unidadDisponible(0), turno_realizado(false), ataque_realizado(false), eliminado(false) {};


bool Jugador::estaEliminado() const { return eliminado; }
void Jugador::marcarEliminado() { eliminado = true; }
string Jugador :: getNombre() const{ return nombre;}
string Jugador :: getColor () const {return color;};
Mano& Jugador ::getMano(){
    return mano; 
};
int Jugador :: getUnidadesDisponibles() const {return unidadDisponible;};
vector<string> Jugador ::getTerritorios() const {return territorios; };

bool Jugador:: obtenerUnidades() const {return turno_realizado;}
bool Jugador ::atacado() const {return ataque_realizado;};

void Jugador ::setUnidadesDisponibles (int unidades){
    unidadDisponible = unidades; 
}; 
void Jugador ::agregarTerritorioConquista (string territorio){
    territorios.push_back(territorio);
};
void Jugador ::eliminarTerritorioConquista(string territorio){
    vector<string>::const_iterator it3;
    for (it3 = territorios.begin(); it3 != territorios.end(); it3++){
        if (*it3 == territorio){
            territorios.erase(it3);
            return;
        }
    }
};
bool Jugador ::dominaTerritorio (string territorio) const{
    vector<string>::const_iterator it4;
    for (it4 = territorios.begin(); it4 != territorios.end(); it4++){
        if(territorio == *it4){
            cout << "el jugador si domina el territorio" << endl;
            return true;
        }
    }

    cout << "el jugador no domina el territorio" << endl;
    return false;
};
int Jugador ::contarTerritorio () const{
    return territorios.size();
} ;
void Jugador ::unidadesObtenidasMarcado (){
    if(!turno_realizado){
        turno_realizado = true;
        cout << "ya se ejecuto el comando" << endl; 
    } 
};
void Jugador ::ataqueRealizadoMarcado (){
    if (!ataque_realizado){
        ataque_realizado = true;
        cout << "ya se realizo el ataque " << endl; 
    }
};
void Jugador ::reiniciarEstadoTurno (){
    turno_realizado= false;
    ataque_realizado= false;
}; 
void Jugador ::sumaUnidades (int cantidad){
    unidadDisponible += cantidad;
}; 
void Jugador ::restaUnidades(int cantidad){
    if (cantidad<= unidadDisponible){
        unidadDisponible -= cantidad;
    }
};
void Jugador ::asignarUnidadesTerritorio (Territorio& territorio ,int  cantidad){
    if(territorio.getColorOcupado() == color){
        territorio.sumarUnidades(cantidad);
    }
};
void Jugador ::agregarCarta(Carta carta ){
    mano.agregarCarta(carta);
};
vector <Carta> Jugador ::getCarta() const {
    return mano.getCartas();
};
void  Jugador ::eliminarCarta (vector <Carta> cartas_para_eliminar){
    mano.eliminarCartas(cartas_para_eliminar);
};
