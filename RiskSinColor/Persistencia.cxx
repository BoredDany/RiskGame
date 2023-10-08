#include "Persistencia.h"
#include "Simbolo.h"
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

//constructores
// --------------------------------------------------------------------
Persistencia::Persistencia(){

}

//getters
// --------------------------------------------------------------------
std::vector<Simbolo> Persistencia::getSimbolos(){
    return this->simbolos;
}
std::vector<int> Persistencia::getCodigo(){
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
void Persistencia::aggSimbolo(Simbolo simboloNuevo){
    (this->simbolos).push_back(simboloNuevo);
}
void Persistencia::setSimbolos(std::string info){

}
void Persistencia::aggCodigo(int codigoNuevo){
    (this->codigo).push_back(codigoNuevo);
}
void Persistencia::aggInfo(std::string caracterNuevo){
    (this->info).append(caracterNuevo);
}
void Persistencia::setArbol(ArbolHUFF arbol){
    this->arbol = arbol;
}

//operaciones
// --------------------------------------------------------------------
void Persistencia::escribirArchivoTxt(std::string nameFile, Partida& partida){
    //ID,nombre,color,unidades,numCartas,carta,numPaises,pais-unidades;

    std::ofstream outputfile(nameFile);
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

            int cantPaises = partida.calcularPaises(j.getId());

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

bool Persistencia::leerArchivoTxt(std::string nameFile){
    std::string line;
    std::stringstream str;
    std::ifstream inputfile (nameFile);
    if(inputfile.is_open()){
        while (getline(inputfile, line)){
            this->aggInfo(line);
        }
    }else{
        return false;
    }
    return true;
}
void Persistencia::crearArbol(){

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