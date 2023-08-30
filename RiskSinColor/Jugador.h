//
// Created by Estudiante on 19/08/2023.
//

#ifndef __JUGADOR__H__
#define __JUGADOR__H__
#include <iostream>
#include <list>
#include "Carta.h"

class Jugador{
private:
    int id;
    std::string color;
    std::string alias;
    int unidades;
    std::list<Carta> cartas;
public:
    Jugador();
    Jugador (int id, std::string color, std::string alias);
    void setId(int idN);
    void setColor(std::string color);
    void setAlias(std::string aliasN);
    void setUnidades(int unidadesN);
    void setCartas(std::list<Carta> cartasN);

    void agregarCarta(Carta carta);
    void quitarCarta(int idP);

    int getId();
    std::string getColor();
    std::string getAlias();
    int getUnidades();
    std::list<Carta> getCartas();
    void tresCartasCumplen(int * ganaIguales, int * ganaTodas);
    bool tieneCarta(int idP);

};

#endif
