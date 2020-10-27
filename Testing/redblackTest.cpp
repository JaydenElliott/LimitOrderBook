#include "../datastructures/hashtable.hpp"
#include "../datastructures/node.hpp"
#include "../datastructures/rbtree.hpp"
#include "catch.hpp"
using namespace std;

RBtree buytree = RBtree("buy");
HashTable testTableRB = HashTable(5);
TEST_CASE("1.1: Insert Elements and Fix-Up", "[multi-file:1]") {
    Node* ins1 = new Node(12, 111);
    Node* ins2 = new Node(15, 114);
    Node* ins3 = new Node(18, 131);
    Node* ins4 = new Node(13, 171);
    REQUIRE_NOTHROW(buytree.insert_price(ins1));
    REQUIRE_NOTHROW(buytree.insert_price(ins2));
    REQUIRE_NOTHROW(buytree.insert_price(ins3));
    REQUIRE_NOTHROW(buytree.insert_price(ins4));
}

RBtree buytree2 = RBtree("buy");
TEST_CASE("1.2: Delete Elements", "[multi-file:1]") {
    Node* ins1 = new Node(12, 111);
    Node* ins2 = new Node(15, 114);
    Node* ins3 = new Node(18, 131);
    Node* ins4 = new Node(13, 171);
    REQUIRE_NOTHROW(buytree2.insert_price(ins1));
    REQUIRE_NOTHROW(buytree2.insert_price(ins2));
    REQUIRE_NOTHROW(buytree2.insert_price(ins3));
    REQUIRE_NOTHROW(buytree2.insert_price(ins4));
    REQUIRE_NOTHROW(buytree2.delete_price(ins1));
    REQUIRE_NOTHROW(buytree2.delete_price(ins2));
    REQUIRE_NOTHROW(buytree2.delete_price(ins3));
    REQUIRE_NOTHROW(buytree2.delete_price(ins4));
}

TEST_CASE("1.3: Search Tree", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.search_tree(12, 111));
}

TEST_CASE("1.3: Print Tree", "[multi-file:1]") {
    REQUIRE_NOTHROW(buytree.preorderPrint(buytree2.root));
}
