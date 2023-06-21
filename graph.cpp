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
    fstream File;
    string fragment;
    string filename;

    cout << "Digite o nome do arquivo de leitura: ";
    cin >> filename;

    File.open(filename, ios::in);

    File >> V;

    while(File >> fragment){
        // read the fragment
        No* node = new No();
    
        node->size = 0;
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

            if(digit == this->adjList[i]->fragment.length() && achou){
                this->adjList[i]->nodesList.push_back(node);
                this->adjList[i]->size++;
                this->E++;
            }

            k = digit = 0;
            achou = 0;
            
            // run the same algorithm on the opposite direction CHECK IF CORRECT TOMORROW
            while(k < node->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                k++;    // iterate through the digits of the words we previously had, to see if any digit is equal to a digit on the new word
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

            if(k == node->fragment.length() && achou){
                node->nodesList.push_back(this->adjList[i]);
                node->size++;
                this->E++;
            }
        }
    }
    File.close();
}

void Graph::printGraph(){
    for(int i = 0; i < this->V; i++){
            cout << this->adjList[i]->fragment << " " << i << endl;
        for(int j = 0; j < this->adjList[i]->nodesList.size(); j++){
            cout << this->adjList[i]->nodesList[j]->fragment << " " << i << endl;
        }
    }
}

string Graph::getFragment(int indexI, int indexJ){
    return this->adjList[indexI]->nodesList[indexJ]->fragment;
}