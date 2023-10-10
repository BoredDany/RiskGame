#include "ArbolHUFF.h"
#include "NodoHUFF.h"
#include <iostream>
#include <utility>
#include <cstdint>
#include <vector>
#include <deque>
#include <stack>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <queue>
#include <unordered_map>

//constructores
// --------------------------------------------------------------------
ArbolHUFF::ArbolHUFF(){
    this->raiz = nullptr;
}
ArbolHUFF::ArbolHUFF(std::pair<int8_t, int64_t>& raiz){
    NodoHUFF * nuevo = new NodoHUFF(raiz);
    this->raiz = nuevo;
}

//desstructores
// --------------------------------------------------------------------
ArbolHUFF::~ArbolHUFF(){
    this->raiz = nullptr;
}
void ArbolHUFF::liberarArbol(NodoHUFF * raiz){
    if(raiz == nullptr){
        return;
    }
    delete raiz;
    liberarArbol(raiz->getHijoI());
    liberarArbol(raiz->getHijoD());
}

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

// Codificar un mensaje utilizando un árbol de Huffman
void ArbolHUFF::codificar(std::pair<int8_t, int64_t> simbolo, std::stack<int64_t>& st, std::vector<int64_t>& codigo) {
    if(this->raiz == nullptr){
        return;
    }else{
        int64_t i = -1;
        this->raiz->ruta(true, simbolo, st, this->raiz, i);
        std::stack<int64_t> rutaCorrecta;
        while(!st.empty()){
            rutaCorrecta.push(st.top());
            st.pop();
        }
        while(!rutaCorrecta.empty()){
            codigo.push_back(rutaCorrecta.top());
            rutaCorrecta.pop();
        }
    }

}

void ArbolHUFF::addToDeque(std::deque< NodoHUFF * >& simbolos, NodoHUFF * nuevo){
    std::deque< NodoHUFF * >::iterator it = simbolos.begin();
    while(it != simbolos.end() && (*it)->getSimbolo().second <= nuevo->getSimbolo().second){
        it++;
    }
    simbolos.insert(it, nuevo);
}

void ArbolHUFF::armarArbol(std::vector<std::pair<int8_t, int64_t>> simbolos) {

    std::deque< NodoHUFF * > simbolosD;
    int64_t nulo = 0;

    for(std::pair<int8_t, int64_t> s : simbolos){
        std::pair<int8_t, int64_t> p (s.first, s.second);
        NodoHUFF * n = new NodoHUFF(p);
        simbolosD.push_back(n);
    }

    while(simbolosD.size() > 1){
        //sacar 2 menores
        NodoHUFF * izq = simbolosD.front();
        simbolosD.pop_front();
        NodoHUFF * der = simbolosD.front();
        simbolosD.pop_front();

        //crear nodo intermedio
        NodoHUFF * intm = new NodoHUFF(izq->getSimbolo().second + der->getSimbolo().second);
        intm->setHijoI(izq);
        intm->setHijoD(der);

        addToDeque(simbolosD, intm);
    }
    this->raiz = simbolosD.front();
}

// Decodificar un mensaje utilizando un árbol de Huffman
void ArbolHUFF::decodificar(std::vector<int64_t> codigo, std::string& info) {
    if (raiz == nullptr || codigo.empty()) {
        return;
    }

    NodoHUFF* nodoActual = this->raiz;

    for (int64_t bit : codigo) {
        if (bit == 0 && nodoActual->getHijoI()) {
            nodoActual = nodoActual->getHijoI();
        } else if (bit == 1 && nodoActual->getHijoD()) {
            nodoActual = nodoActual->getHijoD();
        }

        if (!nodoActual->getHijoI() && !nodoActual->getHijoD()) {
            info.push_back(static_cast<char>(nodoActual->getSimbolo().first));
            nodoActual = this->raiz;  // Reiniciar desde la raíz
        }
    }
}

void ArbolHUFF::nivelOrden() {
    std::queue < NodoHUFF * > cola;
    NodoHUFF* nodo = this->raiz;

    while(nodo != nullptr){
        std::cout << "letra:" << nodo->getSimbolo().first << "  frecuencia: " << nodo->getSimbolo().second << std::endl;
        if(nodo->getHijoI() != nullptr){
            cola.push(nodo->getHijoI());
        }
        if(nodo->getHijoD() != nullptr){
            cola.push(nodo->getHijoD());
        }
        if(!cola.empty()){
            nodo = cola.front();
            cola.pop();
        }
        else{
            nodo = nullptr;
        }
    }
}
