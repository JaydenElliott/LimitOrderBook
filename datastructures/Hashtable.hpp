#include "../importsGlobal.hpp"
#pragma once

using namespace std;

const size_t knuth = 2654435769;  // (1/golden ratio)*(2^32)

class HashNode {
   public:
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
    HashTable(int sizeExponent) {
        this->sizeExponent = sizeExponent;
        this->hashVector = new vector<HashNode>(tableSize);
    }
    ~HashTable(){};

    size_t generateHash(size_t ID) {
        return (ID * knuth) >> (32 - this->sizeExponent);
    }

    void appendHash(size_t hashIndex, int price, size_t ID) {
        HashNode *newEntry = new HashNode(price, ID);
        u_int32_t newIndex = generateHash(ID);

        if (hashVector.at(newIndex) == 0) {
            hashVector.at(newIndex) = newEntry;
        } else {
            HashNode *currNode = hashVector.at(newIndex);
            while (currNode->nextNode != nullptr) {
                currNode = currNode->nextNode;
            }
            currNode->nextNode = newEntry;
        }
    }

    void deleteHash(size_t hashIndex) {
        ;
    }

    int sizeExponent;
    int tableSize = pow(2, sizeExponent);
    vector<HashNode *> hashVector;

   private:
};

// size_t