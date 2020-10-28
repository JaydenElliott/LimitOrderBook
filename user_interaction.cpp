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
        htable.del(sellorder->ID, selltree);
    } else if (sellorder == nullptr) {
        // order_execution_log(buyorder->price);

        //

        //
        cout << "buytree max ID = " << buytree.buyMax->ID << endl;
        cout << " buyorder id =  " << buyorder->ID << endl;

        // PROBLEM IS ABOVE, BUYORDER != BUYMAX ORDER
        cout << " buyorder price = " << buyorder->price << endl;
        cout << endl;

        htable.del(buyorder->ID, buytree);
    } else {
        htable.del(sellorder->ID, selltree);
        htable.del(buyorder->ID, buytree);
    }
}

/*
* Handles order processing
* @param ordertype: buy, sell
* @param price: order price
* @param ID: order ID
*/
void newOrder(string ordertype, float price, size_t ID, RBtree &buytree, RBtree &selltree, HashTable &htable) {
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            //Buy price >= max sell price ----- Order can be executed immediately
            executeorder(nullptr, selltree.sellMin, buytree, selltree, htable);
        } else {
            Node *buynode = new Node(price, ID);
            htable.insert(price, ID, buynode, buytree);
        }
    } else if (ordertype == "sell") {
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            //Sell price <= max sell price ----- Order can be executed immediately
            cout << " BUYMAX ID = " << buytree.buyMax->ID << endl;
            executeorder(buytree.buyMax, nullptr, buytree, selltree, htable);
            cout << "CHECK CHECK 123" << endl;
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
    HashTable table = HashTable(4);
    vector<float> orderlog;

    for (int i = 1; i <= 100; i++) {
        newOrder("buy", i, i + 10, buyTree, sellTree, table);
    }

    cout << "start sell orders" << endl;
    for (int i = 1; i <= 100; i++) {
        cout << endl;
        cout << "start sell of " << i << endl;
        cout << "---------------------------------------" << endl;
        newOrder("sell", i, 1000 + i, buyTree, sellTree, table);
    }
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