//
// Created by Estudiante on 24/08/2023.
//

#ifndef RISK_CONTINENTE_H
#define RISK_CONTINENTE_H
#include "Pais.h"
#include<string>
#include<list>

class Continente{
private:
    std::string nombre;
    std::list<Pais> paises;
public:
    //constructores
    Continente(std::string nombre);
    //getters
    std::string get_nombre();
    std::list<Pais> get_paises();
    //setters
    void setNombre(std::string nombre);
    //operaciones
    void aggPais(Pais p);
    void aggConexion(int pais, int vecino);
    bool lleno();
    void ocuparPais(int idJugador, int idPais, int unidades);
    bool paisExiste(int idP);
    bool jugadorOcupaPais(int idP, int idJ);
    bool paisVecino(int origen, int destino);
    bool quitarUnidad(int idP, bool& encontrado);
    bool intercambioPorPaises(int idJ);
    bool moverUnidad(int idP, int unidades);
    bool fortificar(int idP, int idJ, int unidades);
    int jugadorPosee(int idJ);
};

#endif //RISK_CONTINENTE_H
