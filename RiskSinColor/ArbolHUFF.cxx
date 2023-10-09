#include "ArbolHUFF.h"
#include "NodoHUFF.h"
#include <iostream>
#include <utility>
#include <cstdint>
#include <vector>
#include <deque>
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
// Función para ordenar los nodos por frecuencia (de menor a mayor)
void ArbolHUFF::insertar(std::vector<std::pair<int8_t, int64_t>> simbolos) {
    std::vector<NodoHUFF*> nodos;

    for (const std::pair<int8_t, int64_t>& par : simbolos) {
        NodoHUFF* nuevo = new NodoHUFF(par);
        nodos.push_back(nuevo);
    }

    // Construir el árbol combinando nodos hasta que quede solo uno
    while (nodos.size() > 1) {
        // Ordenar la lista de nodos por frecuencia (de menor a mayor)
        std::sort(nodos.begin(), nodos.end(), [](NodoHUFF* a, NodoHUFF* b) {
            return a->getSimbolo().second > b->getSimbolo().second;
        });

        // Tomar los dos nodos con las frecuencias más bajas
        NodoHUFF* izquierdo = nodos[0];
        NodoHUFF* derecho = nodos[1];

        // Crear un nuevo nodo interno que combine los dos nodos anteriores
        NodoHUFF* interno = new NodoHUFF(std::make_pair(-1, izquierdo->getSimbolo().second + derecho->getSimbolo().second));
        interno->setHijoI(izquierdo);
        interno->setHijoD(derecho);

        // Eliminar los dos nodos anteriores de la lista y agregar el nuevo nodo interno
        nodos.erase(nodos.begin(), nodos.begin() + 2);
        nodos.push_back(interno);
    }

    this->raiz = nodos[0];  // Establecer la raíz del árbol
}

// Codificar un mensaje utilizando un árbol de Huffman
void ArbolHUFF::codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t>& codigo) {
    if (raiz == nullptr || simbolos.empty()) {
        return;
    }

    std::unordered_map<int8_t, std::string> CodigoHuffman;
    construirCodigoHuffman(raiz, "", CodigoHuffman);

    for (const auto& simbolo : simbolos) {
        int8_t caracter = simbolo.first;
        if (CodigoHuffman.find(caracter) != CodigoHuffman.end()) {
            std::string codigoCaracter = CodigoHuffman[caracter];
            for (char bit : codigoCaracter) {
                if (bit == '0') {
                    codigo.push_back(0);
                } else {
                    codigo.push_back(1);
                }
            }
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

        std::cout << "DEQUE"<< std::endl;
        for(NodoHUFF * n : simbolosD){
            std::cout << n->getSimbolo().first << " - " << n->getSimbolo().second << std::endl;
        }
    }

    this->raiz = simbolosD.front();
}

// Construir el código de Huffman
void ArbolHUFF::construirCodigoHuffman(NodoHUFF* nodo, std::string codigo, std::unordered_map<int8_t, std::string>& CodigoHuffman) {
    if (!nodo->getHijoI() && !nodo->getHijoD()) {
        CodigoHuffman[nodo->getSimbolo().first] = codigo;
    }

    if (nodo->getHijoI()) {
        construirCodigoHuffman(nodo->getHijoI(), codigo + "0", CodigoHuffman);
    }

    if (nodo->getHijoD()) {
        construirCodigoHuffman(nodo->getHijoD(), codigo + "1", CodigoHuffman);
    }
}


// Decodificar un mensaje utilizando un árbol de Huffman
void ArbolHUFF::decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>>& simbolos) {
    if (raiz == nullptr || codigo.empty()) {
        return;
    }

    NodoHUFF* nodoActual = raiz;
    for (int64_t bit : codigo) {
        if (bit == 0 && nodoActual->getHijoI()) {
            nodoActual = nodoActual->getHijoI();
        } else if (bit == 1 && nodoActual->getHijoD()) {
            nodoActual = nodoActual->getHijoD();
        }

        if (!nodoActual->getHijoI() && !nodoActual->getHijoD()) {
            simbolos.push_back(nodoActual->getSimbolo());
            nodoActual = raiz;  // Reiniciar desde la raíz
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
