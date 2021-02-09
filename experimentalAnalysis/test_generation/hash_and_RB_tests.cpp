#include "../../imports/importsGlobal.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

float getRandInRange(float min_value, float max_value_inc) {
    uniform_int_distribution<> distr(min_value, max_value_inc);
    return distr(gen);
}

int main() {
    int n = 10000;
    ofstream myfile;
    myfile.open("hashtableExperimental/test-fi-1.txt");
    myfile << n << endl;
    for (int i = 1; i <= n; i++) {
        float rand = getRandInRange(50, 100);
        myfile << "buy " << rand << endl;
    }
    myfile.close();
    return 0;
}