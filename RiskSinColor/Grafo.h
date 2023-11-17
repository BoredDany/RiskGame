//
// Created by estudiante on 17/11/2023.
//

#ifndef RISKSINCOLOR_GRAFO_H
#define RISKSINCOLOR_GRAFO_H

#include <vector>
#include <list>
#include <utility>
#include "Pais.h"

class Grafo{
private:
    std::vector < Pais > paises;
    std::vector < std::list < std::pair < int, int > > > conexiones;
public:
    //constructors
    Graph();

    //getters
    std::vector < T > getVertices();
    std::vector < std::list < std::pair < int, C > > > getEdges();

    //setters
    void setVertices(std::vector < T >& vertices);
    void setEdges(std::vector < std::list < std::pair < int, C > > >& edges);

    //inserting
    bool addVertex(T& vertex);
    bool addEdge(T& origin, T& destination, C cost);

    //searching
    int searchVertice(T& vertex);
    bool searchEdge(T& origin, T& destination);

    //general info
    int numVertices();
    int numEdges();

    //tours
    void plain();
    void bfs();
    void doBFS(int startVertex, std::vector<bool>& visited, std::queue<int>& vertexQueue);
    void dfs();
    void doDFS(int currentVertex, std::vector<bool>& visited);
    void showEdges();
};

#endif //RISKSINCOLOR_GRAFO_H
