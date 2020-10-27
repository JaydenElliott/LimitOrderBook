#include "datastructures/hashtable.hpp"
#include "datastructures/node.hpp"
#include "datastructures/queue.hpp"
#include "datastructures/rbtree.hpp"

using namespace std;

random_device rd;
mt19937 gen(rd());

vector<float> orderlog;  // check the below function actually modifies the state
void order_execution_log(float price) {
    orderlog.push_back(price);
}

/*
* Random number generator
* random_device rd; and mt19937 gen(rd()) are global to prevent multiple calls
*/
float getRandInRange(float min_value, float max_value_inc) {
    uniform_real_distribution<float> distr(min_value, max_value_inc);
    return distr(gen);
}

/*
* Utility function for newOrder()
* Handles deletion in red-black trees, order log and hash table
*/
void executeorder(Node *buyorder, Node *sellorder, RBtree &buytree, RBtree &selltree, HashTable &htable) {
    if (buyorder == nullptr) {
        order_execution_log(sellorder->price);
        selltree.delete_price(sellorder);
        htable.del(sellorder->ID);
    } else if (sellorder == nullptr) {
        order_execution_log(buyorder->price);
        buytree.delete_price(buyorder);
        htable.del(buyorder->ID);
    } else {
        order_execution_log(buyorder->price);
        buytree.delete_price(buyorder);
        selltree.delete_price(sellorder);
        htable.del(sellorder->ID);
        htable.del(buyorder->ID);
    }
}

/*
* Handles order processing
* @param ordertype: buy, sell
* @param price: order price
* @param ID: order ID
*/
void newOrder(string ordertype, float price = 0, size_t ID, RBtree &buytree, RBtree &selltree, HashTable &htable) {
    // cout << "begin order for type " << ordertype << " and price " << price << endl;
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            //Buy price >= max sell price ----- Order can be executed immediately
            executeorder(nullptr, selltree.sellMin, buytree, selltree, htable);
        } else {
            Node *buynode = new Node(price, ID);
            buytree.insert_price(buynode);
            htable.insert(price, ID);
        }
    } else if (ordertype == "sell") {
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            //Sell price <= max sell price ----- Order can be executed immediately
            executeorder(buytree.buyMax, nullptr, buytree, selltree, htable);
        } else {
            Node *sellnode = new Node(price, ID);
            selltree.insert_price(sellnode);
            htable.insert(price, ID);
        }
    } else if (ordertype == "delete") {
        htable.del(ID);  // TODO: This needs to link to rbtree delete also
    } else {
        throw runtime_error("Invalid input. Valid input: buy, sell, delete");
    }
}

int main(int argc, char *argv[]) {
    // Insantiate trees and orderlog
    RBtree sellTree = RBtree("sell");
    RBtree buyTree = RBtree("buy");
    HashTable table = HashTable(4);
    vector<float> orderlog;

    for (int i = 0; i <= 100; i++) {
        newOrder("buy", i, i + 10, buyTree, sellTree, table);
    }

    table.print();

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