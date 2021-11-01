//----------------------------------------------------------------------------
// GRAPHM.CPP
// Implementation for GraphM Class
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


#include "graphm.h"

//----------------------------------------------------------------------------
// Default constructor
// Preconditions:   None
// Postconditions:  Cost array and Dijkstra table are initalized with
//                  infinite (INT_MAX) and 0 values, size is set to 0
GraphM::GraphM() {
    size = 0;
    initC();
    initT();
}

//----------------------------------------------------------------------------
// initC
// Preconditions:   Cost array holds either garbage data or data from a 
//                  previously built graph
// Postconditions:  Cost array is reset to only holding infinite values
void GraphM::initC() {
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            C[i][j] = INT_MAX;
        }
    }
}

//----------------------------------------------------------------------------
// initT
// Preconditions:   Dijkstra table holds either garbage data or data from a 
//                  previously built graph
// Postconditions:  Dijkstra table is reset, all distances are set to infinity,
//                  all visited are set to false, and all paths are set to 0
void GraphM::initT() {
    for(int i = 0; i < MAXNODES; i++) {
        for(int j = 0; j < MAXNODES; j++) {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
}

//----------------------------------------------------------------------------
// buildGraph
// Preconditions:   istream object passed as parameter is correctly formatted as
//                  detailed at the top of this file
// Postconditions:  istream is read and Graph is now filled with data on nodes
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

//----------------------------------------------------------------------------
// insertEdge
// Preconditions:   None
// Postconditions:  Returns false if invalid parameters or a duplicate edge
//                  otherwise adds the edge and returns true
bool GraphM::insertEdge(int from, int to, int length) {
    // Boundary check
    if(from < 0 || from > size) {
        return false;
    }
    // Boundary check 2
    if(to < 0 || to > size) {
        return false;
    }
    // Check for duplicate edge
    if(C[from][to] != INT_MAX) {
        return false;
    }
    // Add the edge
    C[from][to] = length;
    return true;    

    // Re-call Dijkstra to update the shortest paths for display
    findShortestPath();
}

//----------------------------------------------------------------------------
// removeEdge
// Preconditions:   None
// Postconditions:  None  
bool GraphM::removeEdge(int from, int to) {
    // Boundary check
    if(from < 0 || from > size) {
        return false;
    }
    // Boundary check 2
    if(to < 0 || to > size) {
        return false;
    }
    // Checks if edge exists
    if(C[from][to] == INT_MAX) {
        return false;
    }
    // Remove the edge
    C[from][to] = INT_MAX;
    return true;

    // Re-call Dijkstra to prevent weird behavior if display is called
    findShortestPath();
}

//----------------------------------------------------------------------------
// findShortestPath
// Preconditions:   Graph has been filled with nodes, Dijkstra table is in its
//                  reset state (only 0's and infinities)
// Postconditions:  Dijkstra table is filled with the shortest paths between
//                  every node pairing in the Graph
bool GraphM::findShortestPath() {
    // Set source distance to itself to 0
    initT();
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

//----------------------------------------------------------------------------
// min
// Preconditions:   None
// Postconditions:  Returns the lower of the 2 values
int GraphM::min(int a, int b) {
    return a < b ? a : b;
}

//----------------------------------------------------------------------------
// findV
// Preconditions:   Should only be called within the Dijkstra algorithm function
//                  assumes meaningful data in the Dijkstra table
// Postconditions:  Returns the index for the unvisited node with the minimum
//                  distance from the parameter node
int GraphM::findV(int source) {
    int v = 0;
    for(int i = 1; i <= size; i++) {
        if((T[source][i].dist < T[source][v].dist) && !T[source][i].visited) {
            v = i;
        }
    }
    return v;
}

//----------------------------------------------------------------------------
// displayAll
// Preconditions:   Dijkstra's algorithm has been correctly executed on the
//                  graph via a call to buildGraph(), the Dijkstra table    
//                  is filled with data about the paths for the shortest 
//                  distances between all the nodes in the Graph
// Postconditions:  No internal changes to the Graph, path data has been printed
//                  out to the console
void GraphM::displayAll() {
    cout << setw(26) << left << "Description";
    cout << setw(11) << left << "From node";
    cout << setw(9) << left << "To node";
    cout << "Dijkstra's Path" << endl;
    for(int i = 1; i <= size; i++) {
        cout << data[i] << endl;
        for(int j = 1; j <= size; j++) {
            if(i == j) {
                continue;
            }
            cout << setw(31) << left << "";
            cout << setw(8) << left << i;
            cout << setw(9) << j;
            cout << setw(10) << left;
            if(T[i][j].dist != INT_MAX) {
                cout << T[i][j].dist;
                cout << pathToString(i, j) << endl;
            }
            else {
                cout << "---";
                cout << endl;
            }
            
            if(T[i][j].dist != INT_MAX) {
                
            }
        }
    }
}

//----------------------------------------------------------------------------
// display
// Preconditions:   Dijkstra's algorithm has been correctly executed on the
//                  graph via a call to buildGraph(), the Dijkstra table    
//                  is filled with data about the paths for the shortest 
//                  distances between all the nodes in the Graph
// Postconditions:  No internal changes to the Graph, path data has been printed
//                  out to the console
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

//----------------------------------------------------------------------------
// pathToString
// Preconditions:   Should only be called within the display functions, assumes
//                  that the Dijkstra algorithm has been perfomed on the graph
//                  and that path values are meaningful
// Postconditions:  Returns a string of each node visited on the shortest path
//                  from parameter node 1 to parameter node 2
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

//----------------------------------------------------------------------------
// detailedPathToString
// Preconditions:   Should only be called within the display function, assumes
//                  that the Dijkstra algorithm has been perfomed on the graph
//                  and that path values are meaningful
// Postconditions:  Returns a string of the information of each node visited on
//                  the shortest path from parameter node 1 to parameter node 2
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