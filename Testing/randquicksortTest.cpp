#include "../algorithms/randquicksort.cpp"
#include "../imports/importsGlobal.hpp"
#include "catch.hpp"
using namespace std;

/*
* -------- TEST 1 ---------
* Simple tests for the random quick sort algorithm
* ---- 1.1: Tests add functionality
*
*/
TEST_CASE("1.1: Check if sorts correctly", "[multi-file:1]") {
    vector<float> test1{10, 4, 6, 2, 1, 6};
    randQuickSort(&test1, 0, test1.size() - 1);
    for (int i = 0; i < test1.size() - 1; i++) {
        REQUIRE(test1[i] <= test1[i + 1]);
    }
}
