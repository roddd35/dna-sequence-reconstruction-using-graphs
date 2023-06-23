#pragma once

#include <queue>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct No{
    int vPos;
    int size;
    int intersection;   // stores the size of the intersection
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
        void isCircuit();
        void isCircuitR(int v, int* onStack, int* marked, queue<int>* q);
        vector<No*> fixConnected(vector<No*> aux, int k);
};