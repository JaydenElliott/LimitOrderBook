#include "../imports/importsGlobal.hpp"
#include "hashtable.hpp"
#include "node.hpp"
#include "rbtree.hpp"

using namespace std;

int main() {
    //  ---------------HASHTABLE-- ------------  //
    RBtree testRB2("buy");
    HashTable testTable2(0);
    Node *test21node = new Node(13, 111);
    // Node *test22node = new Node(12, 110);

    testTable2.insert(test21node->price, test21node->ID, test21node, testRB2);
    // testTable2.insert(test21node->price, test21node->ID, test2node, testRB2);
    testTable2.del(111, testRB2);

    //---------------RBTREE--------------//

    // RBtree buytree = RBtree("buy");
    // Node* ins1 = new Node(12, 111);
    // Node* ins2 = new Node(15, 114);
    // Node* ins3 = new Node(18, 131);
    // Node* ins4 = new Node(20, 122);
    // Node* ins5 = new Node(11, 191);
    // Node* ins6 = new Node(11, 171);
    // Node* ins7 = new Node(10, 16);

    // buytree.insert_price(ins1);
    // buytree.insert_price(ins2);
    // buytree.insert_price(ins3);
    // buytree.insert_price(ins4);
    // buytree.insert_price(ins5);
    // buytree.insert_price(ins6);
    // buytree.insert_price(ins7);

    // // buytree.preorderPrint(buytree.root);

    // cout << buytree.buyMax->price << endl;
    // buytree.delete_price(ins4);
    // cout << buytree.buyMax->price << endl;

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