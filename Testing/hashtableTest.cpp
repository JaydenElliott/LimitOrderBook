#include "../datastructures/hashtable.hpp"
#include "../datastructures/node.hpp"
#include "../datastructures/rbtree.hpp"
#include "catch.hpp"
using namespace std;

HashTable testTable;
RBtree testRB("buy");

Node *test12node = new Node(14, 111);
TEST_CASE("1.1: Create Table", "[multi-file:1]") {
    REQUIRE_NOTHROW(testTable = HashTable(20));
}

TEST_CASE("1.2: Insert Entry", "[multi-file:1]") {
    testTable.insert(30, 11111, test12node, testRB);
    HashNode node;
    REQUIRE_NOTHROW(testTable.get(11111, node));
}

Node *test13node = new Node(14, 111);
TEST_CASE("1.3: Valid LinkedList", "[multi-file:1]") {
    testTable = HashTable(1);
    testTable.insert(30, 11211, test13node, testRB);
    testTable.insert(28, 11161, test13node, testRB);
    testTable.insert(22, 11811, test13node, testRB);
    testTable.insert(19, 11111, test13node, testRB);
    HashNode node;
    REQUIRE_NOTHROW(testTable.get(11111, node));
    REQUIRE(node.price == 19);
}

TEST_CASE("1.4: Delete Entry", "[multi-file:1]") {
    testTable = HashTable(0);
    Node *test14node = new Node(40, 11211);
    testTable.insert(30, 11211, test14node, testRB);
    testTable.del(11211, testRB);
    REQUIRE(testTable.hashVector.at(0) == 0);
}

// 2.1 SET UP
RBtree testRB2("buy");
HashTable testTable2(0);
Node *test21node = new Node(13, 111);
TEST_CASE("2.1:  Insert Order -> rbtree ->  hashtable", "[multi-file:1]") {
    testRB2.insert_price(test21node);
    HashNode getnode;
    testTable2.get(111, getnode);
    cout << getnode.ID << endl;
    REQUIRE(getnode.price == 13);
}

TEST_CASE("2.2:  Delete Order -> rbtree ->  hashtable", "[multi-file:1]") {
    // REQUIRE_NOTHROW(testRB.delete_price())
}
