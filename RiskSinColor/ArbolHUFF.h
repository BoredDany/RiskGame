#ifndef RISKSINCOLOR_ARBOLHUFF_H
#define RISKSINCOLOR_ARBOLHUFF_H

#include "NodoHUFF.h"
#include "Simbolo.h"
#include <vector>

class ArbolHUFF{
private:
    NodoHUFF * raiz;
public:
    //constructores
    ArbolHUFF();
    ArbolHUFF(Simbolo& raiz);
    //desstructores
    ~ArbolHUFF();
    //getters
    NodoHUFF * getRaiz();
    //setters
    void setRaiz(NodoHUFF * raiz);
    //operaciones
    void insertar(std::vector<Simbolo> simbolos);
    void codificar(std::vector<Simbolo> simbolos, std::vector<int> codigo);
    void decodificar(std::vector<int> codigo, std::vector<Simbolo> simbolos);

};

#endif //RISKSINCOLOR_ARBOLHUFF_H
