

#include "../importsGlobal.hpp"
#include "Hashtable.hpp"
#include "Node.hpp"
#include "Rbtree.hpp"
// #include "Rbtree.hpp"

using namespace std;

int main() {
    //---------------HASHTABLE--------------//
    HashTable testTable;
    testTable = HashTable(1);
    testTable.put(30, 11211);
    // testTable.put(28, 11161);
    // testTable.put(22, 11811);
    // testTable.put(19, 11111);
    cout << "!!! start print 1 !!!" << endl;
    testTable.print();
    cout << "!!! end print 1 !!!" << endl;
    cout << endl;
    cout << "!!! start delele !!!" << endl;
    bool a = testTable.del(11211);
    cout << (a ? "true" : "false") << endl;
    cout << "!!! finish delele !!!" << endl;
    cout << endl;

    cout << testTable.hashVector.at(1)->ID << endl;

    //---------------RBTREE--------------//

    // RBtree testing = RBtree("buy");

    // testing.insert_price("") return 0;
}