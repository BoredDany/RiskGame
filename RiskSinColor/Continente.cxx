#include "Continente.h"
#include <string>

Continente::Continente(std::string nombre){
    this->nombre = nombre;
}

std::string Continente::get_nombre(){
    return nombre;
}
std::list<Pais> Continente::get_paises(){
    return paises;
}
void Continente::aggPais(Pais p){
    this->paises.push_back(p);
}
void Continente::setNombre(std::string nombre){
    this->nombre = nombre;
}

void Continente::aggConexion(int pais, int vecino){
    std::list<Pais>::iterator it = paises.begin();
    for(it = paises.begin();it != paises.end();it++){
        if(pais == it->get_id()){
            it->agg_conexion(vecino);
        }
    }
}
bool Continente::lleno(){
    std::list<Pais>::iterator it = paises.begin();
    bool lleno = true;
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id_jugador() == 0){
            lleno = false;
        }
    }
    return lleno;
}

void Continente::ocuparPais(int idJugador, int idPais, int unidades){
    std::list<Pais>::iterator it = paises.begin();
    for(it = paises.begin();it != paises.end();it++){
        if(idPais == it->get_id()){
            it->set_id_jugador(idJugador);
            it->set_unidades(it->get_unidades()+unidades);
        }
    }
}

bool Continente::paisExiste(int idP){
    std::list<Pais>::iterator it = paises.begin();
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == idP){
            return true;
        }
    }
    return false;
}

bool Continente::jugadorOcupaPais(int idP, int idJ){
    std::list<Pais>::iterator it = paises.begin();
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == idP && it->get_id_jugador() == idJ){
            return true;
        }
    }
    return false;
}

bool Continente::paisVecino(int origen, int destino){
    std::list<Pais>::iterator it = paises.begin();
    bool vecino = false;
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == origen){
            vecino = it->esVecino(destino);
        }
    }
    return vecino;
}

bool Continente::quitarUnidad(int idP, bool& encontrado){
    std::list<Pais>::iterator it = paises.begin();
    bool vacio = false;
    int units = 0;
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == idP){
            encontrado = true;
            units = it->get_unidades()-1;
            if(units <= 0){
                it->set_id_jugador(0);
                it->set_unidades(units);
                vacio = true;
            }else{
                it->set_unidades(units);
            }
        }
    }
    return vacio;
}

bool Continente::intercambioPorPaises(int idJ){
    std::list<Pais>::iterator it = paises.begin();
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id_jugador() != idJ){
            return false;
        }
    }
    return true;
}

bool Continente::moverUnidad(int idP, int unidades){
    std::list<Pais>::iterator it = paises.begin();
    int res = 0;
    bool movido = false;
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == idP){
            res = it->get_unidades()-unidades;
            if(res == 0){
                it->set_unidades(it->get_unidades()-unidades);
                it->set_id_jugador(0);
                movido = true;
            }else{
                movido = true;
                it->set_unidades(it->get_unidades()-unidades);
            }

        }
    }
    return movido;
}

bool Continente::fortificar(int idP, int idJ, int unidades){
    std::list<Pais>::iterator it = paises.begin();
    bool fortificado = false;
    for(it = paises.begin();it != paises.end();it++){
        if(it->get_id() == idP){
            it->set_unidades(it->get_unidades()+unidades);
            it->set_id_jugador(idJ);
        }
    }
    return fortificado;
}