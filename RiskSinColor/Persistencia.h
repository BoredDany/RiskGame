#ifndef RISKSINCOLOR_PERSISTENCIA_H
#define RISKSINCOLOR_PERSISTENCIA_H

#include "Simbolo.h"
#include "ArbolHUFF.h"
#include "Partida.h"
#include <vector>
#include <string>

class Persistencia{
private:
    std::vector<Simbolo> simbolos;
    std::vector<int> codigo;
    std::string info;
    ArbolHUFF arbol;
public:
    //constructores
    Persistencia();
    //getters
    std::vector<Simbolo> getSimbolos();
    std::vector<int> getCodigo();
    std::string getInfo();
    ArbolHUFF getArbol();
    //setters
    void aggSimbolo(Simbolo simboloNuevo);
    void setSimbolos(std::string info);
    void aggCodigo(int codigoNuevo);
    void aggInfo(std::string caracterNuevo);
    void setArbol(ArbolHUFF arbol);
    //operaciones
    void escribirArchivoTxt(std::string nameFile, Partida& partida);
    bool leerArchivoTxt(std::string nameFile);
    void crearArbol();
    void recuperarPartidaConTxt(std::string nameFile, Partida& partida);

};

#endif //RISKSINCOLOR_PERSISTENCIA_H
