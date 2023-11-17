//
// Created by estudiante on 17/11/2023.
//


#include "Grafo.h"
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

template <class T, class C>
Graph<T, C>::Graph() {

}

//----------------------------------------------------------------------------------------------

//getters

template < class T, class C >
std::vector < T > Graph<T, C>::getVertices(){
    return this->vertices;
}

template < class T, class C >
std::vector < std::list < std::pair < int, C > > > Graph<T, C>::getEdges(){
    return this->edges;
}

//----------------------------------------------------------------------------------------------

//setters

template < class T, class C >
void Graph<T, C>::setVertices(std::vector < T >& vertices){
    this->vertices = vertices;
}

template < class T, class C >
void Graph<T, C>::setEdges(std::vector < std::list < std::pair < int, C > > >& edges){
    this.edges = edges;
}

//----------------------------------------------------------------------------------------------

//inserting

template < class T, class C >
bool Graph<T, C>::addVertex(T& vertex){
    int vertexFound = searchVertice(vertex);
    if(vertexFound == -1){
        this->vertices.push_back(vertex);
        this->edges.push_back(std::list<std::pair<int, C>>());
        return true;
    }
    return false;
}

template < class T, class C >
bool Graph<T, C>::addEdge(T& origin, T& destination, C cost){
    int destinationIndex = searchVertice(destination);
    int originIndex = searchVertice(origin);

    if(!searchEdge(origin, destination) && originIndex != -1 && destinationIndex != -1){
        std::pair < int, C > newEdge (destinationIndex, cost);
        this->edges[originIndex].push_back(newEdge);
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------------------------

//searching

template < class T, class C >
int Graph<T, C>::searchVertice(T& vertex){
    int vertexFound = -1;
    for(int i = 0 ; i < this->vertices.size() ; i++){
        if(this->vertices[i] == vertex){
            vertexFound = i;
            break;
        }
    }
    return vertexFound;
}

template < class T, class C >
bool Graph<T, C>::searchEdge(T& origin, T& destination){
    typename  std::list < std::pair < int, C > >::iterator itL;
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

template < class T, class C >
int Graph<T, C>::numVertices(){
    return this->vertices.size();
}

template < class T, class C >
int Graph<T, C>::numEdges(){
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

template < class T, class C >
void Graph<T, C>::plain(){
    for(int i = 0 ; i < this->vertices.size() ; i++){
        std::cout << this->vertices[i] << " ; ";
    }
}

template < class T, class C >
void Graph<T, C>::bfs(){
    std::vector<bool> visited(this->vertices.size(), false);
    std::queue<int> vertexQueue;

    for (int i = 0; i < this->vertices.size(); i++) {
        if (!visited[i]) {
            doBFS(i, visited, vertexQueue);
        }
    }
}

template < class T, class C >
void Graph<T, C>::doBFS(int startVertex, std::vector<bool>& visited, std::queue<int>& vertexQueue){
    visited[startVertex] = true;
    vertexQueue.push(startVertex);

    while (!vertexQueue.empty()) {
        int currentVertex = vertexQueue.front();
        vertexQueue.pop();

        std::cout << this->vertices[currentVertex] << ", ";

        typename  std::list < std::pair < int, C > >::iterator itL;
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

template < class T, class C >
void Graph<T, C>::dfs(){
    std::vector<bool> visited(this->vertices.size(), false);

    for (int i = 0; i < this->vertices.size(); ++i) {
        if (!visited[i]) {
            doDFS(i, visited);
        }
    }
}

template <class T, class C>
void Graph<T, C>::doDFS(int currentVertex, std::vector<bool>& visited) {
    visited[currentVertex] = true;
    std::cout << this->vertices[currentVertex] << ", ";

    typename  std::list < std::pair < int, C > >::iterator itL;
    itL = this->edges[currentVertex].begin();

    for ( ; itL != this->edges[currentVertex].end(); itL++) {
        int neighbor = (*itL).first;
        if (!visited[neighbor]) {
            doDFS(neighbor, visited);
        }
    }
}

template < class T, class C >
void Graph<T, C>::showEdges(){
    typename  std::list < std::pair < int, C > >::iterator itL;

    for(int i = 0 ; i < this->edges.size() ; i++){
        std::cout << "\n" << this->vertices[i] << ": ";
        std::list < std::pair < int, C > > auxEdges = this->edges[i];
        itL = auxEdges.begin();
        for(itL = auxEdges.begin() ; itL != auxEdges.end() ; itL++){
            std::cout << "(" << this->vertices[(*itL).first] << "," << (*itL).second << ") ";
        }
        std::cout << std::endl;
    }

}

//----------------------------------------------------------------------------------------------
