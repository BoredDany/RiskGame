#include "Simbolo.h"
#include <string>

//constructores
//--------------------------------------------------------------------
Simbolo::Simbolo(){
    this->frecuencia = 0;
}

Simbolo::Simbolo(std::string letra, int frecuencia){
    this->letra = letra;
    this->frecuencia = frecuencia;
}

//getters
//--------------------------------------------------------------------
std::string Simbolo::getLetra(){
    return this->letra;
}

int Simbolo::getFrecuencia(){
    return this->frecuencia;
}

//setters
//--------------------------------------------------------------------
void Simbolo::setLetra(std::string letra) {
    this->letra = letra;
}

void Simbolo::setFrecuencia(int frecuencia){
    this->frecuencia = frecuencia;
}