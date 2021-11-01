//----------------------------------------------------------------------------
// GRAPHL.H
// Class for a Graph of Nodes
// Coded by: Austin Barracliffe
//----------------------------------------------------------------------------
// GraphM: stores nodes and edges
// and allows other features:
//      --allows the building of a Graph from an input file
//      --allows output of the nodes and edges in the Graph
//      --allows a depth-first search to be performed on the Graph
//
// Implementation and assumptions:
//      --uses an internal Struct, GraphNode to store data of which edges
//        a node has as well as information on the node
//      --uses an array of GraphNodes to hold data on every node in the Graph
//      --does not allow more than 100 nodes to be held in a Graph
//      --assumes the input file used to build the graph begins with a
//        nonnegative integer n which denotes the number of nodes in the graph
//      --assumes that following n, the input file then has node information
//        in the form of a string of text for n lines corresponding to each
//        node
//      --assumes that after the information, the input file has correctly
//        formatted data of the edges in the form: i j
//        where i = the origin node, and j = the destination node
//      --assumes that a line with two zeroes denotes the end of the file
//----------------------------------------------------------------------------

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
//----------------------------------------------------------------------------
// Default Constructor
// Preconditions:   None
// Postconditions:  Adjacency array is populated with nodes and their edges/data
//                  size is set to the number of nodes in the Graph
    GraphL();

//----------------------------------------------------------------------------
// buildGraph
// Preconditions:   istream object passed as parameter is correctly formatted as
//                  detailed at the top of this file
// Postconditions:  istream is read and Graph is now filled with data on nodes
    void buildGraph(istream&);

//----------------------------------------------------------------------------
// displayGraph
// Preconditions:   None
// Postconditions:  Nodes, their information, and their edges are printed out to
//                  the console
    void displayGraph();

//----------------------------------------------------------------------------
// depthFirstSearch
// Preconditions:   None
// Postconditions:  A sequence of the nodes in the graph is printed out to the 
//                  console as found in the depth-first search
    void depthFirstSearch();

    private:
        GraphNode adjList[MAX_NODES];  // Adjacency array
        int size;

//----------------------------------------------------------------------------
// dfsHelper
// Preconditions:   None
// Postconditions:  Bool array parameter is updated, current node is processed
//                  by pushing it into the queue parameter       
        void dfsHelper(int, bool*, queue<int>&);
};

#endif