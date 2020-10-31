#include <chrono>

#include "datastructures/hashtable.hpp"
#include "datastructures/node.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/rbtree.hpp"
#include "logging/logbook.hpp"

using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());
int getRand() {
    uniform_int_distribution<> distr(0, 255);
    return distr(gen);
}

string generate_uuid() {
    stringstream uuid;
    for (int i = 0; i < 10; i++) {
        unsigned int rc = getRand();
        stringstream hs;
        hs << hex << rc;
        string hex = hs.str();
        if (hex.length() < 2) {
            uuid << '0' + hex;
        } else {
            uuid << hex;
        }
    }
    return uuid.str();
}

/**
 * ---------------- Description ----------------
 * Handles order execution. Will be called by
 * "newOrder()" when a sell order is matched to
 *  a buy order
 *
 * ---------------- Parameters ----------------
 * ordertype:  buy or sell
 * price:      order price
 * ID:         order ID
 * buytree:    reference to the buytree
 * selltree:   reference to the selltree
 * htable:     reference to the hashtable
 * orderlog:   reference to the file responsible for logging orders
*/
void executeorder(string todelete, size_t buyorderID, size_t sellorderID, RBtree &buytree, RBtree &selltree, HashTable &htable, Orderlogbook &orderlog) {
    if (todelete == "sell") {  // sell order
        // push_to_log(buyorder->price, orderlog);  // was causing errors
        htable.del(sellorderID, selltree);
    } else if (todelete == "buy") {
        // push_to_log(buyorder->price, orderlog);  // was causing errors
        htable.del(buyorderID, buytree);
    } else if (todelete == "both") {
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
 * logtrades:  true/false (write to file)
 * price:      order price
 * ID:         order ID
 * buytree:    reference to the buytree
 * selltree:   reference to the selltree
 * htable:     reference to the hashtable
 * orderlog:   reference to the file responsible for logging orders
*/
void newOrder(string ordertype, bool logtrades, float price, size_t ID, RBtree &buytree, RBtree &selltree, HashTable &htable, Orderlogbook &orderlog) {
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            //Buy price >= max sell price ----- Order can be executed immediately
            if (logtrades) {
                executeorder("sell", ID, selltree.sellMin->ID, buytree, selltree, htable, orderlog);
            }
        } else {
            Node *buynode = new Node(price, ID);
            htable.insert(price, ID, buynode, buytree);
        }
    } else if (ordertype == "sell") {
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            //Sell price <= max sell price ----- Order can be executed immediately
            if (logtrades) {
                executeorder("buy", ID, buytree.buyMax->ID, buytree, selltree, htable, orderlog);
            }
        } else {
            Node *sellnode = new Node(price, ID);
            htable.insert(price, ID, sellnode, selltree);
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
    // Insantiate trees and orderlog
    RBtree sellTree = RBtree("sell");
    RBtree buyTree = RBtree("buy");
    HashTable table = HashTable(24);
    Orderlogbook orderlog = Orderlogbook();

    auto start = high_resolution_clock::now();

    int buyorders = 100000;
    for (int i = 1; i <= buyorders; i++) {
        newOrder("buy", false, i, i + 10, buyTree, sellTree, table, orderlog);
    }

    int sellorders = 100000;
    for (int i = 1; i <= sellorders; i++) {
        newOrder("sell", false, i, 1000 + i, buyTree, sellTree, table, orderlog);
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<milliseconds>(end - start);

    cout << "Time taken for " << buyorders + sellorders << " orders = " << duration.count() << " milliseconds" << endl;

    // cout << orderlog.size() << endl;

    // cout << "----- buy tree ------" << endl;
    // buyTree.preorderPrint(buyTree.root);

    // cout << "----- sell tree ------" << endl;
    // sellTree.preorderPrint(sellTree.root);
    // cout << "start orderlog" << endl;
    // for (float i : orderlog) {
    //     cout << i << endl;
    // }

    // newOrder("buy", 100, 1234, buyTree, sellTree, table);
    // newOrder("sell", 50, 333, buyTree, sellTree, table);
    // newOrder("sell", 50, 333, buyTree, sellTree, table);

    // cout << endl;
    // cout << endl;
    // cout << endl;
    // cout << "Begin print stuff" << endl;

    // buyTree.preorderPrint(buyTree.root);
    // sellTree.preorderPrint(sellTree.root);

    // table.print();

    return 0;
}
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//

//
//
//
//
//
//
// File reading

//     if (false) {
//         if (argc < 2) {
//             std::cout << "Please supply the name of the input file\n";
//         } else {
//             // Read input
//             ifstream inFile(argv[1]);
//             int n;
//             inFile >> n;
//             string orderType;
//             float price;
//             u_int32_t ID;

//             for (int i = 0; i < n; i++) {
//                 inFile >> orderType >> price >> ID;

//                 // Generate orders
//                 newOrder(orderType, price, ID, buyTree, sellTree);
//             }
//         }

//         // Print trees to order results
//         buyTree.preorderPrint(buyTree.root);
//         cout << endl;
//         sellTree.preorderPrint(sellTree.root);
//     } else {
//         cout << "Begin processing" << endl;
//         cout << "..." << endl;
//         cout << "..." << endl;
//         int upperbound = 2000000;
//         for (int i = 0; i <= upperbound; i++) {
//             newOrder("buy", i, 111, buyTree, sellTree);
//         }
//         cout << "Finished processing ..." << upperbound << " orders" << endl;
//     }
// }

// ------------------------------------------------------------------------------------ //

// TODO add delete functionality from order
// TODO add compare function
// Add functionality for buy and sell
// If buy or sell is greater than min or max sell buy then dont need to do anything , just execute