//
// Created by Estudiante on 23/08/2023.
//
#include <cstring>
#include <string>
#include <list>
#include <iostream>
#include "Pais.h"

Pais::Pais(int id, std::string nombre,  std::string continente) {
    this->id = id;
    this->nombre = nombre;
    this->continente = continente;
    this->id_jugador = 0;
    this->unidades = 0;
}

int Pais::get_id() {
    return id;
}

std::string Pais::get_nombre() {
    return nombre;
}

std::string Pais::get_continente() {
    return continente;
}

int Pais::get_unidades() {
    return unidades;
}

int Pais::get_id_jugador() {
    return id_jugador;
}

std::list<int> Pais::get_conexiones() {
    return conexiones;
}

void Pais::set_unidades(int unidades) {
    this->unidades = unidades;
}

void Pais::set_id_jugador(int id_jugador) {
    this->id_jugador = id_jugador;
}

void Pais::agg_conexion(int conexion) {
    this->conexiones.push_back(conexion);
}

bool Pais::esVecino(int idP){
    std::list<int>::iterator it = conexiones.begin();
    for( it = conexiones.begin();  it != conexiones.end(); it++){
        if(*it == idP){
            return true;
        }
    }
    return false;
}