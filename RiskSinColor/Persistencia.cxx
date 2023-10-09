#include "Persistencia.h"
#include "ArbolHUFF.h"
#include "Partida.h"
#include "Carta.h"
#include "Jugador.h"
#include "Continente.h"
#include <cstring>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdint>
#include <utility>

//constructores
// --------------------------------------------------------------------
Persistencia::Persistencia(){

}

//getters
// --------------------------------------------------------------------
std::vector<std::pair<int8_t, int64_t>> Persistencia::getSimbolos(){
    return this->simbolos;
}
std::vector<int64_t> Persistencia::getCodigo(){
    return this->codigo;
}
std::string Persistencia::getInfo(){
    return this->info;
}
ArbolHUFF Persistencia::getArbol(){
    return this->arbol;
}

//setters
// --------------------------------------------------------------------
void Persistencia::aggSimbolo(std::pair<int8_t, int64_t> simboloNuevo){
    (this->simbolos).push_back(simboloNuevo);
}
void Persistencia::aggCodigo(int64_t codigoNuevo){
    (this->codigo).push_back(codigoNuevo);
}
void Persistencia::aggInfo(std::string caracterNuevo){
    (this->info).append(caracterNuevo);
}

void Persistencia::setInfo(Partida& partida){
    int cantPaises;
    for(Jugador j : partida.get_jugadores()){
        //datos del jugador
        (this->info).append(std::to_string(j.getId()));
        (this->info).append(",");
        (this->info).append(j.getAlias());
        (this->info).append(",");
        (this->info).append(j.getColor());
        (this->info).append(",");
        (this->info).append(std::to_string(j.getUnidades()));
        (this->info).append(",");
        (this->info).append(std::to_string(j.getCartas().size()));
        (this->info).append(",");
        //cartas del jugador
        for(Carta c : j.getCartas()){
            (this->info).append(std::to_string(c.getId()));
            (this->info).append(",");
        }

        cantPaises = partida.calcularPaises(j.getId());

        (this->info).append(std::to_string(cantPaises));

        //paises ocupados por el jugador
        for(Continente c : partida.get_tablero()){
            for(Pais p : c.get_paises()){
                if(p.get_id_jugador() == j.getId()){
                    (this->info).append(",");
                    (this->info).append(std::to_string(p.get_id()));
                    (this->info).append("-");
                    (this->info).append(std::to_string(p.get_unidades()));
                }
            }
        }

        (this->info).append(";");
    }
}

void Persistencia::setArbol(ArbolHUFF arbol){
    this->arbol = arbol;
}
void Persistencia::setSimbolos() {
    std::map<int8_t, int64_t> frecuencias;
    std::vector<std::pair<int8_t, int64_t>>::iterator itV;
    std::map<int8_t, int64_t>::iterator itM;

    for (char c : this->info) {
        frecuencias[c]++;
    }

    for (itM = frecuencias.begin() ; itM != frecuencias.end() ; itM++) {
        std::pair<int8_t, int64_t> par (itM->first, itM->second);
        (this->simbolos).push_back(par);
    }

    std::sort(this->simbolos.begin(), this->simbolos.end(), [](std::pair<int8_t, int64_t> a, std::pair<int8_t, int64_t> b) {
        return a.second < b.second;
    });

/*
    for(itV = this->simbolos.begin() ; itV != this->simbolos.end() ; itV++){
        std::cout << "Letra: '"<< itV->first << "' - Frecuencia: " << itV->second << std::endl;
    }*/


}

//operaciones
// --------------------------------------------------------------------
void Persistencia::escribirArchivoTxt(std::string nameFile, Partida& partida){
    //ID,nombre,color,unidades,numCartas,carta,numPaises,pais-unidades;

    std::ofstream outputfile(nameFile);
    int cantPaises;

    if(outputfile.is_open()){
        for(Jugador j : partida.get_jugadores()){
            //datos del jugador
            outputfile << j.getId() << ","
                       << j.getAlias() << ","
                       << j.getColor() << ","
                       << j.getUnidades() << ","
                       << j.getCartas().size() << ",";
            //cartas del jugador
            for(Carta c : j.getCartas()){
                outputfile << c.getId() << ",";
            }

            cantPaises = partida.calcularPaises(j.getId());

            outputfile << cantPaises;

            //paises ocupados por el jugador
            for(Continente c : partida.get_tablero()){
                for(Pais p : c.get_paises()){
                    if(p.get_id_jugador() == j.getId()){
                        outputfile << ",";
                        outputfile << p.get_id() << "-" << p.get_unidades();
                    }
                }
            }
            outputfile << ";";
        }
    }else{
        std::cout << "No se creo archivo " << nameFile << std::endl;
    }
    outputfile.close();
}

void Persistencia::escribirArchivoBinario(std::string nameFile, Partida& partida){
    //n c1 f1 · · · cn fn w binary_code
    //n = 2 bytes : # caractereres diferentes en el archivo
    //c = 1 byte : carcater
    //f = 8 bytes : frecuencia
    //w = 8 bytes : cantidad total de caracteres del archivo
    //bynary_code : secuencia de 1s y 0s

    std::vector<std::pair<int8_t, int64_t>>::iterator itV;
    std::map<int8_t, int64_t>::iterator itM;

    int16_t n = static_cast<int16_t>(this->simbolos.size());
    std::cout << "CANTIDAD DE SIMBOLOS DIFERENTES: " << n << std::endl;

    int8_t c;
    int64_t f;

    for(itV = this->simbolos.begin() ; itV != this->simbolos.end() ; itV++){
        c = itV->first;
        f = itV->second;
        std::cout << "Letra: '"<< c << "' - Frecuencia: " << f << std::endl;
    }

    int64_t w = static_cast<int16_t>(this->info.length());
    std::cout << "CANTIDAD DE SIMBOLOS TOTAL: " << w << std::endl;

    this->arbol.armarArbol(this->simbolos);
    std::cout << "ARBOL:" << std::endl;
    this->arbol.nivelOrden();
}

bool Persistencia::leerArchivoTxt(std::string nameFile){
    std::string line;
    std::stringstream str;
    std::ifstream inputfile (nameFile);
    if(inputfile.is_open()){
        while (getline(inputfile, line)){
            this->info.append(line);
        }
    }else{
        return false;
    }
    return true;
}
void Persistencia::crearArbol(){

}

bool Persistencia::leerArchivoBin(std::string nameFile){

}

void Persistencia::recuperarPartidaConTxt(std::string nameFile, Partida& partida){
    //formato
    //ID,nombre,color,unidades,numCartas,carta,numPaises,pais-unidades;

    std::stringstream str (this->info);
    std::string word, word2, word3, nombre, color;
    int id, unidades, numCartas, numPaises, unidadesP, carta, pais;

    if((this->info).empty()){
        std::cout << "Archivo vacio o incompleto"<<std::endl;
    }else{
        while (getline( str, word,';')){

            Jugador j;
            std::stringstream ss(word);
            getline(ss,word2,',');
            id = stoi (word2);
            j.setId(id);

            getline(ss,word2,',');
            nombre = word2;
            j.setAlias(nombre);

            getline(ss,word2,',');
            color = word2;
            j.setColor(color);

            getline(ss,word2,',');
            unidades = stoi(word2);
            j.setUnidades(unidades);

            getline(ss,word2,',');
            numCartas = stoi(word2);

            for(int i = 0 ; i < numCartas ; i++){
                getline(ss,word2,',');
                carta = stoi(word2);
                Carta c = partida.obtenerCarta(carta);
                j.agregarCarta(c);
            }

            getline(ss,word2,',');
            numPaises = stoi(word2);

            for(int i = 0 ; i < numPaises ; i++){
                getline(ss,word2,',');
                std::stringstream ss(word2);
                getline(ss,word3,'-');
                pais = stoi(word3);

                getline(ss,word3,'-');
                unidadesP = stoi(word3);

                partida.ocuparPais(j.getId(),pais,unidadesP);
            }

            partida.aggJugador(j);

        }
    }
}