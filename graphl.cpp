#include "graphl.h"

GraphL::GraphL() : size(0) {}

void GraphL::buildGraph(istream& infile) {
   int fromNode, toNode;          // from and to node ends of edge

   infile >> size;                // read the number of nodes
   if (infile.eof()) return;      // stop reading if no more data
   
   // explanation to student: when you want to read a string after an int, 
   // you must purge the rest of the int line or the end-of-line char will
   // be the string read
   string s;                      // used to read to end of line holding size
   getline(infile, s);

   // read graph node information
   for (int i=1; i <= size; i++) {
       adjList[i].data.setData(infile);
   }

   // read the edge data and add to the adjacency list
   for (;;) {
      infile >> fromNode >> toNode;
      if (fromNode == 0 && toNode == 0) return;     // end of edge data

      // insert a valid edge into the adjacency list for fromNode
      adjList[fromNode].edges.push_front(toNode);
   }
}

void GraphL::displayGraph() {
    cout << "Graph:" << endl;
    for(int i = 1; i <= size; i++) {
        cout << "Node " << i << "\t\t" << adjList[i].data << endl;
        for(int n : adjList[i].edges) {
            cout << "    edge " << i << " " << n << endl;
        }
    }
    cout << endl;
}

void GraphL::depthFirstSearch() {
    // Create array to track which edges have been visited
    bool* visited = new bool[size+1];
    // Mark all vertices as not visited
    for(int i = 0; i < size+1; i++) {
        visited[i] = false;
    }

    // Queue to store nodes found in the search
    queue<int> visitedNodes;

    // For v = 1 to n
    for(int i = 1; i <=size; i++) {
        if(!visited[i]) {
            dfsHelper(i, visited, visitedNodes);
        }
    }

    cout << "Depth-first ordering: ";
    while(!visitedNodes.empty()) {
        cout << visitedNodes.front() << " ";
        visitedNodes.pop();
    }
    cout << endl << endl;

    // De-allocate bool array
    delete[] visited;
    visited = nullptr;
}

void GraphL::dfsHelper(int v, bool* visited, queue<int>& visitedNodes) {
    // Mark v as visited
    visited[v] = true;
    // Add node to queue
    visitedNodes.push(v);

    // For each vertex w adjacent to v
    for(int w : adjList[v].edges) {
        if(!visited[w]) {
            dfsHelper(w, visited, visitedNodes);
        }
    }
}