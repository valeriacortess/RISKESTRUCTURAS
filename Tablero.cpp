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
        datos.push_back({"Alaska", "Alaska", "America del Norte", {"TerritorioNoroccidental", "Alberta", "Kamchatka"}});
        datos.push_back({"Alberta", "Alberta", "America del Norte", {"Alaska", "TerritorioNoroccidental", "Ontario", "EstadosUnidosOccidentales"}});
        datos.push_back({"AmericaCentral", "America Central", "America del Norte", {"EstadosUnidosOccidentales", "EstadosUnidosOrientales", "Venezuela"}});
        datos.push_back({"EstadosUnidosOrientales", "Estados Unidos Orientales", "America del Norte", {"Ontario", "Quebec", "EstadosUnidosOccidentales", "AmericaCentral"}});
        datos.push_back({"Groenlandia", "Groenlandia", "America del Norte", {"TerritorioNoroccidental", "Ontario", "Quebec", "Islandia"}});
        datos.push_back({"TerritorioNoroccidental", "Territorio Noroccidental", "America del Norte", {"Alaska", "Alberta", "Ontario", "Groenlandia"}});
        datos.push_back({"Ontario", "Ontario", "America del Norte", {"Alberta", "TerritorioNoroccidental", "Groenlandia", "Quebec", "EstadosUnidosOrientales", "EstadosUnidosOccidentales"}});
        datos.push_back({"Quebec", "Quebec", "America del Norte", {"Ontario", "Groenlandia", "EstadosUnidosOrientales"}});
        datos.push_back({"EstadosUnidosOccidentales", "Estados Unidos Occidentales", "America del Norte", {"Alberta", "Ontario", "EstadosUnidosOrientales", "AmericaCentral"}});

        // America del Sur
        datos.push_back({"Argentina", "Argentina", "America del Sur", {"Peru", "Brasil"}});
        datos.push_back({"Brasil", "Brasil", "America del Sur", {"Venezuela", "Peru", "Argentina", "AfricaDelNorte"}});
        datos.push_back({"Peru", "Peru", "America del Sur", {"Venezuela", "Brasil", "Argentina"}});
        datos.push_back({"Venezuela", "Venezuela", "America del Sur", {"AmericaCentral", "Brasil", "Peru"}});

        // Europa
        datos.push_back({"GranBretana", "Gran Bretana", "Europa", {"Islandia", "Escandinavia", "EuropaDelNorte", "EuropaOccidental"}});
        datos.push_back({"Islandia", "Islandia", "Europa", {"Groenlandia", "GranBretana", "Escandinavia"}});
        datos.push_back({"EuropaDelNorte", "Europa del Norte", "Europa", {"GranBretana", "Escandinavia", "Ucrania", "EuropaDelSur", "EuropaOccidental"}});
        datos.push_back({"Escandinavia", "Escandinavia", "Europa", {"Islandia", "GranBretana", "EuropaDelNorte", "Ucrania"}});
        datos.push_back({"EuropaDelSur", "Europa del Sur", "Europa", {"EuropaOccidental", "EuropaDelNorte", "Ucrania", "MedioOriente", "Egipto", "AfricaDelNorte"}});
        datos.push_back({"Ucrania", "Ucrania", "Europa", {"Escandinavia", "EuropaDelNorte", "EuropaDelSur", "Ural", "Afganistan", "MedioOriente"}});
        datos.push_back({"EuropaOccidental", "Europa Occidental", "Europa", {"GranBretana", "EuropaDelNorte", "EuropaDelSur", "AfricaDelNorte"}});

        // Africa
        datos.push_back({"Congo", "Congo", "Africa", {"AfricaDelNorte", "AfricaOriental", "AfricaDelSur"}});
        datos.push_back({"AfricaOriental", "Africa Oriental", "Africa", {"Egipto", "AfricaDelNorte", "Congo", "AfricaDelSur", "Madagascar", "MedioOriente"}});
        datos.push_back({"Egipto", "Egipto", "Africa", {"EuropaDelSur", "AfricaDelNorte", "AfricaOriental", "MedioOriente"}});
        datos.push_back({"Madagascar", "Madagascar", "Africa", {"AfricaOriental", "AfricaDelSur"}});
        datos.push_back({"AfricaDelNorte", "Africa del Norte", "Africa", {"Brasil", "EuropaOccidental", "EuropaDelSur", "Egipto", "AfricaOriental", "Congo"}});
        datos.push_back({"AfricaDelSur", "Africa del Sur", "Africa", {"Congo", "AfricaOriental", "Madagascar"}});

        // Asia
        datos.push_back({"Afganistan", "Afganistan", "Asia", {"Ucrania", "MedioOriente", "India", "China", "Ural"}});
        datos.push_back({"China", "China", "Asia", {"Afganistan", "Ural", "Siberia", "Mongolia", "Siam", "India"}});
        datos.push_back({"India", "India", "Asia", {"Afganistan", "MedioOriente", "China", "Siam"}});
        datos.push_back({"Irkutsk", "Irkutsk", "Asia", {"Siberia", "Yakutsk", "Kamchatka", "Mongolia"}});
        datos.push_back({"Japon", "Japon", "Asia", {"Kamchatka", "Mongolia"}});
        datos.push_back({"Kamchatka", "Kamchatka", "Asia", {"Yakutsk", "Irkutsk", "Mongolia", "Japon", "Alaska"}});
        datos.push_back({"MedioOriente", "Medio Oriente", "Asia", {"Ucrania", "EuropaDelSur", "Egipto", "AfricaOriental", "India", "Afganistan"}});
        datos.push_back({"Mongolia", "Mongolia", "Asia", {"Siberia", "Irkutsk", "Kamchatka", "Japon", "China"}});
        datos.push_back({"Siam", "Siam", "Asia", {"India", "China", "Indonesia"}});
        datos.push_back({"Siberia", "Siberia", "Asia", {"Ural", "China", "Mongolia", "Irkutsk", "Yakutsk"}});
        datos.push_back({"Ural", "Ural", "Asia", {"Ucrania", "Afganistan", "China", "Siberia"}});
        datos.push_back({"Yakutsk", "Yakutsk", "Asia", {"Siberia", "Irkutsk", "Kamchatka"}});

        // Australia
        datos.push_back({"AustraliaOriental", "Australia Oriental", "Australia", {"NuevaGuinea", "AustraliaOccidental"}});
        datos.push_back({"Indonesia", "Indonesia", "Australia", {"Siam", "NuevaGuinea", "AustraliaOccidental"}});
        datos.push_back({"NuevaGuinea", "Nueva Guinea", "Australia", {"Indonesia", "AustraliaOriental", "AustraliaOccidental"}});
        datos.push_back({"AustraliaOccidental", "Australia Occidental", "Australia", {"Indonesia", "NuevaGuinea", "AustraliaOriental"}});

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

bool Tablero::inicializarJuego(string archivo) {

    
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
        Jugador* dueño = getJugadorPorColor((*itTerritorio).getColorOcupado());
        if (dueño != nullptr) {
            (*dueño).agregarTerritorioConquista((*itTerritorio).getCodigo());
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


vector<string> coloresUsados;
vector<string>::iterator itC;
for (itTerritorio = territorios.begin(); itTerritorio != territorios.end(); itTerritorio++) {
    string color = (*itTerritorio).getColorOcupado();
    bool yaEsta = false;
    for (itC = coloresUsados.begin(); itC != coloresUsados.end(); itC++) {
        if (*itC == color) { 
            yaEsta = true; 
            break; 
        }
    }
    if (!yaEsta) {
        coloresUsados.push_back(color);
    }
}

    bool coloresValidos = validaColores(coloresUsados);
    bool unidadesValidas = validarUnidadesJugador();
    bool territoriosOcupados = usoTerritoriosOcupados();

    if (!coloresValidos || !unidadesValidas || !territoriosOcupados) {
        
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
bool Tablero::validaColores(vector<string> colores_usados) const{
    vector<string>::iterator it14;

    for (it14 = colores_usados.begin(); it14 != colores_usados.end(); it14++){
        bool encontrado = false;

        vector<Jugador>::const_iterator it15;

        for (it15= jugadores.begin(); it15 != jugadores.end(); it15++){
            if (it15->getColor() == *it14){
                encontrado = true ;
                break;
            }
        }

        if (!encontrado){
            return false;
        }
    }
    return true;
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
    mazoCartas.push_back(Carta("Alaska", "Infanteria"));
    mazoCartas.push_back(Carta("Alberta", "Caballeria"));
    mazoCartas.push_back(Carta("AmericaCentral", "Artilleria"));
    mazoCartas.push_back(Carta("EstadosUnidosOrientales", "Infanteria"));
    mazoCartas.push_back(Carta("Groenlandia", "Caballeria"));
    mazoCartas.push_back(Carta("TerritorioNoroccidental", "Artilleria"));
    mazoCartas.push_back(Carta("Ontario", "Infanteria"));
    mazoCartas.push_back(Carta("Quebec", "Caballeria"));
    mazoCartas.push_back(Carta("EstadosUnidosOccidentales", "Artilleria"));

    mazoCartas.push_back(Carta("Argentina", "Infanteria"));
    mazoCartas.push_back(Carta("Brasil", "Caballeria"));
    mazoCartas.push_back(Carta("Peru", "Artilleria"));
    mazoCartas.push_back(Carta("Venezuela", "Infanteria"));

    mazoCartas.push_back(Carta("GranBretana", "Caballeria"));
    mazoCartas.push_back(Carta("Islandia", "Artilleria"));
    mazoCartas.push_back(Carta("EuropaDelNorte", "Infanteria"));
    mazoCartas.push_back(Carta("Escandinavia", "Caballeria"));
    mazoCartas.push_back(Carta("EuropaDelSur", "Artilleria"));
    mazoCartas.push_back(Carta("Ucrania", "Infanteria"));
    mazoCartas.push_back(Carta("EuropaOccidental", "Caballeria"));

    mazoCartas.push_back(Carta("Congo", "Artilleria"));
    mazoCartas.push_back(Carta("AfricaOriental", "Infanteria"));
    mazoCartas.push_back(Carta("Egipto", "Caballeria"));
    mazoCartas.push_back(Carta("Madagascar", "Artilleria"));
    mazoCartas.push_back(Carta("AfricaDelNorte", "Infanteria"));
    mazoCartas.push_back(Carta("AfricaDelSur", "Caballeria"));

    mazoCartas.push_back(Carta("Afganistan", "Artilleria"));
    mazoCartas.push_back(Carta("China", "Infanteria"));
    mazoCartas.push_back(Carta("India", "Caballeria"));
    mazoCartas.push_back(Carta("Irkutsk", "Artilleria"));
    mazoCartas.push_back(Carta("Japon", "Infanteria"));
    mazoCartas.push_back(Carta("Kamchatka", "Caballeria"));
    mazoCartas.push_back(Carta("MedioOriente", "Artilleria"));
    mazoCartas.push_back(Carta("Mongolia", "Infanteria"));
    mazoCartas.push_back(Carta("Siam", "Caballeria"));
    mazoCartas.push_back(Carta("Siberia", "Artilleria"));
    mazoCartas.push_back(Carta("Ural", "Infanteria"));
    mazoCartas.push_back(Carta("Yakutsk", "Caballeria"));

    mazoCartas.push_back(Carta("AustraliaOriental", "Artilleria"));
    mazoCartas.push_back(Carta("Indonesia", "Infanteria"));
    mazoCartas.push_back(Carta("NuevaGuinea", "Caballeria"));
    mazoCartas.push_back(Carta("AustraliaOccidental", "Artilleria"));

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
