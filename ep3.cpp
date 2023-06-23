#include "graph.h"

using namespace std;

int main(){
    Graph* G = new Graph();

    G->readGraph();
    G->isCircuit();
    G->printGraph();
    return 0;
}