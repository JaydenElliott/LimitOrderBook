#include "../datastructures/Hashtable.hpp"

#include "catch.hpp"
using namespace std;

HashTable testTable;
TEST_CASE("1.1: Create Table", "[multi-file:1]") {
    REQUIRE_NOTHROW(testTable = HashTable(20));
}

TEST_CASE("1.2: Insert Entry", "[multi-file:1]") {
    testTable.insert(30, 11111);
    HashNode node;
    REQUIRE(testTable.get(11111, node));
}

TEST_CASE("1.3: Valid LinkedList", "[multi-file:1]") {
    testTable = HashTable(1);
    testTable.insert(30, 11211);
    testTable.insert(28, 11161);
    testTable.insert(22, 11811);
    testTable.insert(19, 11111);
    HashNode node;
    REQUIRE(testTable.get(11111, node));
    REQUIRE(node.price == 19);
}

TEST_CASE("1.4: Delete Entry", "[multi-file:1]") {
    testTable = HashTable(0);
    testTable.insert(30, 11211);
    testTable.del(11211);
    REQUIRE(testTable.hashVector.at(0) == 0);
}

