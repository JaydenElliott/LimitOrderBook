#include "importsGlobal.hpp"
#pragma once

using namespace std;

const float golden_ratio = 0.61803398875;
const uint32_t knuth = 2654435769;  // 0.6180339887*(2^32)
const int tblpower = 27;
const int tablesize = pow(2, tblpower);

vector<int> vector1(tablesize, 0);

//knuth number
uint32_t hashmult(uint32_t k) {
    return (k * knuth) >> (32 - tblpower);
}

// int main() {
//     int max = 0;
//     int n1 = 1000000;
//     int n2 = 10000000;
//     float test = 111111 >> 0;
//     for (int i = n1; i < n2; i++) {
//         if (i > tablesize) {
//             cout << i << endl;
//             throw runtime_error("BAD");
//         }
//         vector1.at(hashmult(i)) += 1;
//     }

//     for (int i : vector1) {
//         if (i > max) {
//             max = i;
//         }
//     }

//     float percentage_collision = max / (n2 - n1);

//     cout << "for " << n2 - n1 << " hashes, with a hash table size of 2^" << tblpower << " or " << tablesize << endl;
//     cout << "load factor is " << float(((n2 - n1) / tablesize)) << endl;
//     cout << "the max collisions is " << max << endl;
//     cout << "the percentage collision rate is " << percentage_collision << endl;
//     cout << "memory usage in mbbytes " << sizeof(uint32_t) * vector1.capacity() / 1000000 << endl;
//     cout << endl;
//     cout << test;

//     return 0;
// }