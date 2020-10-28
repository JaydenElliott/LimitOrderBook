#include "../imports/importsGlobal.hpp"
#include "node.hpp"
#include "rbtree.hpp"
#pragma once

using namespace std;

const size_t knuth = 2654435769;  // (1/golden ratio)*(2^32)

class HashNode {
   public:
    HashNode(){};
    HashNode(float price, size_t ID, Node *rbNode = nullptr) {
        this->price = price;
        this->ID = ID;
        this->rbNode = rbNode;
    }

    float price;
    size_t ID;
    HashNode *nextNode = nullptr;
    Node *rbNode = nullptr;
};

class HashTable {
   public:
    HashTable(){};
    HashTable(int sizeExponent) {
        if (sizeExponent < 0) {
            throw runtime_error("Invalid size exponent for hash table" + to_string(sizeExponent));
        }
        this->sizeExponent = sizeExponent;
        this->tableSize = pow(2, sizeExponent);
        this->hashVector = vector<HashNode *>(tableSize, nullptr);
    }
    ~HashTable() {
        for (int i = 0; i < hashVector.size(); i++) {
            HashNode *currnode = hashVector.at(i);

            while (currnode != nullptr) {
                HashNode *tempNode = currnode;

                currnode = currnode->nextNode;
                delete tempNode;
            }
            hashVector.at(i) = nullptr;
        }
    };

    int sizeExponent;
    int tableSize;
    vector<HashNode *> hashVector;
    void del(size_t ID, RBtree &rbtree);
    void print();
    bool get(size_t ID, HashNode &node);
    void insert(int price, size_t ID, Node *rbnode, RBtree &tree);
    size_t generateHash(size_t ID);
};

size_t HashTable::generateHash(size_t ID) {
    return ((ID * knuth) >> (32 - this->sizeExponent)) % tableSize;  // TODO replace with simply mod
}

void HashTable::insert(int price, size_t ID, Node *rbnode, RBtree &tree) {
    size_t newIndex = generateHash(ID);
    cout << "...1.1..." << endl;
    tree.insert_price(rbnode);
    cout << "...1.2..." << endl;
    if (hashVector.at(newIndex) == nullptr) {
        hashVector.at(newIndex) = new HashNode(price, ID, rbnode);
    } else {
        HashNode *currNode = hashVector.at(newIndex);
        while (currNode->nextNode != nullptr) {
            currNode = currNode->nextNode;
        }
        currNode->nextNode = new HashNode(price, ID, rbnode);
    }
}

bool HashTable::get(size_t ID, HashNode &node) {
    size_t newIndex = generateHash(ID);
    HashNode *initElem = hashVector.at(newIndex);
    while (initElem != nullptr) {
        if (initElem->ID == ID) {
            node = *initElem;
            return true;
        }
        initElem = initElem->nextNode;
    }
    return false;
}

void HashTable::del(size_t ID, RBtree &rbtree) {
    size_t Index = generateHash(ID);
    if (hashVector.at(Index) != nullptr) {
        HashNode *currNode = hashVector.at(Index);
        HashNode *prevNode = nullptr;

        while (currNode != nullptr) {
            if (currNode->ID == ID) {
                break;
            }
            prevNode = currNode;
            currNode = currNode->nextNode;
        }

        if (currNode->ID == ID) {
            HashNode *nextnode = currNode->nextNode;
            rbtree.delete_price(currNode->rbNode);
            delete currNode;
            if (prevNode == nullptr) {
                hashVector.at(Index) = nextnode;
            } else {
                prevNode->nextNode = nextnode;
            }
        }
    }
}
// Prints ID's in hashtable
void HashTable::print() {
    for (int i = 0; i < hashVector.size(); i++) {
        if (hashVector.at(i) == nullptr) {
            continue;
        }
        cout << hashVector.at(i)->ID << " " << hashVector.at(i)->price << endl;
        if (hashVector.at(i)->nextNode != nullptr) {
            HashNode *tempElem = hashVector.at(i);
            while (tempElem->nextNode != nullptr) {
                cout << tempElem->nextNode->ID << endl;
                tempElem = tempElem->nextNode;
            }
        }
    }
}
