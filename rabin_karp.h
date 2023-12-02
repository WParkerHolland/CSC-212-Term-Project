#pragma once

#include <iostream>
#include <string>
#include <vector>

#ifndef RABINKARP
#define RABINKARP
#endif

class QueueNode{
    private:
        int loc[2];
        char data;
        QueueNode* last;
        QueueNode* next;
    public:
        QueueNode(char data, int row, int col, QueueNode* last, QueueNode* next);
        ~QueueNode();

    friend class TwoWayQ;
};

class TwoWayQ{
    private:
        QueueNode* head;
        QueueNode* tail;
        int len;
    public:
        TwoWayQ();
        ~TwoWayQ();
        int enqueue(char data, int row, int col);
        int dequeue();
        int hash(char data);
        std::vector<int>* rabin_karp(std::string fileName, std::string targetString);
};