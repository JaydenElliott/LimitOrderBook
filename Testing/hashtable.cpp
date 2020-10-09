
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

const uint32_t knuth = 2654435769;  // (1/golden ratio)*(2^32)
const int tblpower = 27;
const int tablesize = pow(2, tblpower);

int main() {
    vector<int> a(1000);
    cout << (a.at(0) == 0 ? "Hi" : "no");
    return 0;
}