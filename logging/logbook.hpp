#include <chrono>  // chrono::system_clock
#include <ctime>   // localtime
#include <fstream>
#include <iomanip>  // put_time
#include <iostream>
#include <sstream>
#include <string>

#include "../imports/importsGlobal.hpp"

using namespace std;
using namespace std::chrono;

// Files to be written to
#define executedfile "logging/executedOrders.txt"
#define allOrdersFile "logging/allOrders.txt"

/** Class for logging orders orders
 */
class Orderlogbook {
   public:
    Orderlogbook() {
        this->executedOrders.open(executedfile, ios_base::app);
        this->allOrders.open(allOrdersFile, ios_base::app);
    }
    vector<float> allOrdersVec;
    vector<float> executedOrdersVec;
    ofstream allOrders;
    ofstream executedOrders;
    string getdatetime();
    void writeExecuteOrder(float price, string buyID, string sellID);
    void add(string type, float price);
};

/** Returns current date-time in year-month-day hour-minute-second format
 */
string Orderlogbook::getdatetime() {
    auto chronotime = system_clock::to_time_t(system_clock::now());
    stringstream dateTime;
    dateTime << put_time(localtime(&chronotime), "%Y-%m-%d %X");
    return dateTime.str();
}

/**
 * Add order to the log file
 * @param type:  executed, overall
 */
void Orderlogbook::add(string type, float price) {
    if (type == "executed") {
        executedOrdersVec.push_back(price);
    } else if (type == "overall") {
        // executedOrdersVec.push_back(price);
        allOrdersVec.push_back(price);
    } else {
        throw runtime_error("order type invalid ");
    }
}

/**
 *
 * Function to log all executed trades
 * - Writes to file: executedOrders.txt
 * - Format:  date (yyyy-mm-dd),    time (hh:mm:ss),    price,    buyid,    sellid
 * 
 * @param price: executed trade price
 * @param buyID: ID of buyer at price
 * @param sellID: ID of seller at price
 */
void Orderlogbook::writeExecuteOrder(float price, string buyID, string sellID) {
    if (this->executedOrders.is_open()) {
        string time = getdatetime();
        executedOrders << time << " " << price << " " << buyID << " " << sellID << " "
                       << endl;
        ;
    } else {
        throw runtime_error("Could not open file ... " + string(executedfile));
    }
}
