#include "../importsGlobal.hpp"
#pragma once

using namespace std;

const uint32_t knuth = 2654435769;  // (1/golden ratio)*(2^32)
const int tblpower = 27;
const int tablesize = pow(2, tblpower);

vector<int> hashTable(tablesize, 0);

//knuth number
uint32_t hashmult(uint32_t k) {
    return (k * knuth) >> (32 - tblpower);
}

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