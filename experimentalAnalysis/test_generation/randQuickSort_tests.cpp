#include "../../imports/importsGlobal.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

float getRandInRange(float min_value, float max_value_inc) {
    uniform_int_distribution<> distr(min_value, max_value_inc);
    return distr(gen);
}
// [10000,50000,200000,400000,500000]
int main() {
    int n = 500000;
    ofstream myfile;
    myfile.open("randsortExperimental/test-fi-5.txt");
    myfile << n << endl;
    for (int i = 1; i <= n; i++) {
        float rand = getRandInRange(50, 100);
        myfile << rand << endl;
    }
    myfile.close();
    return 0;
}