#include "../imports/importsGlobal.hpp"
using namespace std;

// make a struct that when initilised sorts data !!!

class Statistics {
   public:
    // Class variables
    vector<float> executedOrders;
    vector<float> allOrders;

    // Class methods
    float getmin();
    float getmax();
    void printStatistics();
    vector<float> getmedian();
    tuple<float, float, float> getquartiles();
};

float Statistics::getmin() {
    return executedOrders.at(0);
}

float Statistics::getmax() {
    return executedOrders.back();
}

/**
 * Ordertype: overall, executed 
 */
void Statistics::printStatistics() {
    cout << "\n"
         << endl;
    cout << "------------ Trading Order Statistics  ------------"
         << "\n \n";
    cout << "Number of executed orders = " << executedOrders.size() << endl;
    cout << "Number of total orders    = " << allOrders.size() << endl;
    cout << endl;
    cout << "Min executed order price  = " << getmin() << endl;
    cout << "Max executed order price  = " << getmax() << endl;

    tuple<float, float, float> quartiles = getquartiles();
    cout << endl;
    cout << "Quartiles:" << endl;
    cout << "Q1 = " << get<0>(quartiles) << endl;
    cout << "Q2 = " << get<1>(quartiles) << endl;
    cout << "Q3 = " << get<2>(quartiles) << endl;

    cout << endl;
}

/**
 * Either returns int or tuple (int,int);
 */

vector<float> Statistics::getmedian() {
    vector<float> medians;
    int len = executedOrders.size() - 1;
    if ((len + 1) % 2 == 0) {
        medians.push_back(executedOrders.at(len / 2));
        medians.push_back(executedOrders.at(len / 2) + 1);
        return medians;
    } else {
        medians.push_back(executedOrders.at(len / 2));
        return medians;
    }
}

/**
 * Gets upper and lower quartile (25% and 75%)
 * returns tuple of quartiles
 * q1 = 25% of data below
 * q2 = median
 * q3 = 75% data below
 * rounded down
 */

tuple<float, float, float> Statistics::getquartiles() {
    int q1Idx = (executedOrders.size() + 1) * (1.0 / 4);
    int q2Idx = (executedOrders.size() + 1) / 2.0;
    int q3Idx = (executedOrders.size() + 1) * (3.0 / 4);

    return make_tuple(executedOrders.at(q1Idx - 1), executedOrders.at(q2Idx - 1), executedOrders.at(q3Idx - 1));
}
