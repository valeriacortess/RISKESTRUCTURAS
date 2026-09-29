#ifndef TERRITORIO_H
#define TERRITORIO_H
#include <string>
#include <vector>
using namespace std;

class Territorio {
    private: 

    string codigo;
    string nombre;
    string continente;
    string colorOcupado;
    int unidades;
    vector<string> vecinos;

    public: 

    Territorio (string codigo, string nombre, string continente, string colorOcupado, int unidades);
    Territorio();
    string getCodigo() const;
    string getNombre() const;
    string getContinente()const;
    string getColorOcupado()const;
    int getUnidades() const;
    vector<string> getVecinos() const; 
    void setColorOcupado( string color);
    void setUnidades(int cantidad);
    void sumarUnidades(int cantidad);
    bool restarUnidades(int cantidad);
    void agregarVecino(string codigoVecino ) ;
    bool esVecino(string codigoTerritorio) const; 
    bool estaVacio()const;
};

#endif 
