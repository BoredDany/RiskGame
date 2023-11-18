//
// Created by estudiante on 17/11/2023.
//

#ifndef RISKSINCOLOR_GRAFO_H
#define RISKSINCOLOR_GRAFO_H

#include <vector>
#include <list>
#include <utility>
#include "PaisG.h"

class Grafo{
private:
    std::vector < Pais > paises;
    std::vector < std::list < std::pair < int, int > > > conexiones;
public:
    //constructors
    Graph();

    //getters
    std::vector < Pais > getVertices();
    std::vector < std::list < std::pair < int, int > > > getEdges();

    //setters
    void setVertices(std::vector < Pais >& vertices);
    void setEdges(std::vector < std::list < std::pair < int, int > > >& edges);

    //inserting
    bool addVertex(Pais& vertex);
    bool addEdge(Pais& origin, T& destination, C cost);

    //searching
    int searchVertice(Pais& vertex);
    bool searchEdge(Pais& origin, Pais& destination);

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

    //algoritmos
    void readVertices(std::string file);
    void readConnections(std::string file);

};

#endif //RISKSINCOLOR_GRAFO_H
