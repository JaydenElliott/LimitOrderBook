#include "../imports/importsGlobal.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

float getRandInRange(float min_value, float max_value_inc) {
    uniform_int_distribution<> distr(min_value, max_value_inc);
    return distr(gen);
}

int main() {
    int n = 500000;
    ofstream myfile;
    myfile.open("main/test_files/test-fi-5.txt");
    myfile << n << endl;
    for (int i = 1; i <= n; i++) {
        srand((unsigned int)time(0));
        string ordertype;
        float randprice;
        if (i % 2 == 0) {
            ordertype = "buy";
            float randprice = getRandInRange(50, 100);
            myfile << ordertype << " " << randprice << endl;
        } else {
            ordertype = "sell";
            float randprice = getRandInRange(80, 130);
            myfile << ordertype << " " << randprice << endl;
        }
    }
    myfile.close();
    return 0;
}