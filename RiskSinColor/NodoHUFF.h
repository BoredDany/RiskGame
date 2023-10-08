#ifndef RISKSINCOLOR_NODOHUFF_H
#define RISKSINCOLOR_NODOHUFF_H

#include "Simbolo.h"

class NodoHUFF{
private:
    Simbolo simbolo;
    NodoHUFF * hijoI;
    NodoHUFF * hijoD;
public:
    //constructores
    NodoHUFF();
    NodoHUFF(Simbolo simbolo);
    //desstructores
    ~NodoHUFF();
    //getters
    Simbolo getSimbolo();
    NodoHUFF * getHijoI();
    NodoHUFF * getHijoD();
    //setters
    void setHijoI(NodoHUFF * hijoI);
    void setHijoD(NodoHUFF * hijoD);
    //operaciones
};

#endif //RISKSINCOLOR_NODOHUFF_H
