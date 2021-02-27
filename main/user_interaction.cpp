#include <chrono>

#include "../algorithms/randquicksort.cpp"
#include "../algorithms/statistics.hpp"
#include "../datastructures/hashtable.hpp"
#include "../datastructures/node.hpp"
#include "../datastructures/queue.hpp"
#include "../datastructures/rbtree.hpp"
#include "../logging/logbook.hpp"

using namespace std;
using namespace std::chrono;

/**
 * ---------------- Description ----------------
 * Interface function between statistics class
 * and user
 * ---------------- Parameters ----------------
 * toget:  min,max,quartiles, median, print
 * allOrder: false = executed orders only. true = all
 */

void getStatistics(string toget, Statistics &statClass, Orderlogbook &logbook) {
    randQuickSort(&logbook.allOrdersVec, 0, logbook.allOrdersVec.size() - 1);
    randQuickSort(&logbook.executedOrdersVec, 0, logbook.executedOrdersVec.size() - 1);

    statClass.executedOrders = logbook.executedOrdersVec;
    statClass.allOrders = logbook.allOrdersVec;
    if (toget == "all") {
        statClass.printStatistics();
    } else if (toget == "max") {
        statClass.getmax();
    } else if (toget == "median") {
        statClass.getmedian();
    } else if (toget == "quartiles") {
        tuple<float, float, float> quartiles = statClass.getquartiles();
        cout << endl;
        cout << "Quartiles:" << endl;
        cout << "Q1 = " << get<0>(quartiles) << endl;
        cout << "Q2 = " << get<1>(quartiles) << endl;
        cout << "Q3 = " << get<2>(quartiles) << endl;

    } else if (toget == "min") {
        // cout << statClass.getmin() << endl;
    } else {
        throw runtime_error("getStatistics incorrect parameter entry");
    }
}

/**
 * ---------------- Description ----------------
 * Handles order execution. Will be called by
 * "newOrder()" when a sell order is matched to
 *  a buy order
 *
 * ---------------- Parameters ----------------
 * todelete:    delete buy or sell node
 * logtrades:   true/false (do you want to record trades)
 * buyorderID:  order price
 * sellorderID: order ID
 * price:       order price
 * buytree:     reference to the buytree
 * selltree:    reference to the selltree
 * htable:      reference to the hashtable
 * orderlog:    reference to the file responsible for logging orders
*/
void executeorder(string todelete, bool logtrades, string buyorderID, string sellorderID, int price, RBtree &buytree, RBtree &selltree, HashTable &htable, Orderlogbook &orderlog) {
    if (todelete == "sell") {  // sell order
        if (logtrades) {
            orderlog.writeExecuteOrder(price, buyorderID, sellorderID);
        }
        htable.del(sellorderID, selltree);
    } else if (todelete == "buy") {
        if (logtrades) {
            orderlog.writeExecuteOrder(price, buyorderID, sellorderID);
        }
        htable.del(buyorderID, buytree);
    } else if (todelete == "both") {
        orderlog.writeExecuteOrder(price, buyorderID, sellorderID);
        htable.del(sellorderID, selltree);
        htable.del(buyorderID, buytree);
    }
}

/**
 * ---------------- Description ----------------
 * Processes the new orders and sends them to
 the right functions / datastructures
 *
 * ---------------- Parameters ----------------
 * ordertype:  buy, sell, delete_sell, delete_buy
 * logtrades:  true/false (do you want to record trades)
 * price:      order price
 * ID:         order ID
 * buytree:    reference to the buytree
 * selltree:   reference to the selltree
 * htable:     reference to the hashtable
 * orderlog:   reference to the file responsible for logging orders
*/
void newOrder(string ordertype, bool logtrades, float price, string ID, RBtree &buytree, RBtree &selltree, HashTable &htable, Orderlogbook &orderlog) {
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            //Buy price >= max sell price ----- Order can be executed immediately
            executeorder("sell", logtrades, ID, selltree.sellMin->ID, price, buytree, selltree, htable, orderlog);
            orderlog.add("executed", price);
        } else {
            htable.insert(price, ID, new Node(price, ID), buytree);
            orderlog.add("overall", price);
        }
    } else if (ordertype == "sell") {
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            //Sell price <= max sell price ----- Order can be executed immediately
            executeorder("buy", logtrades, buytree.buyMax->ID, ID, price, buytree, selltree, htable, orderlog);
            orderlog.add("executed", price);
        } else {
            htable.insert(price, ID, new Node(price, ID), selltree);
            orderlog.add("overall", price);
        }
    } else if (ordertype == "delete_sell") {
        htable.del(ID, selltree);
    } else if (ordertype == "delete_buy") {
        htable.del(ID, buytree);
    } else {
        throw runtime_error("Invalid input. Valid input: buy, sell, delete");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } else {
        // Instantiate classes
        RBtree sellTree = RBtree("sell");
        RBtree buyTree = RBtree("buy");
        HashTable table = HashTable(24);
        Orderlogbook orderlog = Orderlogbook();
        Statistics stats = Statistics();

        ifstream inFile(argv[1]);
        if (inFile.is_open()) {
            // Read input
            ifstream inFile(argv[1]);
            int n;  // number of orders
            inFile >> n;

            vector<tuple<string, float, string> > insertOrders(n);

            // Read orders and generate an order ID for each
            string insertOrderType;  // buy, sell, delete-buy, delete-sell
            float price;
            for (int i = 0; i < n; i++) {
                inFile >> insertOrderType >> price;
                string ID = generate_uuid();
                insertOrders.at(i) = tuple<string, float, string>(insertOrderType, price, ID);
            }         
            // ------- PROCESS ORDERS ------- //
            for (int i = 0; i < n; i++) {
                // Generate orders
                newOrder(get<0>(insertOrders.at(i)),
                         true,
                         get<1>(insertOrders.at(i)),
                         get<2>(insertOrders.at(i)),
                         buyTree,
                         sellTree,
                         table,
                         orderlog);
            }
            // getStatistics("all", stats, orderlog);  // Uncomment this line to see statistics
        }
    }
}
