#include "graph.h"

Graph::Graph(){
    this->V = 0;
    this->E = 0;
}

Graph::~Graph(){

}

int Graph::getE(){
    return this->E;
}

int Graph::getV(){
    return this->V;
}

void Graph::readGraph(){
    int V;
    int kParam;
    fstream File;
    string fragment;
    string filename;

    cout << "Digite o nome do arquivo de leitura: ";
    cin >> filename;

    cout << endl << "Digite o valor de K: ";
    cin >> kParam;
    File.open(filename, ios::in);

    File >> V;

    while(File >> fragment){
        // read the fragment
        No* node = new No();
    
        node->size = 0;
        node->color = "WHITE";
        node->isCircuit = false;
        node->fragment = fragment;

        this->adjList.push_back(node);
        this->V++;

        for(int i = 0; i < this->V - 1; i++){   // iterate through the whole list of vertex 
            // check if the fragment that was read makes an arch with another one we already have
            int digit = 0, k = 0;
            int copyDigit;
            bool achou = false;
            
            // if(this->adjList[i]->fragment == node->fragment)
            //     this->adjList[i]->nodesList.push_back(node);

            while(digit < this->adjList[i]->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                digit++;    // iterate through the digits of the words we previously had, to see if any digit is equal to a digit on the new word
                copyDigit = digit;
            }

            while(k < node->fragment.length() && digit < this->adjList[i]->fragment.length()){
                if(this->adjList[i]->fragment[digit] == node->fragment[k]){
                    digit++;
                    k++;
                    achou = true;
                }
                else{
                    k = 0;
                    digit = copyDigit + 1;
                    copyDigit++;
                    achou = false;
                }
            }

            if(digit == this->adjList[i]->fragment.length() && achou && k >= kParam){
                this->adjList[i]->nodesList.push_back(node);
                this->adjList[i]->color = "WHITE";
                this->adjList[i]->isCircuit = false;
                this->adjList[i]->size++;
                this->adjList[i]->intersection = k;
                this->E++;
            }

            k = digit = 0;
            achou = 0;
            
            // run the same algorithm on the opposite direction
            while(k < node->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                k++;
                copyDigit = k;
            }
            
            while(k < node->fragment.length() && digit < this->adjList[i]->fragment.length()){
                if(this->adjList[i]->fragment[digit] == node->fragment[k]){
                    digit++;
                    k++;
                    achou = true;
                }
                else{
                    digit = 0;
                    k = copyDigit + 1;
                    copyDigit++;
                    achou = false;
                }
            }

            if(k == node->fragment.length() && achou && k >= kParam){
                node->nodesList.push_back(this->adjList[i]);
                node->intersection = digit;
                node->color = "WHITE";
                node->isCircuit = false;
                node->size++;
                this->E++;
            }
        }
    }
    File.close();
}

void Graph::isCircuit(Graph* G){
    for(int u = 0; u < G->V; u++){
        G->adjList[u]->isCircuit = false;
        G->adjList[u]->color = "WHITE";
    }
    for(int u = 0; u < G->V; u++)
        if(G->adjList[u]->color == "WHITE")
            isCircuitR(G, u, this->adjList[u]->fragment);
}

void Graph::isCircuitR(Graph* G, int u, string frag){
    G->adjList[u]->color = "GRAY";
    for(int v = 0; v < G->adjList[u]->size; v++){
        if(G->adjList[u]->nodesList[v]->fragment == frag){
            G->adjList[u]->isCircuit = true;    // mark if the vertex is in a circuit
            G->adjList[u]->nodesList[v]->isCircuit = true;
        }
        if(G->adjList[v]->color == "WHITE")
            isCircuitR(G, v, frag);
    }
    G->adjList[u]->color = "BLACK";
}

// corrigir isso aqui
void Graph::removeCircuit(){
    for(int i = 0; i < this->V; i++){
        for(int j = 0; j < this->adjList[i]->nodesList.size(); j++){
            if(this->adjList[i]->nodesList[j]->isCircuit == true){
                for(int k = j; k < this->adjList[i]->nodesList.size() - 1; k++)
                    this->adjList[i]->nodesList[k] = this->adjList[i]->nodesList[k + 1];
                this->adjList[i]->nodesList.erase(this->adjList[i]->nodesList.end());
            }
        }
    }
}

void Graph::printGraph(){
    for(int i = 0; i < this->V; i++){
        cout << "Original: " << this->adjList[i]->fragment << " /vértice: " << this->adjList[i]->isCircuit << endl;
        for(int j = 0; j < this->adjList[i]->nodesList.size(); j++){
            cout << "\aArco: " << this->adjList[i]->nodesList[j]->fragment << " /vértice " << this->adjList[i]->nodesList[j]->isCircuit << endl;
        }
        cout << "\n-*- -*- -*- -*- -*- -*-\n" << endl;
    }
}

string Graph::getFragment(int indexI, int indexJ){
    return this->adjList[indexI]->nodesList[indexJ]->fragment;
}