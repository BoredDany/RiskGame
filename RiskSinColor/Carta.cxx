#include "Carta.h"
#include <cstring>

//constructores
//--------------------------------------------------------------------
Carta::Carta(int id, std::string fig, std::string cont, std::string pai) {
    this->id = id;
    this->figura = fig;
    this->continente = cont;
    this->pais = pai;
}

//getters
//--------------------------------------------------------------------
int Carta::getId(){
    return id;
};
std::string Carta::getFigura() {
    return figura;
}

std::string Carta::getPais(){
    return pais;
};

std::string Carta::getContinente() {
    return continente;
}