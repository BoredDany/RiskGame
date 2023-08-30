//
// Created by Estudiante on 23/08/2023.
//

#ifndef RISK_TERRITORIO_H
#define RISK_TERRITORIO_H
#include<string>
#include<list>

class Pais{
private:
    int id;
    std::string nombre;
    std::string continente;
    int unidades;
    int id_jugador;
    std::list<int> conexiones;
public:
    Pais(int id, std::string nombre, std::string continente);
    int get_id();
    std::string get_nombre();
    std::string get_continente();
    int get_unidades();
    int get_id_jugador();
    std::list<int> get_conexiones();
    void set_unidades(int unidades);
    void set_id_jugador(int id_jugador);
    void agg_conexion(int conexion);
    bool esVecino(int idP);
};
#endif //RISK_TERRITORIO_H
