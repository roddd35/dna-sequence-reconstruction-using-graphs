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
            
            if(this->adjList[i]->fragment == node->fragment)
                this->adjList[i]->nodesList.push_back(node);

            while(digit < this->adjList[i]->fragment.length() && this->adjList[i]->fragment[digit] != node->fragment[k]){
                digit++;    // iterate through the digits of the words we previously had, to see if any digit is equal to a digit on the new word
                if(this->adjList[i]->fragment[digit] == node->fragment[k]){
                    copyDigit = digit;
                    while(this->adjList[i]->fragment[digit] == node->fragment[k]){
                        digit++;
                        k++;
                    }
                    if(digit >= this->adjList[i]->fragment.length() - 1){
                        this->adjList[i]->nodesList.push_back(node);
                        this->E++;
                        break;
                    }
                    else{
                        k = 0;
                        digit = copyDigit + 1;
                    }
                }
            }
            digit = k = 0;

            // run the same algorithm on the opposite direction CHECK IF CORRECT TOMORROW
            while(digit < node->fragment.length() && this->adjList[i]->fragment[k] != node->fragment[digit]){
                digit++;    // iterate through the digits of the words we previously had, to see if any digit is equal to a digit on the new word
                if(this->adjList[i]->fragment[k] == node->fragment[digit]){
                    copyDigit = digit;
                    while(this->adjList[i]->fragment[k] == node->fragment[digit]){
                        digit++;
                        k++;
                    }
                    if(digit >= this->adjList[i]->fragment.length() - 1){
                        this->adjList[i]->nodesList.push_back(node);
                        this->E++;
                        break;
                    }
                    else{
                        k = 0;
                        digit = copyDigit + 1;
                    }
                }
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