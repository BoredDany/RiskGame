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
    Continente(std::string nombre);
    std::string get_nombre();
    std::list<Pais> get_paises();
    void aggPais(Pais p);
    void setNombre(std::string nombre);
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
};

#endif //RISK_CONTINENTE_H
