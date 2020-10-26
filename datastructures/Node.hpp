#include "../imports/importsGlobal.hpp"
#include "queue.hpp"
#pragma once

using namespace std;

// TODO: Currently every node gets an ID push, need to fix this
// so that only new nodes get id pushes.
class Node {
   public:
    Node(float price = 0, size_t ID = 0) {
        this->colour = BLACK;
        this->price = price;
        this->ID = ID;
        queue = Queue();
        queue.push(ID);
        bool nullNode = true;
        if (price != 0) {
            nullNode = false;
        }
    }
    ~Node(){};
    bool colour;
    Queue queue;
    size_t ID;
    double price;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};