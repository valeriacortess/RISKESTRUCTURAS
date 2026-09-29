#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include "Comandos.h"
#include "Tablero.h"
#include "Turno.h"
using namespace std;

Tablero tablero;
Turno turno(&tablero);

vector<string> tokenizar(const string& linea){
    vector<string> tokens;

    istringstream iss(linea);
    string token;

    while (iss >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
} 

bool inicializar (string archivo_inicial){
    cout << "\n--------------------------------------------------" << endl;
    bool resultado = tablero.inicializarJuego(archivo_inicial);
    cout << "--------------------------------------------------\n" << endl;
    return resultado;
}

void obtener_unidades (string nombre_jugador){
    cout << "\n--------------------------------------------------" << endl;
    if(!tablero.estaInicializado()){
        cout << "esta partida no esta inicializada correctamente" << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    if(tablero.juegoFinalizado()){
        cout << "esta partida ya tuvo ganador" << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    Jugador* jugador = tablero.getJugadorPorNombre(nombre_jugador);

    if(jugador == nullptr){
        cout << "El jugador " << nombre_jugador << " no forma parte de esta partida" << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    if(!tablero.esTurnoDe(nombre_jugador)){
        cout << "No es el turno del jugador " << nombre_jugador << endl; 
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    //revisa por meido de la funcion de obtener_unidades si el jugador ya obtuvo unidaddes
    if (jugador->obtenerUnidades()){
        cout << "El jugador " << nombre_jugador << " ya reclamo y ubico sus unidades en este turno." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    if(!turno.iniciarTurno(nombre_jugador)){
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    Mano& mano = jugador->getMano();
    if (mano.puedeCanjear()) {
        cout << "\nTienes suficientes cartas para realizar un canje de unidades." << endl;
        cout << "¿Deseas canjear 3 cartas en este momento? (si/no): ";
        string resp;
        getline(cin, resp);

        if (resp == "si") {
            cout << "\nTus cartas actuales:" << endl;
            vector<Carta> cMano = mano.getCartas();
            
            int idx = 0;
            vector<Carta>::const_iterator itCarta;
            for (itCarta = cMano.begin(); itCarta != cMano.end(); itCarta++) {
                cout << "  [" << idx << "] Territorio: " << itCarta->getTerritorio()
                     << " | Tropa: " << itCarta->getTipoEjercito() << endl;
                idx++;
            }

            cout << "\nIngresa los 3 indices de las cartas a canjear separados por espacio (ej: 0 1 2): ";
            string bufInd;
            getline(cin, bufInd);
            stringstream ss(bufInd);
            
            vector<int> indicesSeleccionados;
            int indiceLeido;
            while (ss >> indiceLeido) {
                indicesSeleccionados.push_back(indiceLeido);
            }

            if (indicesSeleccionados.size() == 3) {
                turno.ejecutarCanjeCartas(indicesSeleccionados);
            } else {
                cout << "Seleccion invalida. Debe ingresar exactamente 3 indices." << endl;
            }
        }
    }

    int unidadesTerritorios = turno.calcularUnidadesTerritorio(jugador);

    int unidadesContinentes = turno.calculaUnidadesContinentes(jugador);

    int unidadesCartas= turno.calcularUnidadesCartas(jugador->getMano());

    int totalUnidades = unidadesTerritorios+unidadesContinentes+unidadesCartas;

    jugador->sumaUnidades(totalUnidades);

    cout << "OBTENCION DE UNIDADES" << endl;
    cout << "jugador: " << nombre_jugador << endl;
    cout << "Unidades por territorio: " << unidadesTerritorios <<endl;
    cout << "Unidades por continenetes: " << unidadesContinentes << endl;
    cout << "Unidaddes por cartas: " << unidadesCartas << endl;
    cout << "Unidades totales: " << jugador->getUnidadesDisponibles() << endl; 

    //esto que se hace aca ed para poner las undiades obtenidas en algun territorio
    while(jugador->getUnidadesDisponibles()>0){

        cout << "Unidades restantes: " << jugador->getUnidadesDisponibles() << endl;
        cout << "Territorios controlados " ;

        vector<string> territorios = jugador->getTerritorios();
        vector<string>::iterator it16;

        for(it16= territorios.begin() ; it16!= territorios.end(); it16++){
            Territorio* territorio = tablero.getTerritorioCodigo(*it16);

            if(territorio!= nullptr){
                cout << territorio->getCodigo() << " - " << territorio->getNombre() << "-" << territorio->getUnidades() << endl;
            }
        }

        string territorioCod;
        int cant;

        string buffer;

        cout << "ingrese el codigo del territorio: ";
        getline(cin, territorioCod);

        Territorio* territorio = tablero.getTerritorioCodigo(territorioCod);

        if (territorio == nullptr){
            cout << "El territorio no existe" << endl;
            continue;
        }
        if(!jugador->dominaTerritorio(territorioCod)){
            cout << "el jugador " << nombre_jugador << " no controla el territorio" << endl;
            continue;
        }

        cout << "ingrese la cantidad de unidades: ";
        getline(cin, buffer);
        stringstream(buffer) >> cant;

        if (cant <= 0){
            cout << "ingrese una cantidad mayor a 0: " << endl;
            continue;
        }

        if (cant > jugador->getUnidadesDisponibles()){
            cout << "no puede ubicar mas unidades de las disponibles" << endl;
            continue;
        }

        jugador->asignarUnidadesTerritorio(*territorio, cant);
        jugador->restaUnidades(cant);

        cout << "se ubicaron " << cant << " unidades en" << territorio->getNombre() << endl;
    }
    //mostramos que ya se obtenieron las unidades 

    jugador->unidadesObtenidasMarcado();

    //pasamos al siguiente estado de turno
    turno.ejecutarObtenerUnidades();

    cout << nombre_jugador << " ha terminado de reclamar y ubicar sus unidades" << endl; 
    cout << "--------------------------------------------------\n" << endl;
}

void atacar(string nombre_jugador){
    cout << "\n--------------------------------------------------" << endl;
    if(!tablero.estaInicializado()){
        cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(tablero.juegoFinalizado()){
        cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    Jugador* jugador = tablero.getJugadorPorNombre(nombre_jugador);
    if(jugador == nullptr){
        cout << "(Jugador no válido) El jugador " << nombre_jugador << " no forma parte de esta partida." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(!tablero.esTurnoDe(nombre_jugador)){
        cout << "(Jugador fuera de turno) No es el turno del jugador " << nombre_jugador << "." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(!jugador->obtenerUnidades()){
        cout << "(Jugador no ha ubicado unidades) El jugador " << nombre_jugador << " no ha ejecutado el comando obtener_unidades." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    bool seguirAtacando = true;
    while (seguirAtacando) {
        string origen, destino;
        int numeroDado;

        string buffer;

        cout << "Territorio de origen: ";
        getline(cin, origen);

        cout << "Territorio a atacar: ";
        getline(cin, destino);

        cout << "Cantidad de dados a lanzar (1-3): ";
        getline(cin, buffer);
        stringstream(buffer) >> numeroDado;

        ResultadoAtaque resultado = turno.ejecutarAtaque(origen, destino, numeroDado);
        
        switch (resultado) {
        case ATAQUE_EXITO:
            break;
        case ATAQUE_FUERA_DE_FASE:
            cout << "No es momento de atacar en este turno." << endl;
            break;
        case ATAQUE_TERRITORIO_ORIGEN_INVALIDO:
            cout << "El territorio de origen no existe." << endl;
            break;
        case ATAQUE_TERRITORIO_DESTINO_INVALIDO:
            cout << "El territorio destino no existe." << endl;
            break;
        case ATAQUE_ORIGEN_NO_ES_TUYO:
            cout << "El territorio de origen no te pertenece." << endl;
            break;
        case ATAQUE_DESTINO_ES_TUYO:
            cout << "No puedes atacar un territorio que ya es tuyo." << endl;
            break;
        case ATAQUE_ORIGEN_SIN_UNIDADES_SUFICIENTES:
            cout << "El territorio de origen no tiene suficientes unidades para atacar." << endl;
            break;
        case ATAQUE_NO_SON_VECINOS:
            cout << "Los territorios no son vecinos." << endl;
            break;
        case ATAQUE_DADOS_INVALIDOS:
            cout << "La cantidad de dados debe estar entre 1 y 3." << endl;
            break;
        }

        if (tablero.juegoFinalizado()) {
            break;
        }

        cout << "¿Desea seguir atacando? (si/no): ";
        string respuesta;
        getline(cin, respuesta);
        seguirAtacando = (respuesta == "si");
    }

    turno.robarCartaTurno();

    turno.finalizarAtaque();

    cout << "(Comando correcto) El jugador " << nombre_jugador << " ha terminado de atacar." << endl;
    cout << "--------------------------------------------------\n" << endl;
}

void fortificar(string nombre_jugador){
    cout << "\n--------------------------------------------------" << endl;
    if(!tablero.estaInicializado()){
        cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(tablero.juegoFinalizado()){
        cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    Jugador* jugador = tablero.getJugadorPorNombre(nombre_jugador);
    if(jugador == nullptr){
        cout << "(Jugador no válido) El jugador " << nombre_jugador << " no forma parte de esta partida." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(!tablero.esTurnoDe(nombre_jugador)){
        cout << "(Jugador fuera de turno) No es el turno del jugador " << nombre_jugador << "." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(!jugador->atacado()){
        cout << "(Jugador no ha atacado) El jugador " << nombre_jugador << " no ha ejecutado el comando atacar." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    string origen, destino;
    int unidades;

    string buffer;

        cout << "Territorio origen: ";
        getline(cin, origen);

        cout << "Territorio destino: ";
        getline(cin, destino);

        cout << "Unidades a mover: ";
        getline(cin, buffer);
        stringstream(buffer) >> unidades;

    bool exito = turno.ejecutarFortificar(origen, destino, unidades);

    if (!exito) {
        cout << "No se pudo fortificar, revise los datos ingresados." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }

    cout << "(Comando correcto) El jugador " << nombre_jugador << " ha terminado de fortificar su posición." << endl;
    cout << "--------------------------------------------------\n" << endl;
}

void estado_juego(){
    cout << "\n--------------------------------------------------" << endl;
    if(!tablero.estaInicializado()){
        cout << "(Juego no inicializado) Esta partida no ha sido inicializada correctamente." << endl;
        cout << "--------------------------------------------------\n" << endl;
        return;
    }
    if(tablero.juegoFinalizado()){
        cout << "(Juego terminado) Esta partida ya tuvo un ganador." << endl;
    }
    tablero.mostrarEstado();
    cout << "--------------------------------------------------\n" << endl;
}

void guardar (string nombre_archivo){
    cout << endl;
    cout << "comandos aun no implementados !" << endl;
    cout << endl;
    cout << "Esta partida no ha sido inicializada correctamente." << endl;
    cout << "La partida ha sido guardada correctamente." << endl;
    cout << "La partida no ha sido guardada correctamente." << endl;
}

void guardar_comprimido (string nombre_archivo){
    cout << endl;
    cout << "comandos aun no implementados !" << endl;
    cout << endl;
    cout << "Esta partida no ha sido inicializada correctamente." << endl;
    cout << "La partida ha sido codificada y guardada correctamente." << endl;
    cout << "La partida no ha sido codificada ni guardada correctamente." << endl;
}

void costo_conquista (string nombre_jugador, string territorio){
    cout << endl;
    cout << "comandos aun no implementados !" << endl;
    cout << endl;
    cout << "Esta partida no ha sido inicializada correctamente." << endl;
    cout << "Esta partida ya tuvo un ganador." << endl;
    cout << "Para conquistar el territorio territorio , nombre_jugador debe atacar" << endl;
    cout << "desde territorio_1 , pasando por los territorios territorio_2 , territorio_3 , ...," << endl;
    cout << "territorio_m . Debe conquistar n unidades de ejército." << endl;
}

void conquista_mas_barata (string nombre_jugador){
    cout << endl;
    cout << "comandos aun no implementados !" << endl;
    cout << endl;
    cout << "Esta partida no ha sido inicializada correctamente." << endl;
    cout << "Esta partida ya tuvo un ganador." << endl;
    cout << "La conquista más barata es avanzar sobre el territorio territorio_1" << endl;
    cout << "desde el territorio territorio_2 . Para conquistar el territorio territorio_1 , debe" << endl;
    cout << "atacar desde territorio_2 , pasando por los territorios territorio_3 , territorio_4 ," << endl;
    cout << "..., territorio_m . Debe conquistar n unidades de ejército." << endl;
}

void ayuda (){

    cout << "Comandos disponibles:" << endl << endl;

    cout << "  inicializar <archivo_inicio>" << endl;
    cout << "  obtener_unidades <nombre_jugador>" << endl;
    cout << "  atacar <nombre_jugador>" << endl;
    cout << "  fortificar <nombre_jugador>" << endl;
    cout << "  estado_juego" << endl;
    cout << "  guardar <nombre_archivo>" << endl;
    cout << "  guardar_comprimido <nombre_archivo>" << endl;
    cout << "  costo_conquista <nombre_jugador> <territorio>" << endl;
    cout << "  conquista_mas_barata <nombre_jugador>" << endl;
    cout << "  salir" << endl;
    cout << "  ayuda [comando]" << endl;
}

void ayuda (string comando){
    if (comando == "inicializar") {
        cout << "Uso: inicializar <archivo_inicio>" << endl;
        cout << "Descripcion : Carga una partida desde un archivo para empezar a jugar" << endl;
    } 
    else if (comando == "obtener_unidades") {
        cout << "Uso: obtener_unidades <nombre_jugador>" << endl;
        cout << "Descripcion : Calcula cuantas unidades nuevas te corresponden en el turno y permite colocarla en tu territorio" << endl;
    } 
    else if (comando == "atacar") {
        cout << "Uso: atacar <nombre_jugador>" << endl;
        cout << "Descripcion: Permite atacar un territorio enemido desde uno de tus territorios vecinos" << endl;
        cout << "Se lanzan los dados y se actualizan las unidades hasta que decidas parar o conquiste el territorio " << endl;
    } 
    else if (comando == "fortificar") {
        cout << "Uso: fortificar <nombre_jugador>" << endl;
        cout << "Descripcion: Al final de tu turno puedes mover unidades de un territorio tuyo a otro que sea tuyo y este de vecino" << endl;
    } 
    else if (comando == "estado_juego") {
        cout << "Uso: estado_juego" << endl;
        cout << "Descripcion: Muestra el estado actual de la partida como : " << endl;
        cout << " Jugadores, a quien le toca y como estan ocupados los territorios " << endl;
    } 
    else if (comando == "guardar") {
        cout << "Uso: guardar <nombre_archivo>" << endl;
        cout << "Descripcion: Guarda la partida actual en un archivo para continuar despues" << endl;
    } 
    else if (comando == "guardar_comprimido") {
        cout << "Uso: guardar_comprimido <nombre_archivo>" << endl;
        cout << "Descripcion: Guarda la partida actual en archivo comprimido ocupando menos espacio " << endl;
    } 
    else if (comando == "costo_conquista") {
        cout << "Uso: costo_conquista <nombre_jugador> <territorio>" << endl;
        cout << "Descripcion: Te indica desde donde conviene atacar y cuantas unidades necesitas para conquistar un territorio" << endl;
    } 
    else if (comando == "conquista_mas_barata") {
        cout << "Uso: conquista_mas_barata <nombre_jugador>" << endl;
        cout << "Descripcion: Te suguiere cual es la conquista mas facil en ese momento" << endl;
    } 
    else if (comando == "salir") {
        cout << "Uso: salir" << endl;
        cout << "Descripcion: Cierra el programa y termina la partida " << endl;
    } 
    else if (comando == "ayuda") {
        cout << "Uso: ayuda [comando]" << endl;
        cout << "Descripcion: Muestra  la lista de comandos disponibles y su funcionamiento" << endl;
    } 
    else {
        cout << "este comando no existe" <<endl;
    }
}

void salir (){
    cout << "saliendo..." << endl;
}