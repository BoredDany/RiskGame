#ifndef RISKSINCOLOR_ARBOLHUFF_H
#define RISKSINCOLOR_ARBOLHUFF_H

#include "NodoHUFF.h"
#include <vector>
#include <utility>
#include <cstdint>
#include <deque>
#include <unordered_map>

class ArbolHUFF{
private:
    NodoHUFF * raiz;
public:
    //constructores
    ArbolHUFF();
    ArbolHUFF(std::pair<int8_t, int64_t>& raiz);
    //desstructores
    ~ArbolHUFF();
    //getters
    NodoHUFF * getRaiz();
    //setters
    void setRaiz(NodoHUFF * raiz);
    //operaciones
    void armarArbol(std::vector<std::pair<int8_t, int64_t>> simbolos);
    void addToDeque(std::deque< NodoHUFF * >& simbolos, NodoHUFF * nuevo);
    void insertar(std::vector<std::pair<int8_t, int64_t>> simbolos);
    void codificar(std::vector<std::pair<int8_t, int64_t>> simbolos, std::vector<int64_t>& codigo);
    void construirCodigoHuffman(NodoHUFF* nodo, std::string codigo, std::unordered_map<int8_t, std::string>& CodigoHuffman);
    void decodificar(std::vector<int64_t> codigo, std::vector<std::pair<int8_t, int64_t>>& simbolos);
    //recorridos
    void nivelOrden();

};

#endif //RISKSINCOLOR_ARBOLHUFF_H
