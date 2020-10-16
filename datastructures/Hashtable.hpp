#include "../importsGlobal.hpp"
#pragma once

using namespace std;

const size_t knuth = 2654435769;  // (1/golden ratio)*(2^32)

class HashNode {
   public:
    HashNode(){};
    HashNode(float price, size_t ID) {
        this->price = price;
        this->ID = ID;
    }
    ~HashNode(){};

    float price;
    size_t ID;
    HashNode *nextNode = nullptr;
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
        this->hashVector = vector<HashNode *>(tableSize, 0);
    }
    ~HashTable() {
        for (int i = 0; i < hashVector.size(); i++) {
            delete hashVector.at(i);
        }
    };

    size_t generateHash(size_t ID) {
        return ((ID * knuth) >> (32 - this->sizeExponent)) % tableSize;  // TODO check
    }

    void put(int price, size_t ID) {
        size_t newIndex = generateHash(ID);
        if (hashVector.at(newIndex) == 0) {
            hashVector.at(newIndex) = new HashNode(price, ID);
        } else {
            HashNode *currNode = hashVector.at(newIndex);
            while (currNode->nextNode != nullptr) {
                currNode = currNode->nextNode;
            }
            currNode->nextNode = new HashNode(price, ID);
        }
    }

    bool get(size_t ID, HashNode &node) {
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

    bool getPrev(size_t ID, HashNode &node) {
        size_t newIndex = generateHash(ID);
        HashNode *initElem = hashVector.at(newIndex);
        HashNode *prevElem;
        while (initElem != nullptr) {
            if (initElem->ID == ID) {
                node = *prevElem;
                return true;
            }
            prevElem = initElem;
            initElem = initElem->nextNode;
        }
        return false;
    }

    int sizeExponent;
    int tableSize;
    vector<HashNode *> hashVector;
    bool del(size_t ID);
    void print();
};

bool HashTable::del(size_t ID) {
    HashNode *currNode;
    HashNode *prevNode;
    bool res = get(ID, *currNode);
    bool prev = getPrev(ID, *prevNode);
    if (prev == true) prevNode->nextNode = currNode->nextNode;
    if (res == true) {
        delete currNode;
    }
    return false;
}

void HashTable::print() {
    for (int i = 0; i < hashVector.size(); i++) {
        cout << hashVector.at(i)->ID << endl;
        cout << "start linked list" << endl;
        if (hashVector.at(i)->nextNode != nullptr) {
            HashNode *tempElem = hashVector.at(i);
            while (tempElem->nextNode != nullptr) {
                cout << tempElem->nextNode->ID << endl;
                tempElem = tempElem->nextNode;
            }
            cout << "endl linked list" << endl;
        }
    }
}