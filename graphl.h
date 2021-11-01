#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"
#include <list>
#include <queue>

using namespace std;

const int MAX_NODES = 100;

struct GraphNode {
    list<int> edges;    // List of edge nodes
    NodeData data;      // Node's information
};

class GraphL {
    public:
    GraphL();
    void buildGraph(istream&);
    void displayGraph();
    void depthFirstSearch();

    private:
        GraphNode adjList[MAX_NODES];  // Adjacency array
        int size;
        void dfsHelper(int, bool*, queue<int>&);
};

#endif