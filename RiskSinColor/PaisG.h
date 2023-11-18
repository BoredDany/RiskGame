//
// Created by estudiante on 17/11/2023.
//

#ifndef RISKSINCOLOR_PAISG_H
#define RISKSINCOLOR_PAISG_H

#include <string>

class PaisG {
private:
    int id;
    std::string nombre;
    std::string continente;
    int unidades;
    int id_jugador;
public:
    //constructores
    PaisG (int id, std::string nombre, std::string continente);
    //getters
    int get_id();
    std::string get_nombre();
    std::string get_continente();
    int get_unidades();
    int get_id_jugador();
    //setters
    void set_unidades(int unidades);
    void set_id_jugador(int id_jugador);

};

#endif //RISKSINCOLOR_PAISG_H
