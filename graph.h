#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

struct No{
    int size;
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
        string getFragment(int indexI, int indexJ);
};