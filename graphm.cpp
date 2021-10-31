#include "graphm.h"

GraphM::GraphM() {
    size = 0;
    initC();
    initT();
}

void GraphM::initC() {
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            C[i][j] = INT_MAX;
        }
    }
}

void GraphM::initT() {
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

void GraphM::buildGraph(istream& infile) {
    int fromNode, toNode;      // from and to node ends of edge

    initC();                   // Set/reset cost array
    initT();                   // Set/reset dijkstra array

    infile >> size;            // read the number of nodes
    if(infile.eof()) return;  // stop reading if no more data

    string s;                  // used to read to end of line holding size
    getline(infile, s);

    // read graph node information
    for(int i = 1; i <= size; i++) {
        data[i].setData(infile);
    }

    for(;;) {
        infile >> fromNode >> toNode;
        if(fromNode == 0 && toNode == 0) return; // end of edge data

        infile >> C[fromNode][toNode];
    }
}