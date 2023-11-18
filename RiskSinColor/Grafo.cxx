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

std::vector < PaisG > Grafo::getVertices(){
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

void Grafo::readVertices(std::list < Carta > cartas){
    for(std::list < Carta >::iterator it = cartas.begin() ; it != cartas.end() ; it++){
        PaisG pais((*it).getId(), (*it).getPais(), (*it).getContinente());
        this->addVertex(pais);
    }
}

void Grafo::readConnections(std::string archivo){
    std::ifstream file (archivo);
    std::string line, word;

    if(file.is_open()){
        while(getline(file,line,'\n')){
            std::stringstream ss(line);
            getline(ss,word,'-');
            int idPais = stoi(word);
            PaisG pais = this->paises[searchVertice(idPais)];
            while(getline(ss,word,';')){
                int idVecino = stoi(word);
                PaisG vecino = this->paises[searchVertice(idVecino)];
                this->addEdge(pais, vecino, 0);
            }
        }
    }else{
        std::cout<<"Archivo de conexiones no leido"<<std::endl;
    }
    file.close();
}