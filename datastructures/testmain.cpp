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

    RBtree testing = RBtree("buy");
    Node *test = new Node(4, 1111);
    Node *test2 = new Node(5, 1121);

    testing.insert_price(test);
    testing.insert_price(test2);
    testing.preorderPrint(testing.root);
    return 0;
}