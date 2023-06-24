#include "graph.h"

using namespace std;

int main(){
    Graph* G = new Graph();

    G->readGraph();
    cout << "Grafo original, vértices e arcos: " << endl;
    G->printGraph();
    G->isCircuit();
    cout << "Grafo pós remoção de arestas, vértices e arcos: " << endl;
    G->printGraph();
    cout << "Sequenciamento Genético: ";
    G->maxPath();
    return 0;
}