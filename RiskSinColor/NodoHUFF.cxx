#include "NodoHUFF.h"

//constructores
//--------------------------------------------------------------------
NodoHUFF::NodoHUFF(){
    this->hijoI = nullptr;
    this->hijoD = nullptr;
}
NodoHUFF::NodoHUFF(Simbolo simbolo){
    this->simbolo = simbolo;
    this->hijoI = nullptr;
    this->hijoD = nullptr;
}

//desstructores
//--------------------------------------------------------------------
NodoHUFF::~NodoHUFF(){
    if (this->hijoI != nullptr) {
        delete this->hijoI;
        this->hijoI = nullptr;
    }
    if (this->hijoD != nullptr) {
        delete this->hijoD;
        this->hijoD = nullptr;
    }
}

//getters
//--------------------------------------------------------------------
Simbolo NodoHUFF::getSimbolo(){
    return this->simbolo;
}
NodoHUFF * NodoHUFF::getHijoI(){
    return this->hijoI;
}
NodoHUFF * NodoHUFF::getHijoD(){
    return this->hijoD;
}

//setters
// --------------------------------------------------------------------
void NodoHUFF::setHijoI(NodoHUFF * hijoI){
    this->hijoI = hijoI;
}
void NodoHUFF::setHijoD(NodoHUFF * hijoD){
    this->hijoD = hijoD;
}

//operaciones
//--------------------------------------------------------------------