#include "Continente.h"
#include "Carta.h"
#include "Jugador.h"
#include "Partida.h"
#include<list>
#include<vector>
#include<string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <time.h>

Partida::Partida(int id){
    this->id = id;
}
std::vector<Jugador> Partida::get_jugadores() {
    return jugadores;
}
std::list<Carta> Partida::get_cartas(){
    return cartas;
}
std::list<Continente> Partida::get_tablero(){
    return tablero;
}
void Partida::set_id(int id){
    this->id = id;
}

int Partida::countLines(std::string archivo_cartas){
    int i = 0;
    std::string line;
    std::ifstream inputFile(archivo_cartas);
    if(inputFile.is_open()){
        while(getline(inputFile,line)){
            i++;
        }
        inputFile.clear();
        inputFile.seekg(0);
    }else{
        std::cout<<"No se pudo abrir archivo"<<std::endl;
    }
    inputFile.close();
    return i;
}//contar lineas del archivo de cartas
void Partida::cargarCartas(std::string archivo_cartas){
    std::ifstream inputFile(archivo_cartas);
    std::string line, word;
    int territorio, size = countLines(archivo_cartas);
    std::string figura, pais, continente;

    //terreno; pais; figura; continente
    if(inputFile.is_open()){
        for(int i = 0 ; i < size ; i++){
            getline(inputFile,line);
            std::stringstream str(line);
            getline(str,word,';');
            territorio = stoi(word);
            getline(str,word,';');
            pais = word;
            getline(str,word,';');
            figura = word;
            getline(str,word,';');
            continente = word;
            cartas.push_back(Carta (territorio,figura,continente,pais));
        }

    }else{
        std::cout<<"Archivo no leido"<<std::endl;
    }
    inputFile.close();
}//cargar cartas leyendo archivo
bool Partida::buscarColorRepetido (std::string color){
    for(int i = 0 ; i < jugadores.size() ; i++){
        if(jugadores[i].getColor() == color){
            return true;
        }
    }
    return false;
}//retornar si un color ya esta elejido por jugador
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
}//asignar unidades a jugadores
void Partida::inicializarJugadores(){
    int numJ = 0, id = 1, colorN = 0;
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
}//inicializar info de jugadores
bool Partida::repetido(std::string nombre){
    std::list<Continente>::iterator itCo = tablero.begin();
    for( itCo = tablero.begin() ; itCo != tablero.end() ; itCo++){
        if(nombre == itCo->get_nombre()){
            return true;
        }
    }
    return false;
}//retornar si un continente ya esta repetido
void Partida::inicializarTablero(){
    std::list<Carta>::iterator it = cartas.begin();
    for( it = cartas.begin(); it != cartas.end() ; it++){
        bool rep = repetido(it->getContinente());
        if(!rep){
            Continente c(it->getContinente());
            tablero.push_back(c);
        }
    }
}//cargar continentes
void Partida::llenarContinentes() {
    std::list<Carta>::iterator it = cartas.begin();
    std::list<Continente>::iterator itCo = tablero.begin();

    for( itCo = tablero.begin(); itCo != tablero.end() ; itCo++){
        for( it = cartas.begin(); it != cartas.end() ; it++){
            if(itCo->get_nombre() == it->getContinente()){
                Pais p(it->getId(),it->getPais(),it->getContinente());
                itCo->aggPais(p);
            }
        }
    }
}//lenar continentes los paises
void Partida::aggConexion(int pais, int vecino){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        it->aggConexion(pais,vecino);
    }
}//agregar vecino a un pais
void Partida::cargarConexiones(std::string archivo){
    std::ifstream file (archivo);
    int size = countLines(archivo);
    std::string line, word;

    if(file.is_open()){
        for(int i = 0 ; i<size ; i++){
            getline(file,line,'\n');
            std::stringstream ss(line);
            getline(ss,word,'-');
            int pais = stoi(word);
            while(getline(ss,word,';')){
                int vecino = stoi(word);
                aggConexion(pais,vecino);
            }
        }


    }else{
        std::cout<<"Archivo de conexiones no leido"<<std::endl;
    }
    file.close();
}//leer paises vecinos del archivo de conexiones
bool Partida:: tableroLleno(){
    std::list<Continente>::iterator it = tablero.begin();
    bool llenoTab = true;
    for(it = tablero.begin();it != tablero.end();it++){
        if(!it->lleno()){
            llenoTab = false;
        }
    }
    return llenoTab;
}//retornar si el tablero esta lleno
bool Partida::paisLleno(int id){
    std::list<Continente>::iterator it = tablero.begin();
    bool lleno = true;
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> paises = it->get_paises();
        std::list<Pais>::iterator itPaises = paises.begin();
        for(itPaises = paises.begin() ; itPaises != paises.end() ; itPaises++){
            if(itPaises->get_id() == id && itPaises->get_unidades() == 0){
                lleno = false;
            }
        }

    }
    return lleno;
}//saber si pais esta ocupado
void Partida::ocuparPais(int idJugador, int idPais, int unidades){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        it->ocuparPais(idJugador,idPais, unidades);
    }
}//ocupar pais por jugador
Carta Partida::obtenerCarta(int idPais){
    std::list<Carta>::iterator it = cartas.begin();
    for(it = cartas.begin();it != cartas.end();it++){
        if(it->getId() == idPais){
            return *it;
        }
    }
}//reclamar carta por ocupar pais
void Partida::ubicarUnidades(bool& inicializado, int numUnidades) {
    std::list<Continente>::iterator itContinetes;
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
                ocupado = paisLleno(auxPais);
                if(ocupado){
                    std::cout<<"Pais ocupado o no valido"<<std::endl;
                }
            }while(ocupado && !lleno);
            if(!lleno){
                ocuparPais(jugadores[i].getId(), auxPais, 1);
                jugadores[i].setUnidades(jugadores[i].getUnidades()-1);
                jugadores[i].agregarCarta(obtenerCarta(auxPais));
            }
            lleno = tableroLleno();
        }
    }
    std::cin.ignore();
    inicializado = true;

}//ubicar unidades de cada jugador
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

    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::cout<<it->get_nombre()<<std::endl;
        std::cout<<"------------------------------------------------------"<<std::endl;
        std::list<Pais> p=it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            std::cout<<itp->get_id()<<":"<<itp->get_nombre()<<" - jugador "<<itp->get_id_jugador()<<" con "<<itp->get_unidades()<<" unidades"<<std::endl;
        }
        std::cout<<"------------------------------------------------------"<<std::endl<<std::endl;
    }
}//imprimir resumen
bool Partida::paisExiste(int idP){
    std::list<Continente>::iterator it = tablero.begin();
    bool existe = false;
    for(it = tablero.begin();it != tablero.end();it++){
        existe = it->paisExiste(idP);
        if(existe){
            break;
        }
    }
    return existe;
}//retornar si pais existe
bool Partida::jugadorOcupaPais(int idJ, int idP){
    std::list<Continente>::iterator it = tablero.begin();
    bool ocupa = false;
    for(it = tablero.begin();it != tablero.end();it++){
        ocupa = it->jugadorOcupaPais(idP, idJ);
        if(ocupa){
            break;
        }
    }
    return ocupa;
}//retornar si jugador ocupa pais
bool Partida::paisVecino(int paisOrigen, int paisDestino){
    std::list<Continente>::iterator it = tablero.begin();
    bool vecino = false;
    for(it = tablero.begin();it != tablero.end();it++){
        vecino = it->paisVecino(paisOrigen,paisDestino);
        if(vecino){
            break;
        }
    }
    return vecino;
}//retornar si pais es vecino de otro
bool Partida::paisAtacable(int idJ, int idP){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id() == idP){
                if(itp->get_id_jugador() != idJ && itp->get_id_jugador() != 0){
                    return true;
                }
            }
        }
    }
    return false;
}//retornar si pais es atacable
bool Partida::puedeAtacar(int posJ){
    bool puede = false;
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(jugadores[posJ-1].getId() == itp->get_id_jugador()){
                std::list<int> vecinos = itp->get_conexiones();
                std::list<int>::iterator itv = vecinos.begin();
                for(itv = vecinos.begin();itv != vecinos.end();itv++){
                    puede = paisAtacable(jugadores[posJ-1].getId(), *itv);
                    if(puede){
                        break;
                    }
                }
            }
        }
    }
    return puede;
}//retornar si jugador puede atacar
bool Partida::origenAptoParaAtaque(int posJ, int idP){
    std::list<Continente>::iterator it = tablero.begin();

    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id() == idP){
                std::list<int> vecinos = itp->get_conexiones();
                std::list<int>::iterator itv = vecinos.begin();
                for(itv = vecinos.begin();itv != vecinos.end();itv++){
                    if(paisAtacable(jugadores[posJ-1].getId(),*itv)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}//retornar si pais origen permite atacar
void Partida::elegirUbicacionAtaque(int posJug, int * paisOrigen, int * paisDestino){
    bool ocupado = false, existe = false, esVecino = false, lleno = false, apto = false;
    int idAtacado = 0;
    do{
        std::cout<<"Ingrese numero de pais desde donde quiere atacar: \n$";
        std::cin>>*paisOrigen;
        ocupado = jugadorOcupaPais(jugadores[posJug-1].getId(), *paisOrigen);
        existe = paisExiste(*paisOrigen);
        apto = origenAptoParaAtaque(posJug,*paisOrigen);
        if(!ocupado){
            std::cout<<"No tiene unidades suyas en este pais"<<std::endl;
        }
        if(!existe){
            std::cout<<"No existe este pais"<<std::endl;
        }
        if(!apto){
            std::cout<<"No puede atacar desde este pais, no tiene vecinos a los cuales atacar"<<std::endl;
        }

    }while(!existe || !ocupado || !apto);
    std::cout<<"VA A ATACAR DESDE EL PAIS "<<*paisOrigen<<std::endl<<std::endl;

    do{
        std::cout<<"Ingrese numero de pais a atacar: \n$";
        std::cin>>*paisDestino;
        esVecino = paisVecino(*paisOrigen, *paisDestino);
        existe = paisExiste(*paisDestino);
        ocupado = jugadorOcupaPais(jugadores[posJug-1].getId(), *paisDestino);
        idAtacado = buscarAtacado(*paisDestino);
        if(!existe){
            std::cout<<"Este pais no existe"<<std::endl;
        }
        if(!esVecino){
            std::cout<<"No puede atacar este pais, no es vecino de "<<*paisOrigen<<std::endl;
        }
        if(idAtacado == -1){
            std::cout<<"No puede atacar este pais, no hay nadie, puede fortificar si desea "<<std::endl;
        }
        if(ocupado){
            std::cout<<"No  se puede autoatacar"<<std::endl;
        }
    }while(!existe || !esVecino || idAtacado == -1 || ocupado);

    std::cout<<"VA A ATACAR AL PAIS "<<*paisDestino<<std::endl;
}//seleccionar origen y destino de ataque
int Partida::buscarAtacado(int idP){
    int atacado =  -1, posAtacado = -1;
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id() == idP && itp->get_unidades() > 0){
                atacado = itp->get_id_jugador();
            }
        }
    }
    for(int i = 0 ; i < jugadores.size() ; i++){
        if(jugadores[i].getId() == atacado){
            posAtacado = i;
        }
    }
    return posAtacado;
}//buscar jugador atacado
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
}//lanzar dados
bool Partida::quitarUnidad(int idP){
    std::list<Continente>::iterator it = tablero.begin();
    bool vaciado = false, encontrado = false;
    for(it = tablero.begin();it != tablero.end();it++){
        vaciado = it->quitarUnidad(idP,encontrado);
        if(encontrado){
            break;
        }
    }
    return vaciado;
}//quitar unidad a jugador perdedor del ataque
void Partida::atacar(int posAtacante, int origen, int destino){
    int posAtacado = buscarAtacado(destino), puntosAtacante = 0, puntosAtacado = 0, continuar = 0;
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
            vaciado=quitarUnidad(origen);
            if(vaciado){
                if(!jugadores[posAtacado].tieneCarta(origen)){
                    Carta c = obtenerCarta(origen);
                    jugadores[posAtacado].agregarCarta(c);
                }
                jugadores[posAtacante-1].quitarCarta(origen);
                std::cout<<"\nEl atacante ha quedado sin unidades en su territorio, lo ha perdido:"<<std::endl;
            }
        }
        if(puntosAtacado < puntosAtacante){
            std::cout<<"\nATACANTE GANA"<<std::endl<<std::endl;
            //ATACANTE GANA OK
            vaciado=quitarUnidad(destino);
            if(vaciado){
                if(!jugadores[posAtacante-1].tieneCarta(destino)){
                    Carta c = obtenerCarta(destino);
                    jugadores[posAtacante-1].agregarCarta(c);
                }
                jugadores[posAtacado].quitarCarta(destino);
                std::cout<<"\nEl atacado ha quedado sin unidades en su territorio, lo ha perdido, atacante puede fortificar para ocupar el territorio"<<std::endl;
            }
        }
        if(puntosAtacado == puntosAtacante){
            std::cout<<"\nATACADO GANA POR EMPATE"<<std::endl<<std::endl;
            //ATACADO GANA
            vaciado=quitarUnidad(origen);
            if(vaciado){
                jugadores[posAtacante-1].quitarCarta(origen);
                if(!jugadores[posAtacado].tieneCarta(origen)){
                    Carta c = obtenerCarta(origen);
                    jugadores[posAtacado].agregarCarta(c);
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

}//ejecutar ataque

bool Partida::puedeUbicar(int idJ){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id_jugador() == idJ || itp->get_id_jugador() == 0){
                return true;
            }
        }
    }
    return false;
}
void Partida::ubicarNuevasUnidades(int posJ, int gana, bool propias){
    int pais = 0, unidades = 0, op  = 0;
    bool ocupado  = false, tieneCarta = false;

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
            ocupado = paisFortificable(jugadores[posJ-1].getId(), pais);
            if(!ocupado){
                std::cout<<"Pais no diponible, esta ocupado o no lo domina el jugador"<<std::endl;
            }
        }while(!ocupado);

        ocuparPais(jugadores[posJ-1].getId(), pais, unidades);
        jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()-unidades);

        tieneCarta = jugadores[posJ-1].tieneCarta(pais);
        if(!tieneCarta){
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
}//ubicar unidades ganadas por jugador
int Partida::calcularPaises(int idJ){
    int paises = 0;
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id_jugador() == idJ){
                paises += 1;
            }
        }
    }
    return paises;
}//contar paises que pertenecen a un jugador
void Partida::intercambioNormal(int posJ){

    int paisesDelJugador = 0, gana = 0;

    paisesDelJugador = calcularPaises(jugadores[posJ-1].getId());
    std::cout<<"\nJUGADOR TIENE "<<paisesDelJugador<<" paises"<<std::endl;

    if(paisesDelJugador < 3){
        std::cout << "El jugador no tiene suficientes cartas para el intercambio." << std::endl;
    }else{
        gana =  paisesDelJugador/3;
        jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
        std::cout<<"ha obtenido "<<gana<<" unidades de forma normal"<<std::endl;
        if(puedeUbicar(jugadores[posJ-1].getId())){
            ubicarNuevasUnidades(posJ, gana, false);
        }else{
            std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl<<std::endl;
        }

    }

}//dar unidades ganadas segun paises poseidos y ubicarlas
void Partida::intercambioPorPaises(int posJ){
    std::list<Continente>::iterator it = tablero.begin();
    std::list<std::string> continentes;
    int gana = 0;
    for(it = tablero.begin();it != tablero.end();it++){
        if(it->intercambioPorPaises(jugadores[posJ-1].getId())){
            continentes.push_back(it->get_nombre());
        }
    }
    std::list<std::string>::iterator itc = continentes.begin();
    for(itc = continentes.begin();itc != continentes.end();itc++){
        if(*itc == "Africa"){
            gana+=3;
        }
        if(*itc == "Oceania"){
            gana+=2;
        }
        if(*itc == "Asia"){
            gana+=7;
        }
        if(*itc == "Europa"){
            gana+=5;
        }
        if(*itc == "Sur America"){
            gana+=2;
        }
        if(*itc == "Norte America"){
            gana+=5;
        }
    }
    std::cout<<"\nJUGADOR HA GANADO "<<gana<<" POR HABER CONQUISTADO:"<<std::endl<<std::endl;
    for(std::string c : continentes){
        std::cout<<c<<std::endl;
    }
    jugadores[posJ-1].setUnidades(jugadores[posJ-1].getUnidades()+gana);
    if(gana > 0){
        if(puedeUbicar(jugadores[posJ-1].getId())){
            ubicarNuevasUnidades(posJ,gana,false);
        }else{
            std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl<<std::endl;
        }

    }
}//dar unidades ganadas segun continentes conquistados y ubicarlas
bool Partida::intercambioPorCartasCondicionales(int posJ) {
    int cartasIguales = 0, cartasTodas = 0;
    bool gana = false;
    jugadores[posJ-1].tresCartasCumplen(&cartasIguales, &cartasTodas);
    if(cartasIguales > 0 || cartasTodas > 0){
        gana = true;
    }
}//retornar si jugador posee cartas con las condiciones de entrega de unidades
void Partida::elegirCartasIntercambio(int posJ, std::string figura, bool mismas) {
    int op = 0;
    bool cartaCorrecta = false;
    std::list<int> cartasIntercambiadas;

    if(mismas){
        std::cout << "Cartas de " << figura << ":" << std::endl;
        for(int i = 0 ; i < 3 ; i++){
            std::list<Carta> cartasJugador = jugadores[posJ-1].getCartas();
            std::list<Carta>::iterator it = cartasJugador.begin();
            for(it = cartasJugador.begin();it != cartasJugador.end();it++){
                if(it->getFigura() == figura){
                    std::cout<<it->getId()<<":"<<it->getPais()<<" - "<<it->getFigura()<<std::endl;
                }
            }
            do{
                std::cout<<"\nEscriba el numero de la carta que quiere eliminar \n$";
                std::cin>>op;
                cartaCorrecta = jugadores[posJ-1].tieneCarta(op);
                if(!cartaCorrecta){
                    std::cout<<"\nCarta no valida"<<std::endl;
                }
            }while(!cartaCorrecta);

            jugadores[posJ-1].quitarCarta(op);
            cartasIntercambiadas.push_back(op);

        }
    }else {
        std::cout << "Cartas :" << std::endl;

        for (int i = 0; i < 3; i++) {
            std::list<Carta> cartasJugador = jugadores[posJ - 1].getCartas();
            std::list<Carta>::iterator it = cartasJugador.begin();
            for (it = cartasJugador.begin(); it != cartasJugador.end(); it++) {
                std::cout << it->getId() << ":" << it->getPais() << " - " << it->getFigura() << std::endl;
            }
            do {
                std::cout << "\nEscriba el numero de la carta que quiere eliminar \n$";
                std::cin >> op;
                cartaCorrecta = jugadores[posJ - 1].tieneCarta(op);
                if (!cartaCorrecta) {
                    std::cout << "\nCarta no valida" << std::endl;
                }
            } while (!cartaCorrecta);

            jugadores[posJ - 1].quitarCarta(op);
            cartasIntercambiadas.push_back(op);
        }
    }
    std::cout<<"\nHA INTERCAMBIADO LAS CARTAS:"<<std::endl;
    std::list<int>::iterator iti = cartasIntercambiadas.begin();
    for(iti = cartasIntercambiadas.begin();iti != cartasIntercambiadas.end();iti++){
        std::cout<<*iti<<std::endl;
    }
    for(iti = cartasIntercambiadas.begin();iti != cartasIntercambiadas.end();iti++){
        if(jugadorOcupaPais(jugadores[posJ-1].getId(), *iti)){
            std::cout<<"\nHa ganado 2 unidades adicionales para el pais "<<*iti<<" se ubicaron en dicho pais"<<std::endl;
            ocuparPais(jugadores[posJ-1].getId(),*iti,2);
        }
    }

}//seleccionar cartas a intercambiar
bool Partida::ubicarUnidadesDeCartas(std::string figura, int posJ, int gana, bool mismas){

    int rta = 0;
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
            if(puedeUbicar(jugadores[posJ-1].getId())){
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
            if(puedeUbicar(jugadores[posJ-1].getId())){
                ubicarNuevasUnidades(posJ, gana, false);
            }else{
                std::cout<<"\nEn este momento no puede ubicar sus unidades, no hay territorios disponibles para usted"<<std::endl;
            }

        }else{
            std::cout<<"\nHa decidido no intercambiar cartas"<<std::endl;
        }
    }
    return jugadorIntercambia;
}//ubicar unidades ganadas por intercambio de cartas
bool Partida::intercambiarCartas(int posJ, int gana){

    int rta = 0, soldados = 0, caballos = 0, canions = 0;
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
}//intercambiar cartas si se cumple la condicion


bool Partida::unidadesSuficientes(int idJ, int idP, int unidades){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id_jugador() == idJ && itp->get_unidades() >= unidades){
                return true;
            }
        }
    }
    return false;
}//retornar si jugador tiene unidades suficientes
bool Partida::paisFortificable(int idJ, int idP){
    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id() == idP){
                if(itp->get_id_jugador() == idJ || itp->get_id_jugador() == 0){
                    return true;
                }
            }
        }
    }
    return false;
}//retornar si pais es fortificable
bool Partida::puedeFortificar(int posJ){

    std::list<Continente>::iterator it = tablero.begin();
    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(jugadores[posJ-1].getId() == itp->get_id_jugador()){
                std::list<int> vecinos = itp->get_conexiones();
                std::list<int>::iterator itv = vecinos.begin();
                for(itv = vecinos.begin();itv != vecinos.end();itv++){
                    if(paisFortificable(jugadores[posJ-1].getId(), *itv)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}//retornar si jugador puede fortificar
bool Partida::aptoParaFortificar(int idP, int posJ){
    std::list<Continente>::iterator it = tablero.begin();

    for(it = tablero.begin();it != tablero.end();it++){
        std::list<Pais> p = it->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id() == idP){
                std::list<int> vecinos = itp->get_conexiones();
                std::list<int>::iterator itv = vecinos.begin();
                for(itv = vecinos.begin();itv != vecinos.end();itv++){
                    if(paisFortificable(jugadores[posJ-1].getId(),*itv)){
                        return true;
                    }
                }
            }
        }
    }
    return false;
}//retornar si pais de origen permite fortificar
void Partida::moverUnidades(int posJ, int origen, int destino, int unidadesM){
    std::list<Continente>::iterator it = tablero.begin();
    bool movido = false, fortificado = false;
    //restar del origen
    for(it = tablero.begin();it != tablero.end();it++){
        movido = it->moverUnidad(origen,unidadesM);
        if(movido){
            break;
        }
    }
    //sumar al destino
    for(it = tablero.begin();it != tablero.end();it++){
        fortificado = it->fortificar(destino,jugadores[posJ-1].getId(),unidadesM);
        if(fortificado){
            break;
        }
    }
}//mover unidades en fortificacion
void Partida::fortificarTerritorio(int jugadorIndex) {
    int origen = 0, destino = 0, unidadesM = 0;
    bool ocupaOrigen = false, suficientes = false, vecino = false, libre = false, apto = false;

    do{
        std::cout<<"Ingrese numero de pais desde donde quiere mover unidad: \n$";
        std::cin>>origen;
        //jugador ocupa terreno
        ocupaOrigen = jugadorOcupaPais(jugadores[jugadorIndex-1].getId(), origen);
        apto = aptoParaFortificar(origen, jugadorIndex);
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
        suficientes = unidadesSuficientes(jugadores[jugadorIndex-1].getId(), origen, unidadesM);
        if (!suficientes) {
            std::cout << "El jugador no cuenta con unidades suficientes." << std::endl;
        }
    }while(!suficientes);

    do{
        std::cout<<"Ingrese numero de pais a fortificar: \n$";
        std::cin>>destino;
        //jugador ocupa terreno o terreno está libre
        libre = paisFortificable(jugadores[jugadorIndex-1].getId(), destino);
        vecino = paisVecino(origen, destino);
        if (!vecino) {
            std::cout << "El pais de destino no es vecino del pais de origen." << std::endl;
        }
        if (!libre) {
            std::cout << "El pais de destino no eta libre, o no lo ocupa el jugador." << std::endl;
        }
    }while(!vecino || !libre);

    moverUnidades(jugadores[jugadorIndex-1].getId(), origen, destino, unidadesM);

    if(!jugadores[jugadorIndex-1].tieneCarta(destino)){
        Carta c = obtenerCarta(destino);
        jugadores[jugadorIndex-1].agregarCarta(c);
    }

    std::cout << "Se fortifico dese " << origen << " hasta "<<destino<<" con "<<unidadesM<<" unidades"<< std::endl;

}//reccibir ubicacion para fortificar


bool Partida::jugadorVigente(int posJ){
    bool tieneTerritorios = false, tieneCartas = false;
    std::list<Continente>::iterator itc = tablero.begin();

    for(itc = tablero.begin();itc != tablero.end();itc++){
        std::list<Pais> p = itc->get_paises();
        std::list<Pais>::iterator itp = p.begin();
        for(itp = p.begin();itp != p.end();itp++){
            if(itp->get_id_jugador() == jugadores[posJ-1].getId()){
                tieneTerritorios = true;
            }
        }
    }

    tieneCartas = intercambioPorCartasCondicionales(posJ);

    if(jugadores[posJ-1].getUnidades() == 0 && !tieneTerritorios && !tieneCartas){
        return false;
    }
    return true;
}//retornar si jugador aun tiene cartas para intercambiar, unidades en el tablero o unidades propias
bool Partida::finalizado(int * ganador){
    bool finalizado = true;
    int puntaje  = 0;
    std::list<Continente>::iterator it = tablero.begin();

    for(int i = 0 ; i < jugadores.size() ; i++){
        for(it = tablero.begin();it != tablero.end();it++){
            std::list<Pais>p = it->get_paises();
            std::list<Pais>::iterator itp = p.begin();
            for(itp = p.begin();itp != p.end();itp++){
                if(itp->get_id_jugador() == jugadores[i].getId()){
                    puntaje = puntaje+1;
                }
            }
        }
        if(puntaje == 42){
            *ganador = jugadores[i].getId();
            tablero.clear();
            jugadores.clear();
            break;
        }
        if(puntaje < 42){
            puntaje = 0;
        }
    }
}//retornar si un jugador ya gano, junto con su id