#include "../datastructures/hashtable.hpp"
#include "../datastructures/node.hpp"
#include "../datastructures/rbtree.hpp"
#include "catch.hpp"
using namespace std;

/*
* -------- TEST 1 ---------
* Tests basic functionality of RB_tree
* ---- 1.1: Insert is functional.
* ---- 1.2: Fix-up places nodes in the correct order 
* ---- 1.3: Delete is functional. Checks searching for deleted item return error.
* ---- 1.4: Search return proper node.
* ---- 1.5: Printing tree works doesn't return error.
*/
RBtree buytree = RBtree("buy");
HashTable testTableRB = HashTable(5);
Node* ins1 = new Node(12, "test1");
Node* ins2 = new Node(15, "test2");
Node* ins3 = new Node(18, "test3");
Node* ins4 = new Node(20, "test4");
Node* ins5 = new Node(11, "test5");
Node* ins6 = new Node(10, "test6");

TEST_CASE("1.1: Insert Elements", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.insert_price(ins1));
    REQUIRE_NOTHROW(buytree.insert_price(ins2));
    REQUIRE_NOTHROW(buytree.insert_price(ins3));
    REQUIRE_NOTHROW(buytree.insert_price(ins4));
    REQUIRE_NOTHROW(buytree.insert_price(ins5));
    REQUIRE_NOTHROW(buytree.insert_price(ins6));
    buytree.preorderPrint(buytree.root);
}

TEST_CASE("1.2: Fix-up", "[multi-file:1]") {
    REQUIRE(buytree.root->price == 15);
    REQUIRE(buytree.root->right->price == 18);
    REQUIRE(buytree.root->right->right->price == 20);
    REQUIRE(buytree.root->left->price == 11);
    REQUIRE(buytree.root->left->left->price == 10);
    REQUIRE(buytree.root->left->right->price == 12);
}

TEST_CASE("1.3: Delete Elements", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.delete_price(ins1));
    REQUIRE_NOTHROW(buytree.delete_price(ins2));
    REQUIRE_NOTHROW(buytree.delete_price(ins3));
    REQUIRE_THROWS(buytree.search_tree(12, "test1"));
}

TEST_CASE("1.4: Search Tree", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.search_tree(10, "test6"));
}

TEST_CASE("1.5: Print Tree", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.preorderPrint(buytree.root));
}

// For test cases regarding the link between hash table and redblack tree see "hashtableTest.cpp"