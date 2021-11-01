#ifndef GRAPHM_H
#define GRAPHM_H

#include "nodedata.h"
#include <climits>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

const int MAXNODES = 100;

class GraphM {
public:
    GraphM();
    void buildGraph(istream&);
    bool insertEdge();        
    bool removeEdge();
    bool findShortestPath();
    void displayAll();
    void display(int, int);

    void test(); // For debugging

private:
    struct TableType {
        bool visited;   // whether node has been visited
        int dist;       // currently known shortest distance from source
        int path;       // previous node in path of min dist
    };
    NodeData data[MAXNODES];            // data for graph nodes information
    int C[MAXNODES][MAXNODES];          // Cost array, the adjacency matrix
    int size;                           // number of ndoes in the graph
    TableType T[MAXNODES][MAXNODES];    // stores Dijkstra information

    void initC(); // Initializes cost array
    void initT(); // Initializes dijkstra array
    
    int min(int, int);    // Finds lower value
    int findV(int);       // Finds not yet visited node with min dist

    string pathToString(int, int); // Makes a path between nodes into a string
    string detailedPathToString(int, int); // Makes a detailed path string

    
};

#endif