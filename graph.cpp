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
        node->fragment = fragment;
        node->vPos = this->V;

        this->adjList.push_back(node);
        this->V++;

        for(int i = 0; i < this->V - 1; i++){   // iterate through the whole list of vertex 
            // check if the fragment that was read makes an arch with another one we already have
            int digit = 0, k = 0;
            int copyDigit;
            bool achou = false;
            
            if(this->adjList[i]->fragment == node->fragment)
                continue;

            while(digit < this->adjList[i]->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                digit++;    // iterate through the digits of the words we previously had, to see if any digit is equal to a digit on the new word
            }
            copyDigit = digit;

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
                this->adjList[i]->size++;
                this->adjList[i]->intersection = k;
                this->E++;
            }

            k = digit = 0;
            achou = 0;
            
            // run the same algorithm on the opposite direction
            while(k < node->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                k++;
            }
            copyDigit = k;
            
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
                node->size++;
                this->E++;
            }
        }
    }
    File.close();
}

void Graph::isCircuit(){
    int* onStack = new int[this->V];
    int* marked = new int[this->V];
    queue<int>* q = new queue<int>();

    for(int u = 0; u < this->V; u++){
        onStack[u] = 0;
        marked[u] = 0;
    }

    for(int u = 0; u < this->V; u++)
        if(!marked[u])
            isCircuitR(u, onStack, marked, q);

    delete(q);
    delete[](marked);
    delete[](onStack);
}

void Graph::isCircuitR(int v, int* onStack, int* marked, queue<int>* q){
    int cont = this->adjList[v]->size;
    vector<No*> aux = this->adjList[v]->nodesList;

    onStack[v] = 1;
    marked[v] = 1;

    q->push(v);

    for(int w = 0; w < this->adjList[v]->size; w++){
        if(!marked[this->adjList[v]->nodesList[w]->vPos]){
            isCircuitR(this->adjList[v]->nodesList[w]->vPos, onStack, marked, q);
        }
        else if(onStack[w] || q->front() == this->adjList[v]->nodesList[w]->vPos){
            for(int k = 0; k < cont; k++){
                if(this->adjList[v]->nodesList[w]->vPos == aux[k]->vPos){
                    aux = fixConnected(aux, k);
                    break;
                } 
            }
            cont--;
        }
    }
    onStack[v] = false;
    this->adjList[v]->nodesList = aux;
    this->adjList[v]->size = cont;

    q->pop();
}

vector<No*> Graph::fixConnected(vector<No*> aux, int k){
    for(int j = k; j < int(aux.size() - 1); j++)
        aux[j] = aux[j+1];
    
    aux.erase(aux.end() - 1);
    return aux;
}

void Graph::maxPath(){
    int* marked = new int[this->V];
    int* ini = new int[this->V];
    int* fim = new int[this->V];
    int cont = 0;

    for(int i = 0; i < this->V; i++)
        marked[i] = ini[i] = fim[i] = 0;
    
    for(int v = 0; v < this->V; v++)
        if(!marked[v])
            maxPathR(v, cont, ini, fim, marked);

    int* sortArray = new int[this->V];
    for(int i = 0; i < this->V; i++)
        sortArray[i] = fim[i];
    
    sort(sortArray, sortArray + this->V, greater<int>());

    No** sequencia = new No*[this->V];
    for(int i = 0; i < this->V; i++){
        int aux = fim[i];

        for(int j = 0; j  < this->V; j++){
            if(sortArray[j] == aux){
                sequencia[j] = this->adjList[i];
                break;
            }
        }
    }

    joinSequences(sequencia);
}

void Graph::maxPathR(int v, int& cont, int* ini, int* fim, int* marked){
    marked[v] = 1;
    ini[v] = cont;

    for(int i = 0; i < this->adjList[v]->size; i++){
        int u = this->adjList[v]->nodesList[i]->vPos;

        if(!marked[u])
            maxPathR(u, cont, ini, fim, marked);
    }

    cont += 1;
    fim[v] = cont;
}

void Graph::joinSequences(No** sequencia){
    // set the words correctly and show answer
    for(int i = 0; i < this->V; i++){
        int k = 0;
        int digit = 0;
        int copyDigit = 0;

        if(i < this->V - 1){
            while(digit < sequencia[i]->fragment.length() && sequencia[i]->fragment[digit] != sequencia[i + 1]->fragment[k])
                digit++;
            copyDigit = digit;

            while(digit < sequencia[i]->fragment.length() && k < sequencia[i + 1]->fragment.length()){
                if(sequencia[i]->fragment[digit] == sequencia[i + 1]->fragment[k]){
                    digit++;
                    k++;
                }
                else{
                    k = 0;
                    copyDigit++;
                    digit = copyDigit;
                }
            }
        }
        for(int l = 0; l < sequencia[i]->fragment.length() - k; l++)
            cout << sequencia[i]->fragment[l];
    }
    cout << endl;
}

void Graph::printGraph(){
    for(int i = 0; i < this->V; i++){
        cout << "Original: " << this->adjList[i]->fragment << endl;
        for(int j = 0; j < this->adjList[i]->size; j++){
            cout << "\aArco: " << this->adjList[i]->nodesList[j]->fragment << endl;
        }
        cout << "\n-*- -*- -*- -*- -*- -*-\n" << endl;
    }
}