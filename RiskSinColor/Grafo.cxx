//
// Created by estudiante on 17/11/2023.
//

#include "Grafo.h"
#include "PaisG.h"
#include "Carta.h"
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <climits>
#include <limits>
#include <set>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

//constructors
Grafo::Grafo() {

}

//----------------------------------------------------------------------------------------------
//getters

std::vector < PaisG > Grafo::getPaises(){
    return this->paises;
}

std::vector < std::list < std::pair < int, int > > > Grafo::getEdges(){
    return this->conexiones;
}

//----------------------------------------------------------------------------------------------
//setters

void Grafo::setVertices(std::vector < PaisG >& vertices){
    this->paises = vertices;
}

void Grafo::setEdges(std::vector < std::list < std::pair < int, int > > >& edges){
    this->conexiones = edges;
}

//----------------------------------------------------------------------------------------------
//inserting

bool Grafo::addVertex(PaisG& vertex){
    int vertexFound = searchVertice(vertex.get_id());
    if(vertexFound == -1){
        this->paises.push_back(vertex);
        this->conexiones.push_back(std::list<std::pair<int, int>>());
        return true;
    }
    return false;
}

bool Grafo::addEdge(PaisG& origin, PaisG& destination, int cost){
    int destinationIndex = searchVertice(destination.get_id());
    int originIndex = searchVertice(origin.get_id());

    if(!searchEdge(origin.get_id(), destination.get_id()) && originIndex != -1 && destinationIndex != -1){
        std::pair < int, int > newEdge (destinationIndex, cost);
        this->conexiones[originIndex].push_back(newEdge);
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------

//searching
int Grafo::searchVertice(int vertex){
    int vertexFound = -1;
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == vertex){
            vertexFound = i;
            break;
        }
    }
    return vertexFound;
}

bool Grafo::searchEdge(int origin, int destination){
    typename  std::list < std::pair < int, int > >::iterator itL;
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(destinationIndex != -1 && originIndex != -1){
        itL = this->conexiones[originIndex].begin();
        for(itL = this->conexiones[originIndex].begin() ; itL != this->conexiones[originIndex].end() ; itL++){
            if(itL->first == destinationIndex){
                return true;
            }
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------------
//tours

void Grafo::plain(){
    std::cout << "PAISES" << std::endl;
    for(int i = 0 ; i < this->paises.size() ; i++){
        std::cout << this->paises[i].get_id() << " ; ";
    }
}

void Grafo::bfs(){
    std::vector<bool> visited(this->paises.size(), false);
    std::queue<int> vertexQueue;

    for (int i = 0; i < this->paises.size(); i++) {
        if (!visited[i]) {
            doBFS(i, visited, vertexQueue);
        }
    }
}

void Grafo::doBFS(int startVertex, std::vector<bool>& visited, std::queue<int>& vertexQueue){
    visited[startVertex] = true;
    vertexQueue.push(startVertex);

    while (!vertexQueue.empty()) {
        int currentVertex = vertexQueue.front();
        vertexQueue.pop();

        std::cout << this->paises[currentVertex].get_id() << ", ";

        typename  std::list < std::pair < int, int > >::iterator itL;
        itL = this->conexiones[currentVertex].begin();

        for( ; itL != this->conexiones[currentVertex].end() ; itL++){
            int neighbor = (*itL).first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                vertexQueue.push(neighbor);
            }
        }
    }
}

void Grafo::dfs(){
    std::vector<bool> visited(this->paises.size(), false);

    for (int i = 0; i < this->paises.size(); ++i) {
        if (!visited[i]) {
            doDFS(i, visited);
        }
    }
}

void Grafo::doDFS(int currentVertex, std::vector<bool>& visited) {
    visited[currentVertex] = true;
    std::cout << this->paises[currentVertex].get_id() << ", ";

    typename  std::list < std::pair < int, int > >::iterator itL;
    itL = this->conexiones[currentVertex].begin();

    for ( ; itL != this->conexiones[currentVertex].end(); itL++) {
        int neighbor = (*itL).first;
        if (!visited[neighbor]) {
            doDFS(neighbor, visited);
        }
    }
}

void Grafo::showEdges(){
    typename  std::list < std::pair < int, int > >::iterator itL;

    for(int i = 0 ; i < this->conexiones.size() ; i++){
        std::cout << "\n" << this->paises[i].get_id() << ": ";
        std::list < std::pair < int, int > > auxEdges = this->conexiones[i];
        itL = auxEdges.begin();
        for(itL = auxEdges.begin() ; itL != auxEdges.end() ; itL++){
            std::cout << "(" << this->paises[(*itL).first].get_id() << "," << (*itL).second << ") ";
        }
        std::cout << std::endl;
    }

}

//----------------------------------------------------------------------------------------------

//inicializacion
bool Grafo::paisLleno(int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais && this->paises[i].get_unidades() == 0){
            return false;
        }
    }
    return true;
}

void Grafo::ocuparPais(int idJugador, int idPais, int unidades){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            this->paises[i].set_id_jugador(idJugador);
            this->paises[i].set_unidades(this->paises[i].get_unidades()+unidades);
        }
    }
}

bool Grafo::lleno(){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == 0){
            return false;
        }
    }
    return true;
}

//----------------------------------------------------------------------------------------------
//turno

int Grafo::calcularPaisesJugador(int idJugador){
    int paises = 0;
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador){
            paises++;
        }
    }
    return paises;
}

bool Grafo::jugadorPuedeUbicar(int idJugador){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador || this->paises[i].get_id_jugador() == 0){
            return true;
        }
    }
    return false;
}

bool Grafo::paisFortificable(int idJugador, int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            if(this->paises[i].get_id_jugador() == idJugador || this->paises[i].get_id_jugador() == 0){
                return true;
            }
        }
    }
    return false;
}

int Grafo::intercambioPaises(int idJugador, std::list<std::string>& continentes){
    int nAfrica = 0, nOceania = 0, nAsia = 0, nEuropa = 0, nLatam = 0, nNortAmerica = 0,
            jAfrica = 0, jOceania = 0, jAsia = 0, jEuropa = 0, jLatam = 0, jNortAmerica = 0, gana = 0;

    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_continente() == "Africa"){
            nAfrica++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jAfrica++;
            }
        }
        if(this->paises[i].get_continente() == "Oceania"){
            nOceania++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jOceania++;
            }
        }
        if(this->paises[i].get_continente() == "Asia"){
            nAsia++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jAsia++;
            }
        }
        if(this->paises[i].get_continente() == "Europa"){
            nEuropa++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jEuropa++;
            }
        }
        if(this->paises[i].get_continente() == "Sur America"){
            nLatam++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jLatam++;
            }
        }
        if(this->paises[i].get_continente() == "Norte America"){
            nNortAmerica++;
            if(this->paises[i].get_id_jugador() == idJugador){
                jNortAmerica++;
            }
        }
    }

    if(nAfrica == jAfrica){gana+=3; continentes.push_back("Africa");}
    if(nOceania == jOceania){gana+=2; continentes.push_back("Oceania");}
    if(nAsia == jAsia){gana+=7; continentes.push_back("Asia");}
    if(nEuropa == jEuropa){gana+=5; continentes.push_back("Europa");}
    if(nLatam == jLatam){gana+=2; continentes.push_back("Sur America");}
    if(nNortAmerica == jNortAmerica){gana+=5; continentes.push_back("Norte America");}

    return gana;
}

bool Grafo::jugadorOcupaPais(int idJugador, int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais && this->paises[i].get_id_jugador() == idJugador){
            return true;
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------------
//atacar

bool Grafo::puedeAtacar(int idJugador){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador){
            int indexPais = searchVertice(this->paises[i].get_id());
            for(typename std::list < std::pair <int,int> >::iterator it = this->conexiones[indexPais].begin();
                    it != this->conexiones[indexPais].end(); it++){
                if(paisAtacable(idJugador, this->paises[(*it).first].get_id())){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::paisAtacable(int idJugador, int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            if(this->paises[i].get_id_jugador() != idJugador && this->paises[i].get_id_jugador() != 0){
                return true;
            }
        }
    }
    return false;
}

bool Grafo::origenAptoParaAtaque(int idJugador, int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            int indexPais = searchVertice(this->paises[i].get_id());
            for(typename std::list < std::pair <int,int> >::iterator it = this->conexiones[indexPais].begin();
                    it != this->conexiones[indexPais].end(); it++){
                if(paisAtacable(idJugador, this->paises[(*it).first].get_id())){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::quitarUnidad(int idPais){
    bool vacio = false;
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            if(this->paises[i].get_id() == idPais){
                this->paises[i].set_unidades(this->paises[i].get_unidades()-1);
                if(this->paises[i].get_unidades() <= 0){
                    this->paises[i].set_id_jugador(0);
                    vacio = true;
                }
                break;
            }
        }
    }
    return vacio;
}

//----------------------------------------------------------------------------------------------
//fortificar

bool Grafo::puedeFortificar(int idJugador){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador){
            for(typename std::list < std::pair <int,int> >::iterator it = this->conexiones[i].begin();
                    it != this->conexiones[i].end(); it++){
                if(this->paises[(*it).first].get_id_jugador() == idJugador || this->paises[(*it).first].get_id_jugador() == 0){
                    return true;
                }
            }
        }
    }
    return false;
}

bool Grafo::unidadesSuficientes(int idJugador, int idPais, int unidades){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador && this->paises[i].get_unidades() >= unidades){
            return true;
        }
    }
    return false;
}

bool Grafo::aptoParaFortificar(int idJugador, int idPais){
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id() == idPais){
            for(typename std::list < std::pair <int,int> >::iterator it = this->conexiones[i].begin();
                    it != this->conexiones[i].end(); it++){
                if(paisFortificable(idJugador, this->paises[(*it).first].get_id())){
                    return true;
                }
            }
        }
    }
    return false;
}

void Grafo::moverUnidades(int idJugador, int origen, int destino, int unidadesM){
    int indexOrigen = searchVertice(origen);
    int indexDestino = searchVertice(destino);

    //restar del origen
    this->paises[indexOrigen].set_unidades(this->paises[indexOrigen].get_unidades()-unidadesM);
    if(this->paises[indexOrigen].get_unidades() <= 0){
        this->paises[indexOrigen].set_id_jugador(0);
    }

    //sumar al destino
    this->paises[indexDestino].set_unidades(this->paises[indexDestino].get_unidades()+unidadesM);
    this->paises[indexDestino].set_id_jugador(idJugador);

}

//----------------------------------------------------------------------------------------------
//algoritmos

void Grafo::updateCosts(){
    for(int i = 0 ; i < this->paises.size() ; i++){
        int costo = this->paises[i].get_unidades();
        for(int j = 0 ; j < this->conexiones.size() ; j++){
            for(typename std::list < std::pair <int,int> >::iterator it = this->conexiones[j].begin(); it != this->conexiones[j].end(); it++){
                if(this->paises[i].get_id() == this->paises[(*it).first].get_id()){
                    (*it).second = costo;
                }
            }
        }
    }
}

void Grafo::conquistaMasBarata (int idJugador) {

    int n = this->paises.size();
    updateCosts();
    std::list < std::vector<int> > distancesDij;
    std::list < std::vector<std::list<int>> > pathsDij;

    int bestDistance = std::numeric_limits<int>::max();
    for(int i = 0 ; i < this->paises.size() ; i++){
        if(this->paises[i].get_id_jugador() == idJugador){
            std::vector<int> distance(n, std::numeric_limits<int>::max());
            std::vector<std::list<int>> paths(n); // Vector de listas para almacenar los caminos
            int distanceP = dijkstra(this->paises[i].get_id(), idJugador, distance, paths);
            distancesDij.push_back(distance);
            pathsDij.push_back(paths);
            if(distanceP <= bestDistance){
                bestDistance = distanceP;
            }
        }
    }
    std::cout << "Conquista(s) mas barata(s) para el jugador " << idJugador << ":" << std::endl;

    typename std::list < std::vector<std::list<int>> >::iterator itP = pathsDij.begin();

    for(typename std::list < std::vector<int> >::iterator itD = distancesDij.begin() ; itD != distancesDij.end(); itD++, itP++){
        for(int i = 0 ; i < n ; i++){
            if((*itD)[i] == bestDistance){
                typename std::list<int>::iterator itR = (*itP)[i].begin();

                std::cout << "Conquistar el territorio: " << this->paises[i].get_id() <<
                          " desde el territorio: " << this->paises[(*itR)].get_id() << " derrotando " << (*itD)[i] << " tropa(s)" << std::endl;
                std::cout << "Para conquistar el territorio  " << this->paises[i].get_id() << " debe pasar por los territorios:";

                for(itR = (*itP)[i].begin() ; itR != (*itP)[i].end(); itR++){
                    std::cout << this->paises[*itR].get_id() << " -> ";
                }
                /*for (int node : (*itP)[i]) {
                    std::cout << this->paises[node].get_id() << " -> ";
                }*/
                std::cout << this->paises[i].get_id() << std::endl;
            }
        }
    }
}


int Grafo::dijkstra(int initial, int idJugador, std::vector<int>& distance, std::vector<std::list<int>>& paths) {
    int n = this->paises.size();
    int bestDistance = std::numeric_limits<int>::max();
    std::vector<bool> visited(n, false);

    // Encontrar el índice del vértice inicial
    int startIndex = searchVertice(initial);

    if (startIndex == -1) {
        std::cerr << "Error: Vértice inicial no encontrado." << std::endl;
        return -1;
    }

    distance[startIndex] = 0;
    int unidadesJugador = this->paises[startIndex].get_unidades();

    // Cola de prioridad para almacenar vértices y sus distancias
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, startIndex});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visited[u]) {
            continue; // Saltar si el vértice ya fue visitado
        }

        visited[u] = true;

        // Explorar todos los vecinos del vértice seleccionado 'u'
        for (typename std::list<std::pair<int,int>>::iterator it = this->conexiones[u].begin(); it != this->conexiones[u].end(); it++) {
            int v = (*it).first;
            int edgeCost = (*it).second;

            if (!visited[v] && distance[u] + edgeCost < distance[v]) {
                distance[v] = distance[u] + edgeCost;
                pq.push({distance[v], v});

                // Actualizar el camino hacia 'v' con la información de 'u'
                paths[v] = paths[u]; // Copiar el camino desde el nodo inicial hasta 'u'
                paths[v].push_back(u); // Agregar 'u' al camino hacia 'v'
            }
        }
    }

    //Find best path based on distance
    for (int i = 0; i < n; ++i) {
        if (i != startIndex && this->paises[i].get_id_jugador() != idJugador && distance[i] < bestDistance && unidadesJugador >= distance[i]) {
            bestDistance = distance[i];
        }
    }

    return bestDistance;
}
