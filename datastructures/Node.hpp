#include "../imports/importsGlobal.hpp"
#include "queue.hpp"
#pragma once

using namespace std;

/**
 * Node class for the red-black trees
 */
class Node {
   public:
    Node() {
        this->price = 0;
        this->ID = "NIL";
        this->colour = BLACK;
    }
    Node(float price, string ID) {
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
    string ID;
    double price;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
};