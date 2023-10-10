#include "NodoHUFF.h"

#include <utility>
#include <cstdint>
#include <string>
#include <stack>

//constructores
//--------------------------------------------------------------------
NodoHUFF::NodoHUFF(){
    this->hijoI = nullptr;
    this->hijoD = nullptr;
}
NodoHUFF::NodoHUFF(std::pair<int8_t, int64_t> simbolo){
    this->simbolo = simbolo;
    this->hijoI = nullptr;
    this->hijoD = nullptr;
}
NodoHUFF::NodoHUFF(int64_t frecuencia){
    this->hijoI = nullptr;
    this->hijoD = nullptr;
    std::string vacio = " ";
    std::pair<int8_t, int64_t> dato (vacio[0], frecuencia);
    this->simbolo = dato;
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
std::pair<int8_t, int64_t>  NodoHUFF::getSimbolo(){
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
bool NodoHUFF::hoja() {
    return this->hijoD == nullptr && this->hijoI == nullptr;
}

bool NodoHUFF::ruta(bool raiz, std::pair<int8_t, int64_t> simbolo, std::stack<int64_t>& st, NodoHUFF * nodo, int64_t num){
    int64_t izq = 0, der = 1;
    if(nodo == nullptr){
        return false;
    }
    if(!raiz){
        st.push(num);
    }
    if(nodo->simbolo.first == simbolo.first){
        return true;
    }
    if(ruta(false, simbolo, st, nodo->hijoI, izq) || ruta(false, simbolo, st, nodo->hijoD, der)){
        return true;
    }
    if(!raiz){
        st.pop();
    }
    return false;
}