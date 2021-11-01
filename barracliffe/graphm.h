//----------------------------------------------------------------------------
// GRAPHM.H
// Class for a Graph of Nodes
// Coded by: Austin Barracliffe
//----------------------------------------------------------------------------
// GraphM: stores nodes and edges
// and allows other features:
//      --insertion of an individual Edge
//      --removal of an individual Edge
//      --allows Dijkstra's algorithm to be performed on the Graph
//      --allows output of shortest paths between every node in the Graph
//      --allows more detailed output of shortest path between 2 specified
//        nodes in the graph
//
// Implementation and assumptions:
//      --uses an array of NodeData objects to store text information about the
//        nodes
//      --uses a 2D array (adjacency matrix) to hold the 'cost array' showing
//        the length of edges between nodes in the graph
//      --uses an internal struct TableType to store data used for Dijkstra's
//        algorithm (a 2D array of these structs holds data for the whole graph)
//      --builds the graph from an input text file
//      --assumes that the 1st line of an input file has an int n denoting the 
//        number of nodes in the graph
//      --assumes that the n lines following the 1st line hold a string of text
//        (max length 50 chars) which identifies the corresponding node
//      --after reading the node information, it assumes correctly formatted
//        int data in the form: i j k
//        for each line of text where i is the origin node, j is the destination
//        node, and k is the length of the edge
//      --assumes a maximum of 100 nodes
//      --assumes no 0 nodes
//      --assumes that three zeros on a line is the end of the file
//----------------------------------------------------------------------------

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
//----------------------------------------------------------------------------
// Default constructor
// Preconditions:   None
// Postconditions:  Cost array and Dijkstra table are initalized with
//                  infinite (INT_MAX) and 0 values, size is set to 0
    GraphM();

//----------------------------------------------------------------------------
// buildGraph
// Preconditions:   istream object passed as parameter is correctly formatted as
//                  detailed at the top of this file
// Postconditions:  istream is read and Graph is now filled with data on nodes
    void buildGraph(istream&);

//----------------------------------------------------------------------------
// insertEdge
// Preconditions:   None
// Postconditions:  Returns false if invalid parameters or a duplicate edge
//                  otherwise adds the edge and returns true
    bool insertEdge(int, int, int);

//----------------------------------------------------------------------------
// removeEdge
// Preconditions:   None
// Postconditions:  None    
    bool removeEdge(int, int);

//----------------------------------------------------------------------------
// findShortestPath
// Preconditions:   Graph has been filled with nodes, Dijkstra table is in its
//                  reset state (only 0's and infinities)
// Postconditions:  Dijkstra table is filled with the shortest paths between
//                  every node pairing in the Graph
    bool findShortestPath();

//----------------------------------------------------------------------------
// displayAll
// Preconditions:   Dijkstra's algorithm has been correctly executed on the
//                  graph via a call to buildGraph(), the Dijkstra table    
//                  is filled with data about the paths for the shortest 
//                  distances between all the nodes in the Graph
// Postconditions:  No internal changes to the Graph, path data has been printed
//                  out to the console
    void displayAll();

//----------------------------------------------------------------------------
// display
// Preconditions:   Dijkstra's algorithm has been correctly executed on the
//                  graph via a call to buildGraph(), the Dijkstra table    
//                  is filled with data about the paths for the shortest 
//                  distances between all the nodes in the Graph
// Postconditions:  No internal changes to the Graph, path data has been printed
//                  out to the console
    void display(int, int);

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

//----------------------------------------------------------------------------
// initC
// Preconditions:   Cost array holds either garbage data or data from a 
//                  previously built graph
// Postconditions:  Cost array is reset to only holding infinite values
    void initC(); // Initializes cost array

//----------------------------------------------------------------------------
// initT
// Preconditions:   Dijkstra table holds either garbage data or data from a 
//                  previously built graph
// Postconditions:  Dijkstra table is reset, all distances are set to infinity,
//                  all visited are set to false, and all paths are set to 0
    void initT(); // Initializes dijkstra array

//----------------------------------------------------------------------------
// min
// Preconditions:   None
// Postconditions:  Returns the lower of the 2 values
    int min(int, int);    // Finds lower of 2 values

//----------------------------------------------------------------------------
// findV
// Preconditions:   Should only be called within the Dijkstra algorithm function
//                  assumes meaningful data in the Dijkstra table
// Postconditions:  Returns the index for the unvisited node with the minimum
//                  distance from the parameter node
    int findV(int);       // Finds not yet visited node with min dist

//----------------------------------------------------------------------------
// pathToString
// Preconditions:   Should only be called within the display functions, assumes
//                  that the Dijkstra algorithm has been perfomed on the graph
//                  and that path values are meaningful
// Postconditions:  Returns a string of each node visited on the shortest path
//                  from parameter node 1 to parameter node 2
    string pathToString(int, int); // Makes a path between nodes into a string

//----------------------------------------------------------------------------
// detailedPathToString
// Preconditions:   Should only be called within the display function, assumes
//                  that the Dijkstra algorithm has been perfomed on the graph
//                  and that path values are meaningful
// Postconditions:  Returns a string of the information of each node visited on
//                  the shortest path from parameter node 1 to parameter node 2
    string detailedPathToString(int, int); // Makes a detailed path string
};

#endif