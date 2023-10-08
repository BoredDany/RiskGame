#ifndef RISKSINCOLOR_SIMBOLO_H
#define RISKSINCOLOR_SIMBOLO_H

#include <string>

class Simbolo{

private:
    std::string letra;
    int frecuencia;

public:
    //constructores
    Simbolo();
    Simbolo(std::string letra, int frecuencia);
    //getters
    std::string getLetra();
    int getFrecuencia();
    //setters
    void setLetra(std::string letra);
    void setFrecuencia(int frecuencia);
};
#endif //RISKSINCOLOR_SIMBOLO_H
