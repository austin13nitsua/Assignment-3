#include "graphm.h"

GraphM::GraphM() {
    size = 0;
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            C[i][j] = INT_MAX;
        }
        C[i][i] = INT_MAX;
    }
    initT();
}

void GraphM::initC() {

}

void GraphM::initT() {
    for(int i = 0; i < MAXNODES; i++) {
        T[i][i].dist = INT_MAX;
        T[i][i].visited = false;
        T[i][i].path = 0;
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