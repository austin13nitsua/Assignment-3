#include "graphm.h"

GraphM::GraphM() {
    size = 0;
    for(int i = 0; i < MAXNODES; i++) {
        C[i][i] = INT_MAX;
    }
    initT();
}

void GraphM::initT() {
    for(int i = 0; i < MAXNODES; i++) {
        T[i][i].dist = INT_MAX;
        T[i][i].visited = false;
        T[i][i].path = 0;
    }
}

void GraphM::buildGraph() {
    
}