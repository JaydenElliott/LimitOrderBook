#include <chrono>

#include "datastructures/hashtable.hpp"
#include "datastructures/node.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/rbtree.hpp"

using namespace std;
using namespace std::chrono;

random_device rd;
mt19937 gen(rd());

/*
* ---------------- Description ----------------
* Handles order logging. Will push order price,
* and execution time to a file.
* Also responsible for handling the executed price
* vector
*
* ---------------- Parameters ----------------
* price:    order price
* orderlog: reference to the executed price vector
* 
*/
void push_to_log(float price, vector<float> &log) {
    log.push_back(price);
}

/*
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
void executeorder(Node *buyorder, Node *sellorder, RBtree &buytree, RBtree &selltree, HashTable &htable, vector<float> &orderlog) {
    if (buyorder == nullptr) {  // sell order
        // push_to_log(buyorder->price, orderlog);  // was causing errors
        htable.del(sellorder->ID, selltree);
    } else if (sellorder == nullptr) {
        // push_to_log(buyorder->price, orderlog);  // was causing errors
        htable.del(buyorder->ID, buytree);
    } else {
        htable.del(sellorder->ID, selltree);
        htable.del(buyorder->ID, buytree);
    }
}

/*
*  ---------------- Description ----------------
* Processes the new orders and sends them to
 the right functions / datastructures
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
void newOrder(string ordertype, float price, size_t ID, RBtree &buytree, RBtree &selltree, HashTable &htable, vector<float> &orderlog) {
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            //Buy price >= max sell price ----- Order can be executed immediately
            executeorder(nullptr, selltree.sellMin, buytree, selltree, htable, orderlog);
        } else {
            Node *buynode = new Node(price, ID);
            htable.insert(price, ID, buynode, buytree);
        }
    } else if (ordertype == "sell") {
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            //Sell price <= max sell price ----- Order can be executed immediately
            executeorder(buytree.buyMax, nullptr, buytree, selltree, htable, orderlog);
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
    vector<float> orderlog;

    auto start = high_resolution_clock::now();

    int buyorders = 10000000;
    for (int i = 1; i <= buyorders; i++) {
        newOrder("buy", i, i + 10, buyTree, sellTree, table, orderlog);
    }

    int sellorders = 10000000;
    for (int i = 1; i <= sellorders; i++) {
        newOrder("sell", i, 1000 + i, buyTree, sellTree, table, orderlog);
    }

    auto end = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(end - start);

    cout << "Time taken for " << buyorders + sellorders << " orders = " << duration.count() << " seconds" << endl;

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