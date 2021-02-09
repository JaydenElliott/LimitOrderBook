#include "../datastructures/queue.hpp"
#include "catch.hpp"
using namespace std;

/*
* -------- TEST 1 ---------
* Tests the basic functionality of the custom Queue class
* ---- 1.1: Tests add functionality
* ---- 1.2: Tests delete functionality
*/
Queue testQueue;
TEST_CASE("1.1: Add ID", "[multi-file:1]") {
    testQueue.push("test111");
    testQueue.push("test112");
    testQueue.push("test113");
    testQueue.push("test114");
    REQUIRE(testQueue.size() == 4);
}

TEST_CASE("1.2: Remove ID", "[multi-file:1]") {
    testQueue.pop();
    testQueue.find_and_remove("test112");
    REQUIRE(testQueue.size() == 2);
}
