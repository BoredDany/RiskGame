#ifndef RISKSINCOLOR_ARBOLHUFF_H
#define RISKSINCOLOR_ARBOLHUFF_H

#include "NodoHUFF.h"
#include <vector>
#include <utility>
#include <cstdint>
#include <deque>
#include <stack>
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
    void liberarArbol(NodoHUFF * raiz);
    //getters
    NodoHUFF * getRaiz();
    //setters
    void setRaiz(NodoHUFF * raiz);
    //operaciones
    void armarArbol(std::vector<std::pair<int8_t, int64_t>> simbolos);
    void addToDeque(std::deque< NodoHUFF * >& simbolos, NodoHUFF * nuevo);
    void codificar(std::pair<int8_t, int64_t> simbolo, std::stack<int64_t>& st, std::vector<int64_t>& codigo);
    void decodificar(std::vector<int64_t> codigo, std::string& info);
    //recorridos
    void nivelOrden();
};

#endif //RISKSINCOLOR_ARBOLHUFF_H
