#include "Turno.h"
#include <iostream>
#include <sstream>
using namespace std;

Turno::Turno(Tablero* tablero): estadoActual(-1), jugadorActual(nullptr), tablero(tablero){};
bool Turno::iniciarTurno(string nombreJugador){
    if(!tablero->estaInicializado()){
        return false;
    }
    if(tablero->juegoFinalizado()){
        return false;
    }

    Jugador* jugador = tablero->getJugadorPorNombre(nombreJugador);
    if (jugador == nullptr){
        return false;
    }

    if (!tablero->esTurnoDe(nombreJugador)){
        return false;
    }

    jugadorActual = jugador;
    jugadorActual->reiniciarEstadoTurno();
    conquistoTerritorio = false;
    estadoActual=0;
    return true;
};

bool Turno::ejecutarObtenerUnidades(){
    if(!puedeObtenerUnidades()){
        return false;
    }
    estadoActual = 1;

    return true;
};

ResultadoAtaque Turno::ejecutarAtaque(string codigoAtacante ,string codigoAtacado, int numeroDado){
    if(!puedeAtacar()){
        return ATAQUE_FUERA_DE_FASE;   // CORRECTO, no se toca
    }

    if(jugadorActual == nullptr){
        return ATAQUE_FUERA_DE_FASE;   
    }

    //busca los territorios 
    Territorio* territorioAtacante = tablero->getTerritorioCodigo(codigoAtacante);
    Territorio* territorioAtacado = tablero->getTerritorioCodigo(codigoAtacado);

    //los territorios existen
    if(territorioAtacante == nullptr){
        return ATAQUE_TERRITORIO_ORIGEN_INVALIDO;   
    }
    if(territorioAtacado == nullptr){
        return ATAQUE_TERRITORIO_DESTINO_INVALIDO;   
    }

    //territorio atacante pertenece al jugador actual 
    if(!jugadorActual->dominaTerritorio(codigoAtacante)){
        return ATAQUE_ORIGEN_NO_ES_TUYO;  
    }

    //el territorio atacante tinee tener mas de 1 unidad que defienda
    if(territorioAtacante->getUnidades()<=1){
        return ATAQUE_ORIGEN_SIN_UNIDADES_SUFICIENTES;   
    }

    //el territorio acatacdo no pertenece al jugador actual
    if(jugadorActual->dominaTerritorio(codigoAtacado)){
        return ATAQUE_DESTINO_ES_TUYO; 
    }

    //territorios vencinos
    if(!territorioAtacante->esVecino(codigoAtacado)){
        return ATAQUE_NO_SON_VECINOS;   
    }

    //el atacante lanza como maximo 3 dados 
    if(numeroDado < 1 || numeroDado > 3){
        return ATAQUE_DADOS_INVALIDOS;   
    }

    //no puede lanzar mas dados de las unidades que tenga
    if (numeroDado > territorioAtacante->getUnidades() -1){
        return ATAQUE_DADOS_INVALIDOS;  
    }

    //el defensor siempre lanzara 2 dados a menos que solo tenga una unidad 
    int dadosDefensor =2;
    if(territorioAtacado->getUnidades()<2){
        dadosDefensor = 1;
    }

    //lanzan los datos del atacante
    vector<int> dadosAtacante;
    for (int i = 0; i < numeroDado; i++){
        dadosAtacante.push_back((rand()%6)+1);
    }

    //lanzan los datos defensor
    vector<int> dadosDef1;
    for (int i =0; i < dadosDefensor; i++){
        dadosDef1.push_back((rand()%6)+1);
    }

    int cantidadAtacante = dadosAtacante.size();
    int cantidadDefensor = dadosDef1.size();

    //realizamos ordenamiento

    for(int i =0; i < cantidadAtacante; i++){
        for(int j = i+1 ; j < cantidadAtacante; j++){
            if(dadosAtacante[j]> dadosAtacante[i]){
                int tmp = dadosAtacante[i];
                dadosAtacante[i]= dadosAtacante[j];
                dadosAtacante[j]= tmp;
            }
        }
    }

    for (int i = 0; i < cantidadDefensor; i++){
        for (int j = i+1; j < cantidadDefensor; j++){
            if (dadosDef1[j]> dadosDef1[i]){
                int tmp = dadosDef1[i];
                dadosDef1[i]= dadosDef1[j];
                dadosDef1[j]= tmp;
            }
        }
    }


    cout << "dado atacante: ";
    for (int i =0; i < cantidadAtacante; i++){
        cout << dadosAtacante[i] << "-" << endl;
    }

    cout << "dado defensor: ";
    for (int i =0; i < cantidadDefensor; i++){
        cout << dadosDef1[i] << "-" << endl;
    }

    int comparaciones = cantidadAtacante;
    if(cantidadDefensor < comparaciones){
        comparaciones = cantidadDefensor;
    }

    for (int i =0; i < comparaciones; i++){
        if(dadosAtacante[i]> dadosDef1[i]){
            territorioAtacado->restarUnidades(1);
            cout << "el defensor perdio una unidad" << endl;
        }
        else {
            territorioAtacante->restarUnidades(1);
            cout<< "el atacante pierde una unidad" << endl;
        }
    }

    if(territorioAtacado->getUnidades()==0){
        conquistoTerritorio = true;

        Jugador* defensor = tablero->getJugadorPorColor(territorioAtacado->getColorOcupado());
        territorioAtacado->setColorOcupado(jugadorActual->getColor());
        jugadorActual->agregarTerritorioConquista(codigoAtacado);
        if (defensor != nullptr) {
            defensor->eliminarTerritorioConquista(codigoAtacado);
        }
        cout << "territorio conquistado: " << territorioAtacado->getNombre() << endl;

        // se piden unidades a mover del territorio atacante hacia el territorio recien conquistado
        int maximoAMover = territorioAtacante->getUnidades() - 1; // debe dejar minimo 1 defendiendo
        int unidadesAMover = 0;
        string buffer;

        cout << "Unidades disponibles para mover a " << territorioAtacado->getNombre()
             << " (entre 1 y " << maximoAMover << "): ";
        bool entradaValida = false;
        while (!entradaValida) {
            if (!getline(cin, buffer)) {
                unidadesAMover = 1;
                break;
            }
            stringstream ss(buffer);
            if ((ss >> unidadesAMover) && unidadesAMover >= 1 && unidadesAMover <= maximoAMover) {
                entradaValida = true;
            } else {
                cout << "Cantidad invalida. Ingrese un valor entre 1 y " << maximoAMover << ": ";
            }
        }

        territorioAtacante->restarUnidades(unidadesAMover);
        territorioAtacado->sumarUnidades(unidadesAMover);

        cout << "Se movieron " << unidadesAMover << " unidades a "
             << territorioAtacado->getNombre() << endl;
    
         
        // revisa si el defensor se quedo sin territorios
        if (defensor != nullptr && defensor->contarTerritorio() == 0) {
            defensor->marcarEliminado();
            cout << "El jugador " << defensor->getNombre() << " ha sido eliminado de la partida." << endl;
        }

        // revisa si el atacante ya controla los 42 territorios
        if (jugadorActual->contarTerritorio() == 42) {
            tablero->declararGanador(jugadorActual->getNombre());
            cout << "(Comando correcto) El jugador " << jugadorActual->getNombre()
                << " ha conquistado todos los territorios y ha ganado la partida." << endl;
        }
    }

    return ATAQUE_EXITO;
  
};

bool Turno::finalizarAtaque(){
    if (estadoActual != 1){
        return false;
    }
    jugadorActual->ataqueRealizadoMarcado();
    estadoActual = 2;
    return true;
};

bool Turno::robarCartaTurno() {
    if (jugadorActual != nullptr && conquistoTerritorio) {
        Carta nuevaCarta;
        bool huboCarta = tablero->robarCarta(nuevaCarta);

        if (huboCarta) {
            jugadorActual->getMano().agregarCarta(nuevaCarta);
            cout << "El jugador " << jugadorActual->getNombre()
                 << " ha recibido una carta por conquistar un territorio." << endl;
        } else {
            cout << "No hay cartas disponibles para entregar en este momento." << endl;
        }

        conquistoTerritorio = false;
        return huboCarta;
    }
    return false;
}

bool Turno::ejecutarFortificar(string codigoAtacante, string codigoAtacado, int unidades){
    if (!puedeFortificar()){
        return false;
    }
    if(jugadorActual == nullptr){
        return false;
    }

    //se buscan los codigos de amos territorios 
    Territorio* territorioOrigen = tablero->getTerritorioCodigo(codigoAtacante);
    Territorio* territorioDestino = tablero->getTerritorioCodigo(codigoAtacado);

    if (territorioOrigen == nullptr || territorioDestino == nullptr){
        return false;
    }

    //el jugador debe teber a su cargo los 2 territorios

    if(!jugadorActual->dominaTerritorio(codigoAtacante)){
        return false;
    }
    if(!jugadorActual->dominaTerritorio(codigoAtacado)){
        return false;
    }


    //los territorios son vecinos 
    if(!territorioOrigen->esVecino(codigoAtacado)){
        return false;
    }

    //cantidad positiva 
    if(unidades<=0){
        return false;
    }

    if(unidades>= territorioOrigen->getUnidades()){
        return false;
    }

    //mover unidades
    territorioOrigen->restarUnidades(unidades);
    territorioDestino->sumarUnidades(unidades);

    robarCartaTurno();

    estadoActual = 3;

    //se reiniciamos las marcas
    jugadorActual->reiniciarEstadoTurno();

    //pasar al siguiente jugador
    tablero->avanzarTurno();

    return true;

};

bool Turno::puedeObtenerUnidades() const{
   if (estadoActual == 0){
    return true;
   }else {
    return false;
   }
};

bool Turno::puedeAtacar() const{
    if (estadoActual == 1){
    return true;
   }else {
    return false;
   }
};

bool Turno::puedeFortificar()const{
    if (estadoActual == 2){
    return true;
   }else {
    return false;
   }
};

string Turno::getEstadoActual()const {
    if (estadoActual == 0){
        return "obtener_unidades";
    }
    else if (estadoActual == 1){
        return "atacar";
    }
    else if (estadoActual == 2){
        return "fortificar";
    }
    else if (estadoActual == 3){
        return "finalizado";
    }
    else {
        return "no se ha inicializado";
    }
};

int Turno::calcularUnidadesTerritorio(Jugador* jugador)const {
    int cantidadTerritorios = jugador->contarTerritorio();
    int unidadGanada = cantidadTerritorios/3; // se divide por 3 pq se cuentan los territorios que actualmente ocupa el jugador, se divide este número entre 3, y el resultado es la cantidad de unidades adicionales que puede reclamar.
    return unidadGanada;
};

int Turno::calculaUnidadesContinentes (Jugador* jugador)const {
    vector<Continente> continentes = tablero->getContinentes();
    string color = jugador->getColor();
    vector<Continente>::iterator it16; 
    int total =0;

    for (it16 = continentes.begin(); it16 != continentes.end(); it16++){
        if (it16->esControladoPor(color)){
            total += it16->getBonificacion();
        }
    }

    return total;
    
};

int Turno::calcularUnidadesCartas(const Mano& mano) const {
    if (!mano.puedeCanjear()) {
        return 0;
    }
    int numeroIntercambio = tablero->getIntercambiosRealizados() + 1;   // consulta el contador global
    return mano.calcularUnidadesCanje(numeroIntercambio);             
}

bool Turno::ejecutarCanjeCartas(const vector<int>& indicesCartas) {
    if (jugadorActual == nullptr || estadoActual != 0) {
        return false;
    }
    if (indicesCartas.size() != 3) {
        return false;
    }

    Mano& mano = jugadorActual->getMano();
    vector<Carta> cartasMano = mano.getCartas();

    vector<int>::const_iterator itIdx;
    for (itIdx = indicesCartas.begin(); itIdx != indicesCartas.end(); itIdx++) {
        if (*itIdx < 0 || *itIdx >= (int)cartasMano.size()) {
            cout << "Índice de carta inválido." << endl;
            return false;
        }
    }

    vector<Carta> seleccionadas;
    seleccionadas.push_back(cartasMano[indicesCartas[0]]);
    seleccionadas.push_back(cartasMano[indicesCartas[1]]);
    seleccionadas.push_back(cartasMano[indicesCartas[2]]);

    if (!Carta::esCombinacionValida(seleccionadas)) {
        cout << "La combinación de cartas seleccionada no es válida para canje." << endl;
        return false;
    }

    // se calcula con el contador GLOBAL del tablero, no uno propio de la mano
    int numeroIntercambio = tablero->getIntercambiosRealizados() + 1;
    int unidadesGanadas = mano.calcularUnidadesCanje(numeroIntercambio);

    mano.eliminarCartas(seleccionadas);
    tablero->recibirDescarte(seleccionadas);
    tablero->incrementarIntercambios();   //avanza el contador global

    jugadorActual->sumaUnidades(unidadesGanadas);

    cout << "Canje realizado con éxito. Has obtenido " << unidadesGanadas << " unidades adicionales." << endl;

    vector<Carta>::iterator itSel;
    for (itSel = seleccionadas.begin(); itSel != seleccionadas.end(); itSel++) {
        if (!itSel->esComodin() && jugadorActual->dominaTerritorio(itSel->getTerritorio())) {
            Territorio* ter = tablero->getTerritorioCodigo(itSel->getTerritorio());
            if (ter != nullptr) {
                ter->sumarUnidades(2);
                cout << "¡Bonificación por territorio! Se sumaron +2 unidades a " 
                     << ter->getNombre() << endl;
            }
        }
    }

    return true;
}
