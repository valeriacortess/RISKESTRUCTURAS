#include "Tablero.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

Tablero::Tablero() : turno_actual(0), inicializado(false), terminado(false), ganador(""), intercambiosRealizados(0) {}; 
vector<Continente> Tablero::getContinentes() const {return continentes;}
int Tablero::getIntercambiosRealizados() const { return intercambiosRealizados; }
void Tablero::incrementarIntercambios() { intercambiosRealizados++; }

// ---------------------------------------------------------------------------
// Datos fijos del tablero de Risk (42 territorios, 6 continentes y sus
// vecindades). El enunciado especifica que el archivo de inicializacion solo
// trae, por cada territorio, el color del jugador que lo ocupa y las unidades
// ubicadas alli (ver seccion 2.1, comando "inicializar"); la geografia del
// tablero (continente y vecinos de cada territorio) es fija para el juego de
// Risk y por eso se deja embebida aqui, en un namespace anonimo para que solo
// sea visible dentro de este archivo.
// ---------------------------------------------------------------------------
namespace {

    struct DatosTerritorio {
        string codigo;
        string nombre;
        string continente;
        vector<string> vecinos;
    };

    vector<DatosTerritorio> obtenerDatosTablero() { 
        vector<DatosTerritorio> datos;
        // Estructura .push_back: (código, nombre, continente, {vecinos}
        // America del Norte
        datos.push_back({"1.1", "Alaska", "America del Norte", {"1.6", "1.2", "5.6"}});
        datos.push_back({"1.2", "Alberta", "America del Norte", {"1.1", "1.6", "1.7", "1.9"}});
        datos.push_back({"1.3", "America Central", "America del Norte", {"1.9", "1.4", "2.4"}});
        datos.push_back({"1.4", "Estados Unidos Orientales", "America del Norte", {"1.7", "1.8", "1.9", "1.3"}});
        datos.push_back({"1.5", "Groenlandia", "America del Norte", {"1.6", "1.7", "1.8", "3.2"}});
        datos.push_back({"1.6", "Territorio Noroccidental", "America del Norte", {"1.1", "1.2", "1.7", "1.5"}});
        datos.push_back({"1.7", "Ontario", "America del Norte", {"1.2", "1.6", "1.5", "1.8", "1.4", "1.9"}});
        datos.push_back({"1.8", "Quebec", "America del Norte", {"1.7", "1.5", "1.4"}});
        datos.push_back({"1.9", "Estados Unidos Occidentales", "America del Norte", {"1.2", "1.7", "1.4", "1.3"}});

        // America del Sur
        datos.push_back({"2.1", "Argentina", "America del Sur", {"2.3", "2.2"}});
        datos.push_back({"2.2", "Brasil", "America del Sur", {"2.4", "2.3", "2.1", "4.5"}});
        datos.push_back({"2.3", "Peru", "America del Sur", {"2.4", "2.2", "2.1"}});
        datos.push_back({"2.4", "Venezuela", "America del Sur", {"1.3", "2.2", "2.3"}});

        // Europa
        datos.push_back({"3.1", "Gran Bretana", "Europa", {"3.2", "3.4", "3.3", "3.7"}});
        datos.push_back({"3.2", "Islandia", "Europa", {"1.5", "3.1", "3.4"}});
        datos.push_back({"3.3", "Europa del Norte", "Europa", {"3.1", "3.4", "3.6", "3.5", "3.7"}});
        datos.push_back({"3.4", "Escandinavia", "Europa", {"3.2", "3.1", "3.3", "3.6"}});
        datos.push_back({"3.5", "Europa del Sur", "Europa", {"3.7", "3.3", "3.6", "5.7", "4.3", "4.5"}});
        datos.push_back({"3.6", "Ucrania", "Europa", {"3.4", "3.3", "3.5", "5.11", "5.1", "5.7"}});
        datos.push_back({"3.7", "Europa Occidental", "Europa", {"3.1", "3.3", "3.5", "4.5"}});

        // Africa
        datos.push_back({"4.1", "Congo", "Africa", {"4.5", "4.2", "4.6"}});
        datos.push_back({"4.2", "Africa Oriental", "Africa", {"4.3", "4.5", "4.1", "4.6", "4.4", "5.7"}});
        datos.push_back({"4.3", "Egipto", "Africa", {"3.5", "4.5", "4.2", "5.7"}});
        datos.push_back({"4.4", "Madagascar", "Africa", {"4.2", "4.6"}});
        datos.push_back({"4.5", "Africa del Norte", "Africa", {"2.2", "3.7", "3.5", "4.3", "4.2", "4.1"}});
        datos.push_back({"4.6", "Africa del Sur", "Africa", {"4.1", "4.2", "4.4"}});

        // Asia
        datos.push_back({"5.1", "Afganistan", "Asia", {"3.6", "5.7", "5.3", "5.2", "5.11"}});
        datos.push_back({"5.2", "China", "Asia", {"5.1", "5.11", "5.10", "5.8", "5.9", "5.3"}});
        datos.push_back({"5.3", "India", "Asia", {"5.1", "5.7", "5.2", "5.9"}});
        datos.push_back({"5.4", "Irkutsk", "Asia", {"5.10", "5.12", "5.6", "5.8"}});
        datos.push_back({"5.5", "Japon", "Asia", {"5.6", "5.8"}});
        datos.push_back({"5.6", "Kamchatka", "Asia", {"5.12", "5.4", "5.8", "5.5", "1.1"}});
        datos.push_back({"5.7", "Medio Oriente", "Asia", {"3.6", "3.5", "4.3", "4.2", "5.3", "5.1"}});
        datos.push_back({"5.8", "Mongolia", "Asia", {"5.10", "5.4", "5.6", "5.5", "5.2"}});
        datos.push_back({"5.9", "Siam", "Asia", {"5.3", "5.2", "6.2"}});
        datos.push_back({"5.10", "Siberia", "Asia", {"5.11", "5.2", "5.8", "5.4", "5.12"}});
        datos.push_back({"5.11", "Ural", "Asia", {"3.6", "5.1", "5.2", "5.10"}});
        datos.push_back({"5.12", "Yakutsk", "Asia", {"5.10", "5.4", "5.6"}});

        // Australia
        datos.push_back({"6.1", "Australia Oriental", "Australia", {"6.3", "6.4"}});
        datos.push_back({"6.2", "Indonesia", "Australia", {"5.9", "6.3", "6.4"}});
        datos.push_back({"6.3", "Nueva Guinea", "Australia", {"6.2", "6.1", "6.4"}});
        datos.push_back({"6.4", "Australia Occidental", "Australia", {"6.2", "6.3", "6.1"}});

        return datos;
    }

    // Bonificacion de unidades por dominar un continente completo (seccion 1.5).
    int bonificacionContinente(string nombreContinente) {
        if (nombreContinente == "America del Sur") return 2;
        if (nombreContinente == "Australia") return 2;
        if (nombreContinente == "Africa") return 3;
        if (nombreContinente == "America del Norte") return 5;
        if (nombreContinente == "Europa") return 5;
        if (nombreContinente == "Asia") return 7;
        return 0;
    }

} 

bool Tablero::inicializarJuego(const std::string& archivo, bool validarUnidadesIniciales) {

    
    if (inicializado) {
        cout << "El juego ya ha sido inicializado." << endl;
        return false;
    }


    ifstream entrada(archivo.c_str());
    if (!entrada.is_open()) {
        cout << archivo << " no se encuentra o no puede leerse." << endl;
        return false;
    }

    
    if (entrada.peek() == ifstream::traits_type::eof()) {
        cout << archivo << " no contiene información." << endl;
        entrada.close();
        return false;
    }

    
    string linea;
    if (!getline(entrada, linea)) {
        cout << archivo << " no contiene información en el formato esperado." << endl;
        entrada.close();
        return false;
    }

    int cantidadJugadores;
    {
        stringstream linea1(linea);
        string sobra;
        if (!(linea1 >> cantidadJugadores) || (linea1 >> sobra) ||
            cantidadJugadores < 3 || cantidadJugadores > 6) {
            cout << archivo << " no contiene información en el formato esperado." << endl;
            entrada.close();
            return false;
        }
    }

    
    vector<Jugador> jugadoresTemp;
    vector<Jugador> :: iterator itJugador;
    for (int i = 0; i < cantidadJugadores; i++) {
        if (!getline(entrada, linea)) {
            cout << archivo << " no contiene información en el formato esperado." << endl;
            entrada.close();
            return false;
        }

        stringstream linea2(linea);
        string nombreJugador, colorJugador, sobra;
        if (!(linea2 >> nombreJugador >> colorJugador) || (linea2 >> sobra) || nombreJugador.size() > 8) {
            cout << archivo << " no contiene información en el formato esperado." << endl;
            entrada.close();
            return false;
        }

        //verificar que no se repita el nombre o el color.
        for (itJugador = jugadoresTemp.begin(); itJugador != jugadoresTemp.end(); itJugador++){
            if ((*itJugador).getNombre() == nombreJugador || (*itJugador).getColor() == colorJugador) {
                cout << archivo << " no contiene información en el formato esperado." << endl;
                entrada.close();
                return false;
            }
        }

        jugadoresTemp.push_back(Jugador(nombreJugador, colorJugador, 0));
    }

    //Esqueleto fijo de los 42 territorios (continente y vecinos) 
    vector<DatosTerritorio> datosTablero = obtenerDatosTablero();
    vector<Territorio> territoriosTemp;
    vector<DatosTerritorio>::iterator itDatos;
    vector<string>::iterator itVecinos;
    for (itDatos = datosTablero.begin(); itDatos != datosTablero.end(); itDatos++){
        Territorio t(itDatos->codigo, itDatos->nombre, itDatos->continente, "", 0);
        for (itVecinos = itDatos->vecinos.begin(); itVecinos != itDatos->vecinos.end(); itVecinos++){
            t.agregarVecino(*itVecinos);
        }
        territoriosTemp.push_back(t);
    }

    //Lectura de la ocupacion de los 42 territorios 
    vector<bool> territorioLeido(territoriosTemp.size(), false);
    vector<Territorio>::iterator itTerritorio;
    vector<bool>::iterator itLeido;

    for (size_t i = 0; i < territoriosTemp.size(); i++) {
     if (!getline(entrada, linea)) {
        cout << archivo << " no contiene información en el formato esperado." << endl;
        entrada.close();
        return false;
    }

        stringstream linea3(linea);
        string codigoTerritorio, colorOcupa, sobra;
        int unidades;
        if (!(linea3 >> codigoTerritorio >> colorOcupa >> unidades) || (linea3 >> sobra) || unidades < 0) {
            cout << archivo << " no contiene información en el formato esperado." << endl;
            entrada.close();
            return false;
        }

        vector<Territorio>::iterator itTerritorioEncontrado = territoriosTemp.end();
        vector<bool>::iterator itLeidoEncontrado = territorioLeido.end();

        itLeido = territorioLeido.begin();
        for (itTerritorio = territoriosTemp.begin(); itTerritorio != territoriosTemp.end(); itTerritorio++, itLeido++){
            if ((*itTerritorio).getCodigo() == codigoTerritorio){
                itTerritorioEncontrado = itTerritorio;
                itLeidoEncontrado = itLeido;
                break;
            }
        }
        if (itTerritorioEncontrado == territoriosTemp.end()){
            cout << archivo << " no contiene información en el formato esperado." << endl;
            entrada.close();
            return false;
        }
        (*itTerritorioEncontrado).setColorOcupado(colorOcupa);
        (*itTerritorioEncontrado).setUnidades(unidades);
        (*itLeidoEncontrado) = true;
     
    }

    entrada.close();

     //Validacion de que se leyeron todos los territorios
  vector<bool>::iterator itL;
  for (itL = territorioLeido.begin(); itL != territorioLeido.end(); itL++){
      if (!(*itL)){
          cout << archivo << " no contiene información en el formato esperado." << endl;
          return false;
      }
  }

     //se guardan los datos leidos
    territorios = territoriosTemp;
    jugadores = jugadoresTemp;

   // Cada jugador recibe sus territorios conquistados
    for (itTerritorio = territorios.begin(); itTerritorio != territorios.end(); itTerritorio++) {
        Jugador* dueno = getJugadorPorColor((*itTerritorio).getColorOcupado());
        if (dueno != nullptr) {
            (*dueno).agregarTerritorioConquista((*itTerritorio).getCodigo());
        }
    }

    // los continentes se construyen, evita tener que recorrer los territorios cada vez que se necesiten, se dejan construidos una vez inicializado el juego. Se los explico luego si necesitan mas detalles. 
    continentes.clear();
    vector<string> nombresContinentes;
    nombresContinentes.push_back("America del Norte");
    nombresContinentes.push_back("America del Sur");
    nombresContinentes.push_back("Europa");
    nombresContinentes.push_back("Africa");
    nombresContinentes.push_back("Asia");
    nombresContinentes.push_back("Australia");

    vector<string>::iterator itContinente;
    for (itContinente = nombresContinentes.begin(); itContinente != nombresContinentes.end(); itContinente++) {
        Continente continenteNuevo(*itContinente, bonificacionContinente(*itContinente));

        for (itTerritorio = territorios.begin(); itTerritorio != territorios.end(); itTerritorio++) {
            if ((*itTerritorio).getContinente() == *itContinente) {
                continenteNuevo.agregarTerritorio(&(*itTerritorio));
            }
        }

        continentes.push_back(continenteNuevo);
    }


    // Nota: ya no se exige que el color de cada territorio coincida con el de algun jugador.
    bool unidadesValidas = true;
    bool territoriosOcupados = usoTerritoriosOcupados();

    // Solo validar unidades iniciales si se indica (partida nueva)
    if (validarUnidadesIniciales) {
        unidadesValidas = validarUnidadesJugador();
    }

    if (!unidadesValidas || !territoriosOcupados) {
        territorios.clear();
        jugadores.clear();
        continentes.clear();
        cout << archivo << " no contiene información en el formato esperado." << endl;
        return false;
    }
    
    turno_actual = 0;
    inicializado = true;
    terminado = false;
    ganador = "";
    srand((unsigned int) time(nullptr));

    inicializarMazo(); // Inicializa el mazo de cartas al inicio del juego

    cout << "El juego se ha inicializado correctamente." << endl;
    return true;
}

bool Tablero::estaInicializado() const{
    return inicializado;
}
bool Tablero::juegoFinalizado() const{
    return terminado;
}

vector <Territorio> Tablero::getTerritorios()const{
    return territorios; 
};
vector <Jugador>Tablero:: getJugadores () const {
    return jugadores;
}; 
Jugador* Tablero::getJugadorActual (){
    if (jugadores.empty()){
        cout << "no hay jugadores en la partida" << endl;
        return nullptr;
    }
    return &jugadores[turno_actual];
};
Jugador* Tablero::getJugadorPorNombre(string nombre){
    vector<Jugador>::iterator it5;
    for (it5 = jugadores.begin(); it5 != jugadores.end(); it5++){
        if ((*it5).getNombre() == nombre){
            return &(*it5);
        }
    } 
    return nullptr;
};
Jugador* Tablero::getJugadorPorColor(string color){
    vector<Jugador>::iterator itColor;
    for (itColor = jugadores.begin(); itColor != jugadores.end(); itColor++){
        if ((*itColor).getColor() == color){
            return &(*itColor);
        }
    }
    return nullptr;
};
Territorio* Tablero::getTerritorioCodigo (string codigo){
    vector<Territorio>::iterator it6;
    for (it6 = territorios.begin(); it6 != territorios.end(); it6++){
        if ((*it6).getCodigo() == codigo){
            return &(*it6);
        }
    }
    return nullptr;
};
string Tablero::getGanador()const{ return ganador;};
void Tablero::avanzarTurno(){
    if (jugadores.empty()){
        return;
    }
    do {
        turno_actual = (turno_actual + 1) % jugadores.size();
    } while (jugadores[turno_actual].estaEliminado() && !terminado);

    if (!terminado) {
        jugadores[turno_actual].reiniciarEstadoTurno();
    }
};
bool Tablero::esTurnoDe (string nombre_jugador) const{
    if (jugadores.empty()){
        return false;
    }
    return jugadores[turno_actual].getNombre() == nombre_jugador;
};
void Tablero::mostrarEstado() const {
    cout << "Numero de jugadores: " << jugadores.size() << endl;
    cout << "Turno Actual: " << jugadores[turno_actual].getNombre() <<  endl; 

    vector <Jugador> ::const_iterator it7; 
    vector <Territorio>:: const_iterator it8;

    for (it7 = jugadores.begin(); it7!= jugadores.end(); it7++){
        cout << "Jugador: " << (*it7).getNombre() << endl;
        cout << "Color: " << (*it7).getColor() << endl; 
    }

    for (it8 = territorios.begin(); it8!= territorios.end(); it8++){
        cout << "codigo: " << (*it8).getCodigo() << " Nombre: " << (*it8).getNombre() << endl;
        cout << "Ocupado por : " << (*it8).getColorOcupado() << " Unidades: " << (*it8).getUnidades() << endl;
    }
};
string Tablero::getEstadoResumen() const {
    string resumen= "";
    
    resumen += to_string(jugadores.size()) + "\n"; // pega la informacion al final de lo que ya esta

    vector<Jugador>::const_iterator itJugador;
    vector<Territorio> :: const_iterator itTerritorio;
    for(itJugador = jugadores.begin(); itJugador != jugadores.end(); itJugador++){
        resumen+= itJugador->getNombre() + " " + itJugador->getColor() + " " ; 
    }

    for (itTerritorio = territorios.begin(); itTerritorio != territorios.end(); itTerritorio++){
        resumen += itTerritorio->getCodigo() + " " + itTerritorio->getColorOcupado() + " " + to_string(itTerritorio->getUnidades());
    }

    return resumen;
};
bool Tablero::validarUnidadesJugador() const{
    int unidadEsperada;

    // se revisa la cantidad de jugadores que hay y se verifica que tengan la cantidad correcta de unidades
    switch(jugadores.size()){

        case 3: 
            unidadEsperada = 35;
            break;
        
        case 4: 
            unidadEsperada =30;
            break;
        
        case 5: 
            unidadEsperada = 25;
            break;
        
        case 6: 
            unidadEsperada = 20; 
            break;
        
        default: 
            return false;

    }

    vector<Jugador> ::const_iterator it11;
    vector<Territorio>:: const_iterator it12;

    for(it11 = jugadores.begin(); it11!= jugadores.end(); it11++){
        int suma =0;
        for (it12= territorios.begin(); it12 != territorios.end(); it12++){
            if (it12->getColorOcupado() == it11->getColor()){
                suma += it12->getUnidades();
            }
        }
        if (suma != unidadEsperada){
            return false;
        }

    }

    cout << "Todos los colores son validos" << endl;
    return true;
};

bool Tablero::usoTerritoriosOcupados() const{

    vector<Territorio>::const_iterator it13;
    for (it13= territorios.begin(); it13!= territorios.end(); it13++){
        if (it13->getUnidades()==0){
            return false;
        }
        
    }
    return true;
};

void Tablero::declararGanador(string nombreGanador) {
    terminado = true;
    ganador = nombreGanador;
}

void Tablero::inicializarMazo() {
    mazoCartas.clear();
    descarteCartas.clear();

    // Crear las 42 cartas
    mazoCartas.push_back(Carta("1.1", "Infanteria"));
    mazoCartas.push_back(Carta("1.2", "Caballeria"));
    mazoCartas.push_back(Carta("1.3", "Artilleria"));
    mazoCartas.push_back(Carta("1.4", "Infanteria"));
    mazoCartas.push_back(Carta("1.5", "Caballeria"));
    mazoCartas.push_back(Carta("1.6", "Artilleria"));
    mazoCartas.push_back(Carta("1.7", "Infanteria"));
    mazoCartas.push_back(Carta("1.8", "Caballeria"));
    mazoCartas.push_back(Carta("1.9", "Artilleria"));

    mazoCartas.push_back(Carta("2.1", "Infanteria"));
    mazoCartas.push_back(Carta("2.2", "Caballeria"));
    mazoCartas.push_back(Carta("2.3", "Artilleria"));
    mazoCartas.push_back(Carta("2.4", "Infanteria"));

    mazoCartas.push_back(Carta("3.1", "Caballeria"));
    mazoCartas.push_back(Carta("3.2", "Artilleria"));
    mazoCartas.push_back(Carta("3.3", "Infanteria"));
    mazoCartas.push_back(Carta("3.4", "Caballeria"));
    mazoCartas.push_back(Carta("3.5", "Artilleria"));
    mazoCartas.push_back(Carta("3.6", "Infanteria"));
    mazoCartas.push_back(Carta("3.7", "Caballeria"));

    mazoCartas.push_back(Carta("4.1", "Artilleria"));
    mazoCartas.push_back(Carta("4.2", "Infanteria"));
    mazoCartas.push_back(Carta("4.3", "Caballeria"));
    mazoCartas.push_back(Carta("4.4", "Artilleria"));
    mazoCartas.push_back(Carta("4.5", "Infanteria"));
    mazoCartas.push_back(Carta("4.6", "Caballeria"));

    mazoCartas.push_back(Carta("5.1", "Artilleria"));
    mazoCartas.push_back(Carta("5.2", "Infanteria"));
    mazoCartas.push_back(Carta("5.3", "Caballeria"));
    mazoCartas.push_back(Carta("5.4", "Artilleria"));
    mazoCartas.push_back(Carta("5.5", "Infanteria"));
    mazoCartas.push_back(Carta("5.6", "Caballeria"));
    mazoCartas.push_back(Carta("5.7", "Artilleria"));
    mazoCartas.push_back(Carta("5.8", "Infanteria"));
    mazoCartas.push_back(Carta("5.9", "Caballeria"));
    mazoCartas.push_back(Carta("5.10", "Artilleria"));
    mazoCartas.push_back(Carta("5.11", "Infanteria"));
    mazoCartas.push_back(Carta("5.12", "Caballeria"));

    mazoCartas.push_back(Carta("6.1", "Artilleria"));
    mazoCartas.push_back(Carta("6.2", "Infanteria"));
    mazoCartas.push_back(Carta("6.3", "Caballeria"));
    mazoCartas.push_back(Carta("6.4", "Artilleria"));

    // 2 comodines
    mazoCartas.push_back(Carta());
    mazoCartas.push_back(Carta());

    // Barajar
    int totalCartas = mazoCartas.size();
    for (int i = 0; i < totalCartas; i++) {
        int indiceAleatorio = rand() % totalCartas;
        Carta temp = mazoCartas[i];
        mazoCartas[i] = mazoCartas[indiceAleatorio];
        mazoCartas[indiceAleatorio] = temp;
    }
}

bool Tablero::robarCarta(Carta& cartaSalida) {
    if (mazoCartas.empty()) {
        if (descarteCartas.empty()) {
            // No hay cartas en ningun lado: ni en el mazo de robo
            // ni en el descarte. No se puede entregar carta.
            return false;
        }
        mazoCartas = descarteCartas;
        descarteCartas.clear();

        int totalCartas = mazoCartas.size();
        for (int i = 0; i < totalCartas; i++) {
            int indiceAleatorio = rand() % totalCartas;
            Carta temp = mazoCartas[i];
            mazoCartas[i] = mazoCartas[indiceAleatorio];
            mazoCartas[indiceAleatorio] = temp;
        }
    }

    cartaSalida = mazoCartas.back();
    mazoCartas.pop_back();
    return true;
}

void Tablero::recibirDescarte(const vector<Carta>& cartas) {
    vector<Carta>::const_iterator itDescarte;
    for (itDescarte = cartas.begin(); itDescarte != cartas.end(); itDescarte++) {
        descarteCartas.push_back(*itDescarte);
    }
}
