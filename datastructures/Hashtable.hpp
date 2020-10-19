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
        this->hashVector = vector<HashNode *>(tableSize, nullptr);
    }
    // ~HashTable() {
    //     for (int i = 0; i < hashVector.size(); i++) {
    //         cout << "iter " << i << endl;
    //         HashNode *currnode = hashVector.at(i);

    //         while (currnode != nullptr) {
    //             HashNode *tempNode = currnode;
    //             cout << "HERE " << currnode << endl;
    //             currnode = currnode->nextNode;
    //             delete tempNode;
    //         }
    //         hashVector.at(i) = nullptr;
    //     }
    //     cout << "end destruct" << endl;
    // };

    int sizeExponent;
    int tableSize;
    vector<HashNode *> hashVector;
    bool del(size_t ID);
    void print();
    bool getelem(size_t ID);
    bool get(size_t ID, HashNode &node);
    void put(int price, size_t ID);
    size_t generateHash(size_t ID);
};

size_t HashTable::generateHash(size_t ID) {
    return ((ID * knuth) >> (32 - this->sizeExponent)) % tableSize;  // TODO check
}

void HashTable::put(int price, size_t ID) {
    size_t newIndex = generateHash(ID);
    if (hashVector[newIndex] == nullptr) {
        hashVector[newIndex] = new HashNode(price, ID);
    } else {
        HashNode *currNode = hashVector[newIndex];
        while (currNode->nextNode != nullptr) {
            currNode = currNode->nextNode;
        }
        currNode->nextNode = new HashNode(price, ID);
    }
}

bool HashTable::get(size_t ID, HashNode &node) {
    size_t newIndex = generateHash(ID);
    HashNode *initElem = hashVector.at(newIndex);
    cout << initElem->ID << endl;
    while (initElem != nullptr) {
        if (initElem->ID == ID) {
            cout << "!! 1 !!" << endl;
            node = *initElem;
            cout << "!! 2 !!" << endl;
            return true;
        }
        initElem = initElem->nextNode;
    }
    return false;
}

bool HashTable::del(size_t ID) {
    size_t Index = generateHash(ID);
    HashNode *currNode = hashVector[Index];
    HashNode *prevNode = nullptr;

    if (currNode == nullptr) {
        cout << "Already deleted" << endl;
        return false;
    }

    while (currNode != nullptr && currNode->ID != ID) {
        prevNode = currNode;
        currNode = currNode->nextNode;
    }
    if (currNode == nullptr) {
        cout << "a;lskdjf;kl" << endl;
        return false;
    }
    if (prevNode == nullptr) {
        cout << "condit 1" << endl;
        this->hashVector[Index] = currNode;
        cout << "hashy" << hashVector[Index]->ID << endl;
        cout << "currnode = " << currNode->ID << endl;
        // cout << hashVector[Index] << endl;
        // cout << currNode->ID << endl;

    } else {
        cout << "condit 2" << endl;
        prevNode->nextNode = currNode;
    }

    cout << "hashy2 = " << hashVector[Index]->ID << endl;
    cout << "currnode2 = " << currNode->ID << endl;
    delete currNode;
    currNode = nullptr;
    cout << "currnode2 = " << currNode << endl;
    cout << "hash vector urg" << hashVector[Index] << endl;
    // cout << currNode->ID << endl;
    return true;
}

void HashTable::print() {
    for (int i = 0; i < hashVector.size(); i++) {
        if (hashVector.at(i) == nullptr) {
            continue;
        }
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