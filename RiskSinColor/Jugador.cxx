#include "Jugador.h"
#include "Continente.h"
#include <cstring>
#include <iostream>

//constructores
//--------------------------------------------------------------------
Jugador::Jugador(){
}

Jugador::Jugador(int id, std::string color, std::string alias) {
    this->id = id;
    this->color = color;
    this->alias = alias;
    this->unidades = 0;
}

//getters
//--------------------------------------------------------------------
int Jugador::getId() {
    return id;
}

std::string Jugador::getColor() {
    return color;
}

std::string Jugador::getAlias(){
    return alias;
}

int Jugador::getUnidades(){
    return unidades;
}

std::list<Carta> Jugador::getCartas(){
    return cartas;
}

//setters
//--------------------------------------------------------------------
void Jugador::setId(int idN) {
    this->id = idN;
}

void Jugador::setColor(std::string colorN){
    this->color = colorN;
}

void Jugador::setAlias( std::string aliasN){
    this->alias = aliasN;
}

void Jugador::setUnidades(int unidadesN){
    this->unidades = unidadesN;
}

void Jugador::setCartas(std::list<Carta> cartasN){
    this->cartas = cartasN;
}

//operaciones
//--------------------------------------------------------------------
void Jugador::agregarCarta(Carta carta) {
    cartas.push_back(carta);
}

void Jugador::quitarCarta(int idP) {
    std::list<Carta>::iterator it = cartas.begin();
    std::list<Carta>::iterator itE = cartas.end();
    for(it = cartas.begin();it != cartas.end();it++){
        if(it->getId() == idP){
            itE = it;
            cartas.erase(itE);
        }
    }
}

void Jugador::tresCartasCumplen(int * ganaIguales, int * ganaTodas){
    std::list<Carta>::iterator it = cartas.begin();
    std::list<Carta>::iterator itEliminar = cartas.end();
    int soldado = 0, canion = 0, caballo = 0;

    for(it = cartas.begin();it != cartas.end();it++){
        if(it->getFigura() == "soldado"){
            soldado+=1;
        }
        if(it->getFigura() == "caballo"){
            caballo+=1;
        }
        if(it->getFigura() == "canion"){
            canion+=1;
        }
    }
    if(soldado > 0 && canion > 0 && caballo > 0){
        *ganaTodas = 1;
    }
    else if(soldado >= 3 || canion >= 3 || caballo >=3){
        *ganaIguales = 1;
    }
}

bool Jugador::tieneCarta(int idP){
    std::list<Carta>::iterator it = cartas.begin();
    for (it = cartas.begin();it != cartas.end();it++) {
        if(it->getId() == idP){
            return true;
        }
    }
    return false;
}

void Jugador::showCartas(){
    std::list<Carta>::iterator it = this->cartas.begin();;
    for (it = this->cartas.begin(); it != this->cartas.end(); it++) {
        std::cout << it->getId() << ":" << it->getPais() << " - " << it->getFigura() << std::endl;
    }
}

void Jugador::showCartasFigureFilter(std::string figura){
    std::list<Carta>::iterator it = this->cartas.begin();
    for(it = this->cartas.begin(); it != this->cartas.end(); it++){
        if(it->getFigura() == figura){
            std::cout<<it->getId()<<":"<<it->getPais()<<" - "<<it->getFigura()<<std::endl;
        }
    }
}