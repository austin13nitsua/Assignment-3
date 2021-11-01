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
        if(fromNode == 0 && toNode == 0) {
            int garbage;
            infile >> garbage;
            return; // end of edge data
        } 
        infile >> C[fromNode][toNode];
    }
}

bool GraphM::insertEdge() {
    return false;
}

bool GraphM::removeEdge() {
    return false;
}

bool GraphM::findShortestPath() {
    // Set source distance to itself to 0
    for(int source = 1; source <= size; source++) {
        T[source][source].dist = 0;
    }

    // Iterate through each source node
    for(int i = 1; i <= size; i++) {
        // Find paths to each node from this source node
        for(int j = 1; j <= size; j++) {
            // Find the min dist not yet visited node
            int v = findV(i);
            if(v == 0) {
                break;
            }
            T[i][v].visited = true;

            // For each w adjacent to v
            for(int k = 1; k <= size; k++) {
                if(C[v][k] == INT_MAX) {
                    continue;
                }
                if(!T[i][k].visited) {
                    int original = T[i][k].dist;
                    int throughV = T[i][v].dist + C[v][k];
                    if(min(original, throughV) == throughV) {
                        T[i][k].dist = throughV;
                        T[i][k].path = v;
                    }
                }
            }
        }
    }

    return false;
}

int GraphM::min(int a, int b) {
    return a < b ? a : b;
}

int GraphM::findV(int source) {
    int v = 0;
    for(int i = 1; i <= size; i++) {
        if((T[source][i].dist < T[source][v].dist) && !T[source][i].visited) {
            v = i;
        }
    }
    return v;
}

void GraphM::displayAll() {
    cout << "Description               From node  To node  Dijkstra's  Path";
    cout << endl;
    for(int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for(int j = 1; j <= size; j++) {
            if(i == j) {
                continue;
            }
            cout << setw(32);
            cout << i << "        ";
            cout << j << "        ";
            if(T[i][j].dist != INT_MAX) {
                cout << T[i][j].dist << "        ";
                cout << pathToString(i, j) << endl;
            }
            else {
                cout << "---        ";
                cout << endl;
            }
            
            if(T[i][j].dist != INT_MAX) {
                
            }
        }
    }
}

void GraphM::display(int i, int j) {
    cout << "\t" << i << "\t" << j << "\t";
    if(T[i][j].dist == INT_MAX) {
        cout << "---" << endl;
        return;    
    }
    cout << T[i][j].dist << "\t";
    cout << pathToString(i,j) << endl;
    cout << detailedPathToString(i,j) << endl;
}

string GraphM::pathToString(int i, int j) {
    string path;
    stack<int> route;
    route.push(j);
    while(j != 0) {
        if(T[i][j].path == 0) {
            break;
        }
        route.push(T[i][j].path);
        j = T[i][j].path;
    }
    while (!route.empty()) {
        path.append(to_string(route.top()));
        path.append(" ");
        route.pop();
    }
    return path;
}

string GraphM::detailedPathToString(int i, int j) {
    stringstream ss;
    stack<int> route;
    route.push(j);
    while(j != 0) {
        if(T[i][j].path == 0) {
            break;
        }
        route.push(T[i][j].path);
        j = T[i][j].path;
    }
    while (!route.empty()) {
        ss << data[route.top()];
        ss << endl;
        route.pop();
    }
    return ss.str();
}

void GraphM::test() {
    cout << "C array" << endl;
    for(int i = 0; i <= size; i++) {
        for(int j = 0; j <= size; j++) {
            cout << "[" << i << "][" << j << "] : " << C[i][j] << endl;
        }
    }
}