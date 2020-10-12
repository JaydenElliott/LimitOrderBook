#pragma once
#include "../datastructures/Hashtable.hpp"

#include "catch.hpp"
using namespace std;

HashTable testTable;
TEST_CASE("1.1: Create Table", "[multi-file:1]") {
    REQUIRE_NOTHROW(testTable = HashTable(20));
}

TEST_CASE("1.2: Insert Entry", "[multi-file:1]") {
    testTable.put(30, 11111);
    HashNode node;
    REQUIRE(testTable.get(11111, node));
}

TEST_CASE("1.3: Valid LinkedList", "[multi-file:1]") {
    testTable = HashTable(1);
    testTable.put(30, 11211);
    testTable.put(28, 11161);
    testTable.put(22, 11811);
    testTable.put(19, 11111);
    HashNode node;
    REQUIRE(testTable.get(11111, node));
    REQUIRE(node.price == 19);
}