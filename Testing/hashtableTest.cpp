#include "../datastructures/hashtable.hpp"
#include "../datastructures/node.hpp"
#include "../datastructures/rbtree.hpp"
#include "catch.hpp"
using namespace std;

/*
* -------- TEST 1 ---------
* Tests basic functionality of hash-table
* ---- 1.1: Instantiation/Hash table build is functional (also tests get functionality on regular elements)
* ---- 1.2: Insert hash entry is working
* ---- 1.3: Linked-list chaining is functional (also tests get functionality on "chained" elements)
* ---- 1.4: Delete method is functional
*/
HashTable testTable;
RBtree testRB("buy");
Node *test12node = new Node(14, "test11");
TEST_CASE("1.1: Create Table", "[multi-file:1]") {
    REQUIRE_NOTHROW(testTable = HashTable(20));
}

TEST_CASE("1.2: Insert Entry", "[multi-file:1]") {
    testTable.insert(30, "test12", test12node, testRB);
    HashNode node12;
    REQUIRE_NOTHROW(testTable.get("test12", node12));
    REQUIRE(node12.price == 30);
}

Node *test131node = new Node(14, "test131");
Node *test132node = new Node(12, "test132");
Node *test133node = new Node(15, "test133");
TEST_CASE("1.3: Valid LinkedList", "[multi-file:1]") {
    testTable = HashTable(1);
    testTable.insert(test131node->price, test131node->ID, test131node, testRB);
    testTable.insert(test132node->price, test132node->ID, test132node, testRB);
    testTable.insert(test133node->price, test133node->ID, test133node, testRB);
    HashNode node;
    REQUIRE_NOTHROW(testTable.get("test131", node));
    REQUIRE(node.price == 14);
}

TEST_CASE("1.4: Delete Entry", "[multi-file:1]") {
    testTable = HashTable(0);
    Node *test14node = new Node(40, "test14");
    testTable.insert(30, "test14", test14node, testRB);
    testTable.del("test14", testRB);
    REQUIRE(testTable.hashVector.at(0) == 0);
}

/*
* -------- TEST 2 ---------
* Tests the link between the hash table and RB tree is working
* ---- 2.1: Tests if the pointer stored in hashtable is maintained
* ---- 2.2: Tests if deletion in table deletes RB node.
*/
RBtree testRB2("buy");
HashTable testTable2(0);
Node *test21node = new Node(13, "test21");
TEST_CASE("2.1:  HashTable / RBtree insert link working", "[multi-file:1]") {
    testTable2.insert(test21node->price, test21node->ID, test21node, testRB2);
    REQUIRE(testTable2.hashVector.at(0)->rbNode->price == 13);
}

TEST_CASE("2.2:  Delete Order -> hashtable ->  rbtree", "[multi-file:1]") {
    REQUIRE_NOTHROW(testTable2.del("test21", testRB2));
    REQUIRE_THROWS(testRB2.search_tree(13, "test21"));
}
