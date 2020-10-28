#include "../imports/importsGlobal.hpp"
#include "hashtable.hpp"
#include "node.hpp"
#include "rbtree.hpp"

using namespace std;

int main() {
    //  ---------------HASHTABLE-- ------------  //
    // HashTable testTable;
    // testTable = HashTable(0);
    // testTable.insert(30, 11211);
    // testTable.insert(28, 11161);
    // // testTable.insert(22, 11811);
    // // testTable.insert(19, 11111);
    // cout << endl;
    // cout << "Before" << endl;
    // testTable.print();
    // cout << endl;
    // cout << "After" << endl;
    // testTable.del(11161);
    // testTable.del(11211);
    // testTable.print();
    // // cout << testTable.hashVector.at(0) << endl;
    // cout << "!!! end print 1 !!!" << endl;

    //---------------RBTREE--------------//

    RBtree buytree = RBtree("buy");
    Node* ins1 = new Node(12, 111);
    Node* ins2 = new Node(15, 114);
    Node* ins3 = new Node(18, 131);
    Node* ins4 = new Node(20, 122);
    Node* ins5 = new Node(11, 191);
    Node* ins6 = new Node(11, 171);
    Node* ins7 = new Node(10, 16);

    buytree.insert_price(ins1);
    buytree.insert_price(ins2);
    buytree.insert_price(ins3);
    buytree.insert_price(ins4);
    buytree.insert_price(ins5);
    buytree.insert_price(ins6);
    buytree.insert_price(ins7);

    buytree.preorderPrint(buytree.root);

    //---------------BOTH--------------//
    // HashTable testTable = HashTable(2);
    // RBtree testTree = RBtree("buy");
    // Node *test = new Node(4, 1111);
    // Node *test2 = new Node(5, 1121);

    // testTable.insert(test->price, test->ID, test, testTree);
    // testTable.insert(test2->price, test2->ID, test2, testTree);

    // cout << "Printing table ... " << endl;
    // testTable.print();
    // cout << endl;
    // cout << "Printing tree ... " << endl;
    // testTree.preorderPrint(testTree.root);

    // cout << endl;
    // cout << "indexing link" << endl;

    // cout << testTable.hashVector[2]->rbNode->price << endl;
    // cout << testTable.hashVector[2]->price << endl;

    // cout << endl;

    // cout << testTable.hashVector[3]->rbNode->ID << endl;
    // cout << testTable.hashVector[3]->ID << endl;

    return 0;
}