#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct No{
    int size;
    int intersection;   // stores the size of the intersection
    bool isCircuit;
    string color;
    string fragment;
    vector<No*> nodesList;
};

class Graph {
    private:
        int V;  // vertex
        int E;  // edges
        vector<No*> adjList; // array with pointers
    
    public:
        Graph();
        ~Graph();
        int getV();
        int getE();
        void readGraph();
        void printGraph();
        void removeCircuit();
        void isCircuit(Graph* G);
        void isCircuitR(Graph* G, int v, string u);
        string getFragment(int indexI, int indexJ);
};