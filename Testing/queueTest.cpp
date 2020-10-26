#include "../datastructures/queue.hpp"
#include "catch.hpp"
using namespace std;

Queue testQueue;

TEST_CASE("1.1: Add ID", "[multi-file:1]") {
    testQueue.push(11111);
    testQueue.push(11111);
    testQueue.push(11141);
    testQueue.push(15111);
    REQUIRE(testQueue.size() == 4);
}

TEST_CASE("1.2: Remove ID", "[multi-file:1]") {
    testQueue.pop();
    testQueue.find_and_remove(11141);
    REQUIRE(testQueue.size() == 2);
}
