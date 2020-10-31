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

#define executedfile "logging/executedOrders.txt"
#define allOrdersFile "logging/allOrders.txt"

class Orderlogbook {
   public:
    Orderlogbook() {
        this->executedOrders.open(executedfile, ios_base::app);
        this->allOrders.open(allOrdersFile, ios_base::app);
    }

    ofstream allOrders;
    ofstream executedOrders;

    string getdatetime();
    void writeExecuteOrder(float price, size_t buyID, size_t sellID);
};

string Orderlogbook::getdatetime() {
    auto chronotime = system_clock::to_time_t(system_clock::now());
    stringstream dateTime;
    dateTime << put_time(localtime(&chronotime), "%Y-%m-%d %X");
    return dateTime.str();
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
void Orderlogbook::writeExecuteOrder(float price, size_t buyID, size_t sellID) {
    if (this->executedOrders.is_open()) {
        string time = getdatetime();
        executedOrders << time << " " << price << " " << buyID << " " << sellID << " "
                       << endl;
        ;
    } else {
        throw runtime_error("Could not open file ... " + string(executedfile));
    }
}
