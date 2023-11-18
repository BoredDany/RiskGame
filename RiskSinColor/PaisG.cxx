//
// Created by estudiante on 17/11/2023.
//

#include <cstring>
#include <string>
#include <list>
#include <iostream>
#include "PaisG.h"

//constructores
//--------------------------------------------------------------------
PaisG::PaisG(int id, std::string nombre,  std::string continente) {
    this->id = id;
    this->nombre = nombre;
    this->continente = continente;
    this->id_jugador = 0;
    this->unidades = 0;
}

//getters
//--------------------------------------------------------------------
int PaisG::get_id() {
    return this->id;
}

std::string PaisG::get_nombre() {
    return this->nombre;
}

std::string PaisG::get_continente() {
    return this->continente;
}

int PaisG::get_unidades() {
    return this->unidades;
}

int PaisG::get_id_jugador() {
    return this->id_jugador;
}

//setters
//--------------------------------------------------------------------
void PaisG::set_unidades(int unidades) {
    this->unidades = unidades;
}

void PaisG::set_id_jugador(int id_jugador) {
    this->id_jugador = id_jugador;
}