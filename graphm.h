#ifndef GRAPHM_H
#define GRAPHM_H

class GraphM {
public:

private:
    struct TableType {
        bool visited;   // whether node has been visited
        int dist;       // currently known shortest distance from source
        int path;       // previous node in path of min dist
    };
}

#endif