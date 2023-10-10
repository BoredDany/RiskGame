#ifndef RISKSINCOLOR_NODOHUFF_H
#define RISKSINCOLOR_NODOHUFF_H

#include <utility>
#include <cstdint>
#include <stack>

class NodoHUFF{
private:
    std::pair<int8_t, int64_t> simbolo;
    NodoHUFF * hijoI;
    NodoHUFF * hijoD;
public:
    //constructores
    NodoHUFF();
    NodoHUFF(int64_t frecuencia);
    NodoHUFF(std::pair<int8_t, int64_t> simbolo);
    //desstructores
    ~NodoHUFF();
    //getters
    std::pair<int8_t, int64_t> getSimbolo();
    NodoHUFF * getHijoI();
    NodoHUFF * getHijoD();
    //setters
    void setHijoI(NodoHUFF * hijoI);
    void setHijoD(NodoHUFF * hijoD);
    //operaciones
    bool hoja();
    bool ruta(bool raiz, std::pair<int8_t, int64_t> simbolo, std::stack<int64_t>& st, NodoHUFF * nodo, int64_t num);
};

#endif //RISKSINCOLOR_NODOHUFF_H
