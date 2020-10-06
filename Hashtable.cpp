#include <cmath>
#include <string>

#include "rbtree.h"
using namespace std;

const uint32_t knuth = 2654435769;
const int tblpower = 10;
const int tablesize = pow(2, tblpower);

vector<int> vector1(tablesize, 0);

//knuth number
uint32_t hashmult(uint32_t k) {
    return (k * knuth) >> (32 - tblpower);
}

int main() {
    int max = 0;
    for (int i = 1000000; i < 90000000; i++) {
        vector1.at(hashmult(i)) += 1;
    }

    for (int i : vector1) {
        if (i > max) {
            max = i;
        }
    }

    float percentage_collision = max / (90000000 - 1000000);
    cout << max << endl;
    cout << percentage_collision;
    return 0;
}