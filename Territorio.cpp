#include "Territorio.h"
#include <iostream>
using namespace std; 

Territorio::Territorio(std::string codigo, std::string nombre, std::string continente, std::string colorOcupado, int unidades) :
codigo(codigo), nombre(nombre), continente(continente), colorOcupado(colorOcupado), unidades(unidades), vecinos(vector<string>()){}

Territorio::Territorio() : codigo(""), nombre(""), continente(""), colorOcupado(""), unidades(0), vecinos(vector<string>()){
};

string Territorio:: getCodigo() const {return codigo;}

string Territorio:: getNombre() const {return nombre;}

string Territorio:: getContinente()const {return continente;}

string Territorio:: getColorOcupado()const {return colorOcupado;}

int Territorio:: getUnidades() const {return unidades;}

vector<string> Territorio::getVecinos() const {return vecinos;} 

void Territorio::setColorOcupado( string color){
    colorOcupado= color;
};

void Territorio::setUnidades(int cantidad){
    if(cantidad >= 0){
        unidades = cantidad;
    }
};

void Territorio::sumarUnidades(int cantidad){
    if (cantidad >= 1){
        unidades += cantidad;
    }
};

bool Territorio::restarUnidades(int cantidad){
    if (cantidad <=0 || cantidad > unidades){
        return false;
    }
    unidades -= cantidad;

    return true;
};

void Territorio::agregarVecino(string codigoVecino){
    vector<string>::iterator it1; 
    for (it1 = vecinos.begin(); it1 != vecinos.end(); it1++){
        if (*it1 == codigoVecino){
            cout << "este vecino ya se encuentra agregado" << endl;
            return ;  
        }
    }
    vecinos.push_back(codigoVecino);
};

bool Territorio::esVecino(string codigoTerritorio) const {
    vector<string>::const_iterator it2;
    for (it2 = vecinos.begin(); it2 != vecinos.end(); it2++){ 
        if (*it2 == codigoTerritorio) {
            return true;
        }
    }
    return false;
}


bool Territorio::estaVacio()const{
    return unidades == 0;
};