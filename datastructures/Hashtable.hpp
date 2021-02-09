

#include "../imports/importsGlobal.hpp"
#include "node.hpp"
#include "rbtree.hpp"
#pragma once

using namespace std;
using namespace std::chrono;

// For second hash function
#define offsetbasis 2166136261
#define fnvprime 16777619

class HashNode {
   public:
    HashNode(){};
    HashNode(float price, string ID, Node *rbNode) {
        this->price = price;
        this->ID = ID;
        this->rbNode = rbNode;
    }

    float price;
    string ID;
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
    void del(string ID, RBtree &rbtree);
    void print();
    bool get(string ID, HashNode &node);
    void insert(int price, string ID, Node *rbnode, RBtree &tree);
    unsigned int generateHash(string uuid);
};

/**
 * Modified implementation of the FNV-1a hash
 */
unsigned int HashTable::generateHash(string uuid) {
    // check that its even
    if (uuid.length() % 2 != 0) {
        uuid.append("a");
    }
    unsigned int hash = offsetbasis;
    for (int i = 0; i < uuid.length() - 2; i += 2) {
        unsigned int octet = (uuid[i] << 4) + uuid[i + 1];
        hash = (hash ^ octet);
        hash *= fnvprime;
    }
    return hash % this->tableSize;
}
void HashTable::insert(int price, string ID, Node *rbnode, RBtree &tree) {
    unsigned int newIndex = generateHash(ID);
    if (newIndex > this->tableSize) {
        throw runtime_error("TOO LARGE HASH");
    }
    tree.insert_price(rbnode);  // COMMENT OUT when conducting hash table timing tests
    if (hashVector.at(newIndex) == nullptr) {
        hashVector.at(newIndex) = new HashNode(price, ID, rbnode);
    } else {
        HashNode *currNode = hashVector.at(newIndex);
        while (currNode->nextNode != nullptr) {
            currNode = currNode->nextNode;
        }
        if (currNode != nullptr && currNode->ID == ID) {
            currNode->price = price;

            return;
        }
        if (currNode == nullptr) {
            hashVector.at(newIndex) = new HashNode(price, ID, rbnode);
        } else {
            currNode->nextNode = new HashNode(price, ID, rbnode);
        }
    }
}

/**
 * In place 'get' node from hashtable function
 * Returns true if node was found
 */
bool HashTable::get(string ID, HashNode &node) {
    unsigned int newIndex = generateHash(ID);
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

/**
 * In-place delete. 
 * Throws error if node does not exist
 */
void HashTable::del(string ID, RBtree &rbtree) {
    unsigned int Index = generateHash(ID);
    if (hashVector.at(Index) != nullptr) {
        HashNode *currNode = hashVector.at(Index);
        HashNode *prevNode = nullptr;

        while (currNode != nullptr && currNode->ID != ID) {
            prevNode = currNode;
            currNode = currNode->nextNode;
        }

        if (currNode == nullptr) {
            throw runtime_error("Node to delete does not exist");
        }
        if (currNode->ID == ID) {
            HashNode *nextnode = currNode->nextNode;
            rbtree.delete_price(currNode->rbNode);  // COMMENT OUT when conducting hash table timing tests
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

// Random number generator
random_device rd2;
mt19937 gen2(rd2());

int getRand() {
    uniform_int_distribution<> distr(0, 255);
    return distr(gen2);
}
/**
 * Generates an adapted shortnered universally
 * unique identifier (uuid)
 */
string generate_uuid() {
    stringstream uuid;
    auto start = high_resolution_clock::now();  // find the date
    uint64_t microsec = duration_cast<microseconds>(high_resolution_clock::now().time_since_epoch()).count();
    for (int i = 0; i < 10; i++) {
        unsigned int rc = getRand();
        stringstream hs;
        hs << hex << rc;
        string hex = hs.str();
        if (hex.length() < 2) {
            uuid << '0' + hex;
        } else {
            uuid << hex;
        }
    }

    uuid << microsec;
    return uuid.str();
}