//
// Created by estudiante on 17/11/2023.
//

#include "Grafo.h"
#include "PaisG.h"
#include <vector>
#include <list>
#include <utility>
#include <iostream>
#include <queue>
#include <climits>
#include <limits>
#include <set>
#include <algorithm>

//constructors

Graph::Graph() {

}

//----------------------------------------------------------------------------------------------

//getters

std::vector < Pais > Graph::getVertices(){
    return this->vertices;
}

std::vector < std::list < std::pair < int, int > > > Graph::getEdges(){
    return this->edges;
}

//----------------------------------------------------------------------------------------------

//setters

void Graph::setVertices(std::vector < Pais >& vertices){
    this->vertices = vertices;
}

void Graph::setEdges(std::vector < std::list < std::pair < int, int > > >& edges){
    this.edges = edges;
}

//----------------------------------------------------------------------------------------------

//inserting

bool Graph::addVertex(Pais& vertex){
    int vertexFound = searchVertice(vertex);
    if(vertexFound == -1){
        this->vertices.push_back(vertex);
        this->edges.push_back(std::list<std::pair<int, int>>());
        return true;
    }
    return false;
}

bool Graph::addEdge(Pais& origin, Pais& destination, int cost){
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(!searchEdge(origin, destination) && originIndex != -1 && destinationIndex != -1){
        std::pair < int, int > newEdge (destinationIndex, cost);
        this->edges[originIndex].push_back(newEdge);
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------

//searching

int Graph::searchVertice(Pais& vertex){
    int vertexFound = -1;
    for(int i = 0 ; i < this->vertices.size() ; i++){
        if(this->vertices[i] == vertex){
            vertexFound = i;
            break;
        }
    }
    return vertexFound;
}

bool Graph::searchEdge(Pais& origin, Pais& destination){
    typename  std::list < std::pair < int, int > >::iterator itL;
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(destinationIndex != -1 && originIndex != -1){
        itL = this->edges[originIndex].begin();
        for(itL = this->edges[originIndex].begin() ; itL != this->edges[originIndex].end() ; itL++){
            if(itL->first == destinationIndex){
                return true;
            }
        }
    }
    return false;
}

//----------------------------------------------------------------------------------------------
//general info

int Graph::numVertices(){
    return this->vertices.size();
}

int Graph::numEdges(){
    typename  std::list < std::pair < int, C > >::iterator itL;
    int numEdges = 0;

    for(int i = 0 ; i < this->edges.size() ; i++){
        std::list < std::pair < int, C > > auxEdges = this->edges[i];
        itL = auxEdges.begin();
        for(itL = auxEdges.begin() ; itL != auxEdges.end() ; itL++){
            numEdges++;
        }
    }
    return numEdges;
}

//----------------------------------------------------------------------------------------------
//tours
void Graph::plain(){
    for(int i = 0 ; i < this->vertices.size() ; i++){
        std::cout << this->vertices[i] << " ; ";
    }
}

void Graph::bfs(){
    std::vector<bool> visited(this->vertices.size(), false);
    std::queue<int> vertexQueue;

    for (int i = 0; i < this->vertices.size(); i++) {
        if (!visited[i]) {
            doBFS(i, visited, vertexQueue);
        }
    }
}

void Graph::doBFS(int startVertex, std::vector<bool>& visited, std::queue<int>& vertexQueue){
    visited[startVertex] = true;
    vertexQueue.push(startVertex);

    while (!vertexQueue.empty()) {
        int currentVertex = vertexQueue.front();
        vertexQueue.pop();

        std::cout << this->vertices[currentVertex] << ", ";

        typename  std::list < std::pair < int, int > >::iterator itL;
        itL = this->edges[currentVertex].begin();

        for( ; itL != this->edges[currentVertex].end() ; itL++){
            int neighbor = (*itL).first;
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                vertexQueue.push(neighbor);
            }
        }
    }
}

void Graph::dfs(){
    std::vector<bool> visited(this->vertices.size(), false);

    for (int i = 0; i < this->vertices.size(); ++i) {
        if (!visited[i]) {
            doDFS(i, visited);
        }
    }
}

void Graph::doDFS(int currentVertex, std::vector<bool>& visited) {
    visited[currentVertex] = true;
    std::cout << this->vertices[currentVertex] << ", ";

    typename  std::list < std::pair < int, int > >::iterator itL;
    itL = this->edges[currentVertex].begin();

    for ( ; itL != this->edges[currentVertex].end(); itL++) {
        int neighbor = (*itL).first;
        if (!visited[neighbor]) {
            doDFS(neighbor, visited);
        }
    }
}

void Graph::showEdges(){
    typename  std::list < std::pair < int, int > >::iterator itL;

    for(int i = 0 ; i < this->edges.size() ; i++){
        std::cout << "\n" << this->vertices[i] << ": ";
        std::list < std::pair < int, int > > auxEdges = this->edges[i];
        itL = auxEdges.begin();
        for(itL = auxEdges.begin() ; itL != auxEdges.end() ; itL++){
            std::cout << "(" << this->vertices[(*itL).first] << "," << (*itL).second << ") ";
        }
        std::cout << std::endl;
    }

}

//----------------------------------------------------------------------------------------------

void Graph::readVertices(std::string file){
    for(){

    }
}

void Graph::readConnections(std::string file){

}