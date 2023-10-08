#include "ArbolHUFF.h"
#include "Simbolo.h"

//constructores
// --------------------------------------------------------------------
ArbolHUFF::ArbolHUFF(){
    this->raiz = nullptr;
}
ArbolHUFF::ArbolHUFF(Simbolo& raiz){
    NodoHUFF * nuevo = new NodoHUFF(raiz);
    this->raiz = nuevo;
}

//desstructores
// --------------------------------------------------------------------
ArbolHUFF::~ArbolHUFF(){
    this->raiz = nullptr;
};

//getters
// --------------------------------------------------------------------

NodoHUFF * ArbolHUFF::getRaiz(){
    return this->raiz;
}

//setters
// --------------------------------------------------------------------
void ArbolHUFF::setRaiz(NodoHUFF * raiz){
    this->raiz = raiz;
}

//operaciones
// --------------------------------------------------------------------
void ArbolHUFF::insertar(std::vector<Simbolo> simbolos){

}
void ArbolHUFF::codificar(std::vector<Simbolo> simbolos, std::vector<int> codigo){

}
void ArbolHUFF::decodificar(std::vector<int> codigo, std::vector<Simbolo> simbolos){

}