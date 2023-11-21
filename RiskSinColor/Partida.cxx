#include "Carta.h"
#include "Jugador.h"
#include "Partida.h"
#include "Grafo.h"
#include<list>
#include<vector>
#include<string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>

//constructores
//--------------------------------------------------------------------
Partida::Partida(int id, Grafo g){
    this->id = id;
    this->grafo = g;
}

//getters
//--------------------------------------------------------------------
std::vector<Jugador> Partida::get_jugadores() {
    return this->jugadores;
}
std::list<Carta> Partida::get_cartas(){
    return this->cartas;
}
Grafo Partida::get_grafo(){
    return this->grafo;
}

//setters
//--------------------------------------------------------------------
void Partida::set_id(int id){
    this->id = id;
}

//operaciones de inicicialización del juego
//--------------------------------------------------------------------
void Partida::ocupar(int idJugador, int idPais, int unidades){
    this->grafo.ocuparPais(idJugador, idPais, unidades);
}

void Partida::aggJugador(Jugador j){
    (this->jugadores).push_back(j);
}

void Partida::cargarTablero(std::string archivo_cartas){
    std::ifstream inputFile(archivo_cartas);
    std::string line, word, figura, pais, continente;
    int territorio;

    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            std::stringstream str(line);
            getline(str,word,';');
            territorio = stoi(word);
            getline(str,word,';');
            pais = word;
            getline(str,word,';');
            figura = word;
            getline(str,word,';');
            continente = word;
            Carta c (territorio,figura,continente,pais);
            (this->cartas).push_back(c);
            PaisG pais (c.getId(), c.getPais(), c.getContinente());
            this->grafo.addVertex(pais);
        }
    }else{
        std::cout<<"Archivo no leido"<<std::endl;
    }
    inputFile.close();
}

void Partida::cargarConexiones(std::string archivo){
    std::ifstream file (archivo);
    std::string line, word;

    if(file.is_open()){
        while(getline(file,line,'\n')){
            std::stringstream ss(line);
            getline(ss,word,'-');
            int idPais = stoi(word);
            PaisG pais = this->grafo.getPaises()[this->grafo.searchVertice(idPais)];
            while(getline(ss,word,';')){
                int idVecino = stoi(word);
                PaisG vecino = this->grafo.getPaises()[this->grafo.searchVertice(idVecino)];
                this->grafo.addEdge(pais, vecino, 0);
            }
        }
    }else{
        std::cout<<"Archivo de conexiones no leido"<<std::endl;
    }
    file.close();
}

void Partida::inicializarJugadores(){
    int numJ, id = 1, colorN;
    std::string color, alias;
    bool repetido = false;

    do{
        std::cout<<"Ingrese cantidad de jugadores (entre 3 y 6): \n$";
        std::cin>>numJ;
    }while(numJ < 3 || numJ > 6);

    std::cout<<"\nColores disponibles:"<<std::endl;
    std::cout<<"\n1. verde\n2. azul\n3. rojo\n4. amarillo\n5. rosado\n6. morado"<<std::endl;

    for(int i = 0 ; i < numJ ; i++){
        std::cout<<"\nJUGADOR "<<i+1<<std::endl;
        std::cout<<"ALIAS:";
        std::cout<< "\n$";
        std::cin>>alias;
        std::cout<<"Color:\n$";
        do{
            std::cin>>colorN;
            switch (colorN) {
                case 1:
                    color = "verde";
                    break;
                case 2:
                    color = "azul";
                    break;
                case 3:
                    color = "rojo";
                    break;
                case 4:
                    color = "amarillo";
                    break;
                case 5:
                    color = "rosado";
                    break;
                case 6:
                    color = "morado";
                    break;
            }
            repetido = buscarColorRepetido(color);
            if(colorN < 1 || colorN > 6){
                std::cout<<"Color invalido\n$";
            }
            if(repetido){
                std::cout<<"Color repetido\n$";
            }else{
                repetido = false;
            }
        }while(colorN < 1 || colorN > 6 || repetido);
        Jugador nuevo(id,color,alias);
        jugadores.push_back(nuevo);
        id++;
    }
    asignarUnidades();
    std::cin.ignore();
}

void Partida::asignarUnidades(){
    int unidades = 0, numJ = jugadores.size();
    switch(numJ){
        case 3:
            unidades = 35;
            break;
        case 4:
            unidades = 30;
            break;
        case 5:
            unidades = 25;
            break;
        case 6:
            unidades = 20;
            break;
    }
    for(int i = 0 ; i < jugadores.size() ; i++){
        jugadores[i].setUnidades(unidades);
    }
}

bool Partida::buscarColorRepetido (std::string color){
    for(int i = 0 ; i < jugadores.size() ; i++){
        if(jugadores[i].getColor() == color){
            return true;
        }
    }
    return false;
}

void Partida::ubicarUnidades(bool& inicializado, int numUnidades) {
    int auxPais = 0;
    bool lleno = false;
    bool ocupado = true;

    mostrarInicializacion();

    while(!lleno){

        for(int i=0; i<jugadores.size() && !lleno; i++){
            do{
                std::cout<<"\nJUGADOR:"<<jugadores[i].getAlias()<<std::endl;
                std::cout<<"Ingrese el numero del pais: \n$";
                std::cin>>auxPais;
                ocupado = this->grafo.paisLleno(auxPais);
                if(ocupado){
                    std::cout<<"Pais ocupado o no valido"<<std::endl;
                }
            }while(ocupado && !lleno);
            if(!lleno){
                this->grafo.ocuparPais(jugadores[i].getId(), auxPais, 1);
                jugadores[i].setUnidades(jugadores[i].getUnidades()-1);
                jugadores[i].agregarCarta(obtenerCarta(auxPais));
            }
            lleno = this->grafo.lleno();
        }
    }
    std::cin.ignore();
    inicializado = true;
}

void Partida::mostrarInicializacion(){//mostrar jugadores con sus cartas

    std::cout << "\n****************************************" << std::endl;
    std::cout << "*                JUGADORES              *" << std::endl;
    std::cout << "****************************************" << std::endl << std::endl;
    for(int i = 0 ; i < jugadores.size() ; i++){
        std::cout<<"Jugador "<<jugadores[i].getId()<<":"<<jugadores[i].getAlias()<<std::endl;
        std::cout<<"color: "<<jugadores[i].getColor()<<std::endl;
        std::cout<<"tiene "<<jugadores[i].getUnidades()<<" unidades "<<std::endl;
        std::cout<<"tiene "<<jugadores[i].getCartas().size()<<" cartas: "<<std::endl;
        std::list<Carta> cartasJ = jugadores[i].getCartas();
        std::list<Carta>::iterator it = cartasJ.begin();
        for(it = cartasJ.begin();it != cartasJ.end();it++){
            std::cout<<it->getId()<<":"<<it->getPais()<<std::endl;
        }
        std::cout<<std::endl<<std::endl;
    }
    std::cout<<"\n****************************************"<<std::endl;
    std::cout<<"*   TERRITORIOS DEL TABLERO DE JUEGO   *"<<std::endl;
    std::cout<<"****************************************"<<std::endl<<std::endl;

    for(int i = 0 ; i < this->grafo.getPaises().size() ; i++){
        std::cout<<this->grafo.getPaises()[i].get_id()<<":"<<this->grafo.getPaises()[i].get_nombre()<<" - jugador "
        <<this->grafo.getPaises()[i].get_id_jugador()<<" con "<<this->grafo.getPaises()[i].get_unidades()
        <<" unidades"<<std::endl;
    }
}

//operaciones de ataque
//--------------------------------------------------------------------

Carta Partida::obtenerCarta(int idPais){
    std::list<Carta>::iterator it = cartas.begin();
    for(it = cartas.begin();it != cartas.end();it++){
        if(it->getId() == idPais){
            return *it;
        }
    }
}

void Partida::elegirUbicacionAtaque(int posJug, int * paisOrigen, int * paisDestino){
    bool ocupado, esVecino, apto, atacable;
    int indexPaisOrigen, indexPaisDestino;

    do{
        std::cout<<"Ingrese numero de pais desde donde quiere atacar: \n$";
        std::cin>>*paisOrigen;
        ocupado = this->grafo.jugadorOcupaPais(jugadores[posJug-1].getId(), *paisOrigen);
        indexPaisOrigen = this->grafo.searchVertice(*paisOrigen);
        apto = this->grafo.origenAptoParaAtaque(jugadores[posJug-1].getId(),*paisOrigen);
        if(!ocupado){
            std::cout<<"No tiene unidades suyas en este pais"<<std::endl;
        }
        if(indexPaisOrigen == -1){
            std::cout<<"No existe este pais"<<std::endl;
        }
        if(!apto){
            std::cout<<"No puede atacar desde este pais, no tiene vecinos a los cuales atacar"<<std::endl;
        }

    }while(indexPaisOrigen == -1 || !ocupado || !apto);
    std::cout<<"VA A ATACAR DESDE EL PAIS "<<*paisOrigen<<std::endl<<std::endl;

    do{
        std::cout<<"Ingrese numero de pais a atacar: \n$";
        std::cin>>*paisDestino;
        esVecino = this->grafo.searchEdge(*paisOrigen, *paisDestino);
        indexPaisDestino = this->grafo.searchVertice(*paisDestino);
        ocupado = this->grafo.jugadorOcupaPais(jugadores[posJug-1].getId(), *paisDestino);
        atacable = this->grafo.paisAtacable(jugadores[posJug-1].getId(), *paisDestino);

        if(indexPaisDestino == -1){
            std::cout<<"Este pais no existe"<<std::endl;
        }
        if(!esVecino){
            std::cout<<"No puede atacar este pais, no es vecino de "<<*paisOrigen<<std::endl;
        }
        if(!atacable){
            std::cout<<"No puede atacar este pais, no hay nadie, puede fortificar si desea "<<std::endl;
        }
        if(ocupado){
            std::cout<<"No  se puede autoatacar"<<std::endl;
        }

    }while(indexPaisDestino == -1 || !esVecino || ocupado || !atacable);

    std::cout<<"VA A ATACAR AL PAIS "<<*paisDestino<<std::endl;
}

void Partida::atacar(int posAtacante, int origen, int destino){
    int posAtacado = buscarAtacado(destino), puntosAtacante = 0, puntosAtacado = 0, continuar;
    bool vaciado = false;

    std::cout<<"\nATACANTE ES:"<<jugadores[posAtacante-1].getId()<<" en "<<origen<<std::endl;
    std::cout<<"ATACADO ES:"<<jugadores[posAtacado].getId()<<" en "<<destino<<std::endl;

    do{
        std::cout<<"\nATACANTE LANZA  DADOS:"<<std::endl;
        puntosAtacante = lanzarDados(3);
        std::cout<<"\nATACANTE OBTUVO:"<<puntosAtacante<<std::endl;

        std::cout<<"\nATACADO LANZA DADOS:"<<std::endl;
        puntosAtacado = lanzarDados(2);
        std::cout<<"\nATACADO OBTUVO:"<<puntosAtacado<<std::endl;

        if(puntosAtacado > puntosAtacante){
            std::cout<<"\nATACADO GANA"<<std::endl<<std::endl;
            //ATACADO GANA
            vaciado=this->grafo.quitarUnidad(origen);
            if(vaciado){
                if(!jugadores[posAtacado].tieneCarta(origen)){
                    jugadores[posAtacado].agregarCarta(obtenerCarta(origen));
                }
                jugadores[posAtacante-1].quitarCarta(origen);
                std::cout<<"\nEl atacante ha quedado sin unidades en su territorio, lo ha perdido:"<<std::endl;
            }
        }
        if(puntosAtacado < puntosAtacante){
            std::cout<<"\nATACANTE GANA"<<std::endl<<std::endl;
            //ATACANTE GANA
            vaciado=this->grafo.quitarUnidad(destino);
            if(vaciado){
                if(!jugadores[posAtacante-1].tieneCarta(destino)){
                    jugadores[posAtacante-1].agregarCarta(obtenerCarta(destino));
                }
                jugadores[posAtacado].quitarCarta(destino);
                std::cout<<"\nEl atacado ha quedado sin unidades en su territorio, lo ha perdido, atacante puede fortificar para ocupar el territorio"<<std::endl;
            }
        }
        if(puntosAtacado == puntosAtacante){
            std::cout<<"\nATACADO GANA POR EMPATE"<<std::endl<<std::endl;
            //ATACADO GANA
            vaciado= this->grafo.quitarUnidad(origen);
            if(vaciado){
                jugadores[posAtacante-1].quitarCarta(origen);
                if(!jugadores[posAtacado].tieneCarta(origen)){
                    jugadores[posAtacado].agregarCarta(obtenerCarta(origen));
                }
                std::cout<<"\nEl atacante ha quedado sin unidades en su territorio, lo ha perdido:"<<std::endl;
            }
        }
        do{
            std::cout<<"Desea atacar otra vez?:\n1) Si\n2) No\n$";
            std::cin>>continuar;
            if(continuar < 1 || continuar > 2){
                std::cout<<"Opcion  no valida";
            }
        }while((continuar < 1 || continuar > 2) && !vaciado);

    }while(!vaciado && continuar == 1);

}

int Partida::buscarAtacado(int idP){
    int indexPais = this->grafo.searchVertice(idP);
    for(int i = 0 ; i < jugadores.size() ; i++){
        if(jugadores[i].getId() == this->grafo.getPaises()[indexPais].get_id_jugador()){
            return i;
        }
    }
    return -1;
}

int Partida::lanzarDados(int numDados){
    std::vector<int> dados;
    int descartar = 0, resultado = 0;

    srand(time(NULL));
    for(int i = 0 ; i < numDados ; i++){
        int n = 1 + rand() % (7 - 1);
        dados.push_back(n);
    }
    for(int i = 0 ; i < dados.size() ; i++){
        std::cout<<"Dado "<<i+1<<":"<<dados[i]<<std::endl;
    }
    if(numDados == 3){
        do{
            std::cout<<"Elija dado para descartar:\n$";
            std::cin>>descartar;
        }while(descartar < 1 || descartar > 3);
        dados.erase(dados.begin()+descartar-1);
        for(int i = 0 ; i < dados.size() ; i++){
            resultado = resultado+dados[i];
        }
    }else{
        for(int i = 0 ; i < dados.size() ; i++){
            resultado = resultado+dados[i];
        }
    }
    return resultado;
}

//operaciones de ubicacion de unidades
//--------------------------------------------------------------------

void Partida::intercambioNormal(int posJ){

    int paisesDelJugador = 0, gana = 0;

    paisesDelJugador = this->grafo.calcularPaisesJugador(jugadores[posJ-1].getId());
    std::cout<<"\nJUGADOR TIENE "<<paisesDelJugador<<" paises y "<<jugadores[posJ-1].getCartas().size()<<"cartas"<<std::endl;

    if(jugadores[posJ-1].getCartas().size() < 3){
        std::cout << "El jugador no tiene suficientes cartas para el intercambio." << std::endl;
    }else{
        gana =  paisesDelJugador/3;
        jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
        std::cout<<"ha obtenido "<<gana<<" unidades de forma normal"<<std::endl;

        if(this->grafo.jugadorPuedeUbicar(jugadores[posJ-1].getId())){
            ubicarNuevasUnidades(posJ, gana, false);
        }else{
            std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl<<std::endl;
        }

    }
}

void Partida::ubicarNuevasUnidades(int posJ, int gana, bool propias){
    int pais = 0, unidades = 0, op;
    bool ocupado;

    do{
        do{
            std::cout<<"\nIngrese numero de unidades a ubicar: \n$";
            std::cin>>unidades;
            if(unidades > gana){
                std::cout << "No tiene tantas unidades" << std::endl;
            }
        }while(unidades > gana);

        do{
            std::cout<<"Ingrese el numero del pais: \n$";
            std::cin>>pais;
            ocupado = this->grafo.paisFortificable(jugadores[posJ-1].getId(), pais);
            if(!ocupado){
                std::cout<<"Pais no diponible, esta ocupado o no lo domina el jugador"<<std::endl;
            }
        }while(!ocupado);

        this->grafo.ocuparPais(jugadores[posJ-1].getId(), pais, unidades);
        jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()-unidades);

        if(!(jugadores[posJ-1].tieneCarta(pais))){
            jugadores[posJ-1].agregarCarta(obtenerCarta(pais));
        }
        gana = gana - unidades;
        std::cout<<"Se han ubicado "<<unidades<<" unidades en el pais "<<pais<<std::endl;

        if(propias){
            do{
                std::cout<<"Desea continuar?: \n1) Si\n2) No\n$";
                std::cin>>op;
                if(op < 1 || op >2){
                    std::cout<<"Opcion no valida"<<std::endl;
                }
                if(jugadores[posJ-1].getUnidades() == 0){
                    std::cout<<"Se ha quedado sin unidades"<<std::endl;
                    break;
                }
            }while(op < 1 || op >2);
        }

        if(op == 2){
            break;
        }

    }while(gana > 0 || (propias && jugadores[posJ-1].getUnidades() > 0));
}

void Partida::intercambioPorPaises(int posJ){
    std::list<std::string> continentes;
    int gana = this->grafo.intercambioPaises(jugadores[posJ-1].getId(), continentes);

    std::cout<<"\nJUGADOR HA GANADO "<<gana<<" POR HABER CONQUISTADO:"<<std::endl<<std::endl;
    for(std::string c : continentes){
        std::cout<<c<<std::endl;
    }
    jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
    if(gana > 0){
        if(this->grafo.jugadorPuedeUbicar(jugadores[posJ-1].getId())){
            ubicarNuevasUnidades(posJ,gana,false);
        }else{
            std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl<<std::endl;
        }

    }
}

bool Partida::intercambioPorCartasCondicionales(int posJ) {
    int cartasIguales = 0, cartasTodas = 0;
    jugadores[posJ-1].tresCartasCumplen(&cartasIguales, &cartasTodas);
    if(cartasIguales > 0 || cartasTodas > 0) {
        return true;
    }
    return false;
}

bool Partida::intercambiarCartas(int posJ, int gana){

    int soldados = 0, caballos = 0, canions = 0;
    bool jugadorIntercambia = false;
    std::string soldado = "soldado", caballo = "caballo", canion = "canion";

    std::list<Carta> cartasJ = jugadores[posJ-1].getCartas();
    std::list<Carta>::iterator it = cartasJ.begin();
    for(it = cartasJ.begin();it != cartasJ.end();it++){
        if(it->getFigura() == soldado){
            soldados = soldados+1;
        }if(it->getFigura() == caballo){
            caballos = caballos+1;
        }if(it->getFigura() == canion){
            canions = canions+1;
        }
    }
    if(soldados >= 3){
        if(ubicarUnidadesDeCartas(soldado,posJ,gana,true)){
            jugadorIntercambia = true;
        }
    }if(caballos >= 3){
        if(ubicarUnidadesDeCartas(caballo,posJ,gana,true)){
            jugadorIntercambia = true;
        }
    }if(canions >= 3){
        if(ubicarUnidadesDeCartas(canion,posJ,gana,true)){
            jugadorIntercambia = true;
        }
    }if(soldados >= 1 && caballos >= 1 && canions >= 1){
        if(ubicarUnidadesDeCartas(canion,posJ,gana,false)){
            jugadorIntercambia = true;
        }
    }

    return jugadorIntercambia;
}

bool Partida::ubicarUnidadesDeCartas(std::string figura, int posJ, int gana, bool mismas){

    int rta;
    bool jugadorIntercambia = false;
    if(mismas){
        std::cout<<"Tiene 3 o mas cartas de "<<figura<<std::endl;
        do{
            std::cout<<"\nDesea intercambiarlas?\n1) Si\n2) No\n$";
            std::cin>>rta;
            if(rta < 1 || rta >2){
                std::cout<<"\nOpcion no valida"<<std::endl;
            }
        }while(rta < 1 || rta >2);
        if(rta == 1){
            jugadorIntercambia = true;
            elegirCartasIntercambio(posJ, figura, true);
            jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
            if(this->grafo.jugadorPuedeUbicar(jugadores[posJ-1].getId())){
                ubicarNuevasUnidades(posJ, gana, false);
            }else{
                std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl;
            }

        }else{
            std::cout<<"\nHa decidido no intercambiar cartas de "<<figura<<std::endl;
        }
    }else{
        std::cout<<"Tiene al menos una carta de cada figura "<<std::endl;
        do{
            std::cout<<"\nDesea intercambiarlas?\n1) Si\n2) No\n$";
            std::cin>>rta;
            if(rta < 1 || rta >2){
                std::cout<<"\nOpcion no valida"<<std::endl;
            }
        }while(rta < 1 || rta >2);
        if(rta == 1){
            jugadorIntercambia = true;
            elegirCartasIntercambio(posJ, figura, false);
            jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
            if(this->grafo.jugadorPuedeUbicar(jugadores[posJ-1].getId())){
                ubicarNuevasUnidades(posJ, gana, false);
            }else{
                std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl;
            }
        }else{
            std::cout<<"\nHa decidido no intercambiar cartas"<<std::endl;
        }
    }
    return jugadorIntercambia;
}

void Partida::elegirCartasIntercambio(int posJ, std::string figura, bool mismas) {
    int op = 0;
    bool cartaCorrecta = false;
    std::list<int> cartasIntercambiadas;

    if(mismas){
        for(int i = 0 ; i < 3 ; i++){
            std::cout << "Cartas de " << figura << ":" << std::endl;
            jugadores[posJ-1].showCartasFigureFilter(figura);
            do{
                std::cout<<"\nEscriba el numero de la carta que quiere eliminar \n$";
                std::cin>>op;
                Carta carta = obtenerCarta(op);
                cartaCorrecta = jugadores[posJ-1].tieneCarta(op) && carta.getFigura() == figura;
                if(!cartaCorrecta){
                    std::cout<<"\nCarta no valida"<<std::endl;
                }
            }while(!cartaCorrecta);

            jugadores[posJ-1].quitarCarta(op);
            cartasIntercambiadas.push_back(op);
        }
    }else {
        for (int i = 0; i < 3; i++) {
            std::cout << "Cartas :" << std::endl;
            jugadores[posJ - 1].showCartas();
            do {
                std::cout << "\nEscriba el numero de la carta que quiere eliminar \n$";
                std::cin >> op;
                Carta carta = obtenerCarta(op);
                cartaCorrecta = jugadores[posJ - 1].tieneCarta(op) && carta.getFigura() == figura;
                if (!cartaCorrecta) {
                    std::cout << "\nCarta no valida" << std::endl;
                }
            } while (!cartaCorrecta);

            jugadores[posJ - 1].quitarCarta(op);
            cartasIntercambiadas.push_back(op);
        }
    }
    std::cout<<"\nHA INTERCAMBIADO LAS CARTAS:"<<std::endl;
    for(std::list<int>::iterator iti = cartasIntercambiadas.begin(); iti != cartasIntercambiadas.end(); iti++){
        std::cout<<*iti<<std::endl;
    }
    for(std::list<int>::iterator iti = cartasIntercambiadas.begin(); iti != cartasIntercambiadas.end(); iti++){
        if(this->grafo.jugadorOcupaPais(jugadores[posJ-1].getId(), *iti)){
            std::cout<<"\nHa ganado 2 unidades adicionales para el pais "<<*iti<<" se ubicaron en dicho pais"<<std::endl;
            this->grafo.ocuparPais(jugadores[posJ-1].getId(),*iti,2);
        }
    }

}

//operaciones de fortificación
//--------------------------------------------------------------------

void Partida::fortificarTerritorio(int jugadorIndex) {
    int origen = 0, destino = 0, unidadesM = 0;
    bool ocupaOrigen, suficientes , vecino, libre, apto;

    do{
        std::cout<<"Ingrese numero de pais desde donde quiere mover unidad: \n$";
        std::cin>>origen;
        //jugador ocupa terreno
        ocupaOrigen = this->grafo.jugadorOcupaPais(jugadores[jugadorIndex-1].getId(), origen);
        apto = this->grafo.aptoParaFortificar(jugadores[jugadorIndex-1].getId(), origen);
        if (!ocupaOrigen) {
            std::cout << "El jugador no ocupa el pais de origen." << std::endl;
        }
        if(!apto){
            std::cout << "El pais origen no tiene vecinos para fortificar." << std::endl;
        }
    }while(!ocupaOrigen || !apto);

    do{
        std::cout<<"Ingrese numero de unidades a mover: \n$";
        std::cin>>unidadesM;
        //cuenta con unidades suficientes
        suficientes = this->grafo.unidadesSuficientes(jugadores[jugadorIndex-1].getId(), origen, unidadesM);
        if (!suficientes) {
            std::cout << "El jugador no cuenta con unidades suficientes." << std::endl;
        }
    }while(!suficientes);

    do{
        std::cout<<"Ingrese numero de pais a fortificar: \n$";
        std::cin>>destino;
        //jugador ocupa terreno o terreno está libre
        libre = this->grafo.paisFortificable(jugadores[jugadorIndex-1].getId(), destino);
        vecino = this->grafo.searchEdge(origen, destino);
        if (!vecino) {
            std::cout << "El pais de destino no es vecino del pais de origen." << std::endl;
        }
        if (!libre) {
            std::cout << "El pais de destino no eta libre, o no lo ocupa el jugador." << std::endl;
        }
    }while(!vecino || !libre);

    this->grafo.moverUnidades(jugadores[jugadorIndex-1].getId(), origen, destino, unidadesM);

    if(!jugadores[jugadorIndex-1].tieneCarta(destino)){
        jugadores[jugadorIndex-1].agregarCarta(obtenerCarta(destino));
    }

    std::cout << "Se fortifico dese " << origen << " hasta "<<destino<<" con "<<unidadesM<<" unidades"<< std::endl;

}

//operaciones de terminación del juego
//--------------------------------------------------------------------
bool Partida::jugadorVigente(int posJ){
    for(int i = 0 ; i < this->grafo.getPaises().size() ; i++){
        if(this->grafo.getPaises()[i].get_id_jugador() == jugadores[posJ-1].getId()){
            return true;
        }
    }
    if(intercambioPorCartasCondicionales(posJ)){
        return true;
    }

    if(jugadores[posJ-1].getUnidades() > 0){
        return true;
    }
    return false;
}

bool Partida::finalizado(int * ganador){
    int totalPaises = this->grafo.getPaises().size();
    for(int i = 0 ; i < this->jugadores.size() ; i++){
        if(totalPaises == this->grafo.calcularPaisesJugador(this->jugadores[i].getId())){
            *ganador = this->jugadores[i].getId();
        }
    }
    return false;
}