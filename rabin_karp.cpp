#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include "rabin_karp.h"

QueueNode::QueueNode(char data, int row, int col, QueueNode* last, QueueNode* next){
    this->data = data;
    loc[0] = row;
    loc[1] = col;
    this->last = last;
    this->next = next;
}

QueueNode::~QueueNode(){

}

int TwoWayQ::hash(char data){
    return (int(data) * int(pow(7, int(data) % 11))) % 2027;
}

TwoWayQ::TwoWayQ(){
    head = nullptr;
    tail = nullptr;
    len = 0;
}

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


int* TwoWayQ::rabin_karp(std::string fileName, std::string targetString){
    std::fstream legFile;
    legFile.open(fileName, std::ios::in);
    int row = -1, col, targetHash = 0, searchHash = 0, targetLen = targetString.size();
    bool isSame = true;
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
                            int* arr = new int[2];
                            arr[0] = tail->loc[0];
                            arr[1] = tail->loc[1];
                            return arr;
                        }
                    }
                }
                col++;
            }
        }
    }

    legFile.close();
    return nullptr;
}