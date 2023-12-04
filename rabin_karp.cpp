#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "rabin_karp.h"

// Constructor for Node Class
QueueNode::QueueNode(char data, int row, int col, QueueNode* last, QueueNode* next){
    this->data = data;
    loc[0] = row;
    loc[1] = col;
    this->last = last;
    this->next = next;
}

QueueNode::~QueueNode(){

}

// Hash function
// Data is the character to take the hash value of
// Returns the hash value of the provided character
int TwoWayQ::hash(char data){
    return (int(data) * int(pow(7, int(data) % 11))) % 2027;
}

// Default constructor for queue class
// Starts with an empty queue
TwoWayQ::TwoWayQ(){
    head = nullptr;
    tail = nullptr;
    len = 0;
}

// Desctructor for queue class
// Iterates through each node in the queue and deletes it
TwoWayQ::~TwoWayQ(){
    QueueNode* grim = head;
    QueueNode* reaper = nullptr;
    while(grim != nullptr){
        reaper = grim->next;
        delete grim;
        grim = reaper;
    }
    head = nullptr;
    tail = nullptr;
}

// Creates a new node at the head of the queue
// The variables passed to the function are used to create the node
// Returns the hash value of the character inside the node
int TwoWayQ::enqueue(char data, int row, int col){
    if(this->head == nullptr){
        head = new QueueNode(data, row, col, nullptr, nullptr);
        tail = head;
    } else {
        head->last = new QueueNode(data, row, col, nullptr, head);
        head = head->last;
    }
    int tempHash = this->hash(head->data);
    len++;
    return tempHash;
}

// Deletes the node at the tail of the queue
// If there is a tail node, the hash value of the character inside the node is returned
// If the queue is empty, -1 is returned, which is not a number than can't be produced by the hash function
int TwoWayQ::dequeue(){
    if(tail != nullptr){
        int tempHash = this->hash(tail->data);
        tail = tail->last;
        delete tail->next;
        len--;
        return tempHash;
    }
    return -1;
}

// Rabin-Karp String Search Algorithm
// Searches for every instance of targetString in the file named fileName
// Returns a vector of rows and columns, each pair pointing to a place where that string can be found in the file.
// If the targetString cannot be found, a null pointer is returned instead.
std::vector<int>* TwoWayQ::rabin_karp(std::string fileName, std::string targetString){
    std::fstream legFile;
    legFile.open(fileName, std::ios::in);
    int row = -1, col, targetHash = 0, searchHash = 0, targetLen = targetString.size();
    bool isSame = true;
    std::vector<int>* returnPtr = nullptr;
    std::string searchString;

    for(int i = 0; i < targetLen; i++){
        targetHash += this->hash(targetString[i]);
    }

    if(legFile.is_open()){
        while(std::getline(legFile, searchString)){
            row++;
            col = 0;
            while(col < searchString.size()){
                if(len < targetLen){
                    searchHash += this->enqueue(searchString[col], row, col);;
                } else {
                    searchHash -= this->dequeue();
                    searchHash += this->enqueue(searchString[col], row, col);

                    if(searchHash == targetHash){
                        QueueNode* checker = head;
                        for(int i = 0; i < targetLen; i++){
                            if(checker->data = targetString[i]){
                                checker = checker->next;
                            } else {
                                isSame = false;
                                break;
                            }
                        }

                        if(isSame){
                            if(returnPtr == nullptr){
                                returnPtr = new std::vector<int>;
                            }
                            returnPtr->push_back(tail->loc[0]);
                            returnPtr->push_back(tail->loc[1]);
                        }
                    }
                }
                col++;
            }
        }
    }

    legFile.close();
    return returnPtr;
}