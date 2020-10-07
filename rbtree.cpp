
#include "rbtree.h"

#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>
#include <string>

using namespace std::chrono;
using namespace std;

#define BLACK true
#define RED false

class Queue {
   public:
    Queue() {}
    ~Queue() {}

    int pop() {
        if (ID_Queue.size() == 0) {
            throw out_of_range("No more IDs, delete Node!");
        }
        int last{ID_Queue.back()};
        ID_Queue.pop_back();
        return last;
    }

    void push(int ID) {
        ID_Queue.insert(ID_Queue.begin(), ID);
        // cout << "appending " << ID << endl;
    }

    /// Very rare // FIXME - if cant find then terminate:
    void find_and_remove(int ID) {
        int i = 0;
        while (1) {
            if (ID_Queue.at(i) == ID) {
                ID_Queue.erase(ID_Queue.begin() + i);
                break;
            }
            i++;
        }
    }
    void print() {
        for (int i : ID_Queue) {
            cout << i << ", ";
        }
        cout << endl;
    }
    size_t size() {
        return ID_Queue.size();
    }

   private:
    vector<int> ID_Queue;
};

// TODO: Currently every node gets an ID push, need to fix this
// so that only new nodes get id pushes.
class Node {
   public:
    // Node() {} // TODO I commented this out, not sure if its needed as defaults
    Node(float price = 0, int ID = 0) {
        this->colour = BLACK;
        this->price = price;
        this->ID = ID;
        queue = Queue();
        queue.push(ID);
        bool nullNode = true;
        if (price != 0) {
            nullNode = false;
        }
    }
    ~Node(){};
    bool colour;
    Queue queue;
    int ID;
    double price;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    // Node *sucessor = nullptr;
};

class RBtree {
   public:
    Node *buyMax = nullptr;   // if buy tree //TODO need to update max/min
    Node *sellMin = nullptr;  // if sell tree
    Node *NIL = new Node();
    Node *root = NIL;
    RBtree(string treetype) {
        this->treetype = treetype;
    }
    ~RBtree() {}
    string treetype;

    void insert_price(Node *currnode) {
        Node *y = new Node();
        Node *x = new Node();
        y = NIL;
        x = this->root;  // TODO: could make this a parameter to stop the scaling of the tree

        while (x != NIL) {
            y = x;
            if (currnode->price < x->price) {
                x = x->left;
            } else if (currnode->price > x->price) {
                x = x->right;
            } else {
                break;  // same price
            }
        }

        if (y == NIL) {
            currnode->parent = y;
            root = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
            this->buyMax = currnode;
            this->sellMin = currnode;
            // currnode->colour = RED;  // TODO : changed
        } else if (currnode->price < y->price) {
            currnode->parent = y;
            y->left = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
            currnode->colour = RED;
            if (this->treetype == "sell" && currnode->price < this->sellMin->price) {
                this->sellMin = currnode;
            }
        } else if (currnode->price > y->price) {
            currnode->parent = y;
            y->right = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
            currnode->colour = RED;
            if (currnode->price > this->buyMax->price && this->treetype == "buy") {
                this->buyMax = currnode;
            }
        } else {
            // y->price = currnode->price;
            y->queue.push(currnode->ID);
            delete currnode;
            currnode = nullptr;
            return;
        }

        if (currnode != root) {
            insert_fixup(currnode);
        }
    }

    void insert_fixup(Node *currnode) {
        while (currnode != root && currnode->parent->colour == RED) {
            // TODO figured out that the problem is occuring when node = 16.

            // Category 1
            if (currnode->parent == currnode->parent->parent->left) {
                Node *y = new Node();
                y = currnode->parent->parent->right;
                // C1 Case 1

                if (y->colour == RED) {
                    currnode->parent->colour = BLACK;
                    y->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    currnode = currnode->parent->parent;
                }
                // C1 Case 2

                else {
                    if (currnode == currnode->parent->right) {
                        currnode = currnode->parent;
                        rotate_left(currnode);
                    }
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_right(currnode->parent->parent);
                }

            }
            // Category 2

            else {
                Node *y = new Node();
                y = currnode->parent->parent->left;
                // C2 Case 1

                if (y->colour == RED) {
                    currnode->parent->colour = BLACK;
                    y->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    currnode = currnode->parent->parent;
                }
                // C2 Case 2

                else {
                    if (currnode == currnode->parent->left) {
                        currnode = currnode->parent;
                        rotate_right(currnode);
                    }
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_left(currnode->parent->parent);
                }
            }
        }
        root->colour = BLACK;
    }
    // TODO: multiple id's
    Node *search_tree(float tofind, int ID) {
        Node *n = new Node();
        n = root;
        while (n == NIL || n->price != tofind) {
            if (n == NIL) {
                throw runtime_error("price does not exist in tree");
            }
            if (n->price < tofind) {
                n = n->right;
            } else {
                n = n->left;
            }
        }
        return n;
    }

    void delete_price(Node *todelete) {
        Node *y = NIL;
        Node *x = NIL;
        bool ycolour;
        y = todelete;
        ycolour = y->colour;
        if (todelete->left == NIL) {
            x = todelete->right;
            rbTransplant(todelete, todelete->right);
        } else if (todelete->right == NIL) {
            x = todelete->left;
            rbTransplant(todelete, todelete->left);
        } else {
            y = findMin(todelete->right);

            ycolour = y->colour;
            x = y->right;
            if (y->parent == todelete) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = todelete->right;
                y->right->parent = y;
            }
            rbTransplant(todelete, y);
            y->left = todelete->left;
            y->left->parent = y;
            y->colour = todelete->colour;
        }

        if (ycolour == BLACK) {
            delete_fixup(x);
        }
        delete todelete;
        todelete = nullptr;
    }

    void delete_fixup(Node *n) {
        Node *w = new Node();
        while (n != root && n->colour == BLACK) {
            if (n == n->parent->left) {
                w = n->parent->right;
                if (w->colour == RED) {
                    w->colour = BLACK;
                    n->parent->colour = RED;
                    rotate_left(n->parent);
                    w = n->parent->right;
                }
                if (w->left->colour == BLACK && w->right->colour == BLACK) {
                    w->colour = RED;
                    n = n->parent;
                } else {
                    if (w->right->colour == BLACK) {
                        w->left->colour = BLACK;
                        w->colour = RED;
                        rotate_right(w);
                        w = n->parent->right;
                    }
                    w->colour = n->parent->colour;
                    n->parent->colour = BLACK;
                    w->right->colour = BLACK;
                    rotate_left(n->parent);
                    n = root;
                }
            } else {
                w = n->parent->left;
                if (w->colour == RED) {
                    w->colour = BLACK;
                    n->parent->colour = RED;
                    rotate_right(n->parent);
                    w = n->parent->left;
                }
                if (w->right->colour == BLACK && w->left->colour == BLACK) {
                    w->colour = RED;
                    n = n->parent;
                } else {
                    if (w->left->colour == BLACK) {
                        w->right->colour = BLACK;
                        w->colour = RED;
                        rotate_left(w);
                        w = n->parent->left;
                    }
                    w->colour = n->parent->colour;
                    n->parent->colour = BLACK;
                    w->left->colour = BLACK;
                    rotate_right(n->parent);
                    n = root;
                }
            }
        }
        n->colour = BLACK;
    }

    // Delete helper function
    void rbTransplant(Node *n, Node *v) {
        if (n->parent == NIL) {
            this->root = v;
        } else if (n == n->parent->left) {
            n->parent->left = v;
        } else {
            n->parent->right = v;
        }
        v->parent = n->parent;
    }

    void rotate_left(Node *currnode) {
        Node *y = currnode->right;
        currnode->right = y->left;
        if (y->left != NIL) {
            y->left->parent = currnode;
        }
        y->parent = currnode->parent;
        if (currnode->parent == NIL) {
            this->root = y;
        } else if (currnode == currnode->parent->left) {
            currnode->parent->left = y;
        } else {
            currnode->parent->right = y;
        }
        y->left = currnode;
        currnode->parent = y;
    }

    void rotate_right(Node *currnode) {
        Node *y = currnode->left;
        currnode->left = y->right;
        if (y->right != NIL) {
            y->right->parent = currnode;
        }
        y->parent = currnode->parent;
        if (currnode->parent == NIL) {
            this->root = y;
        } else if (currnode == currnode->parent->right) {
            currnode->parent->right = y;
        } else {
            currnode->parent->left = y;
        }
        y->right = currnode;
        currnode->parent = y;
    }

    void update_tree(float price, int ID, string func = "add", bool execute = false) {
        if (func == "add") {
            Node *currnode = new Node(price, ID);
            insert_price(currnode);
            // cout << "finished inserting price " << price << endl;
        } else if (func == "del") {
            Node *x = new Node();
            x = search_tree(price, ID);
            if (x->queue.size() > 1) {
                x->queue.find_and_remove(ID);
            } else {
                delete_price(x);
            }
        }
    }

    Node *findMin(Node *n) {
        while (n->left != NIL) {
            n = n->left;
        }
        return n;
    }

    /*
    * Helper function for printing tree
    * @param node: node to begin printing from
    */
    void preorderPrint(Node *node, bool withColour = false) {
        if (node == nullptr)
            return;
        if (withColour == true) {
            cout << "price = " << node->price << " colour = " << (node->colour == RED ? "RED" : "BLACK") << endl;
        } else {
            cout << "price = " << node->price << endl;
        }

        preorderPrint(node->left);
        preorderPrint(node->right);
    }
};

void parseInput(RBtree *tree, const string &input_value) {
    if (input_value == "buy") {
        string stock;
        cout << "Enter stock" << endl;
        cin >> stock;
        string price;
        cout << "Enter price" << endl;
        cin >> price;
        cout << stock << " " << price << endl;
    }
}

vector<float> orderlog;  // check the below function actually modifies the state
void order_execution_log(float price) {
    orderlog.push_back(price);
}

random_device rd;
mt19937 gen(rd());
/*
* Random number generator
* Above defined variables are global to prevent multiple calls
*/
float getRandInRange(float min_value, float max_value_inc) {
    uniform_real_distribution<float> distr(min_value, max_value_inc);
    return distr(gen);
}
void executeorder(Node *buyorder, Node *sellorder, RBtree &buytree, RBtree &selltree) {
    if (buyorder == nullptr) {
        order_execution_log(sellorder->price);
        selltree.delete_price(sellorder);
    } else if (sellorder == nullptr) {
        order_execution_log(buyorder->price);
        buytree.delete_price(buyorder);
    } else {
        order_execution_log(buyorder->price);
        buytree.delete_price(buyorder);
        selltree.delete_price(sellorder);
    }
}

//TODO NEED TO FIX THIS SO THAT I CAN CALL IT OUTSIDE OF THE CLASS
/*
    * Utility function to handle orders
    * @param ordertype: buy, sell
    * @param price: order price
    * @param ID: order ID
    */
void newOrder(string ordertype, float price, int ID, RBtree &buytree, RBtree &selltree) {
    // cout << "begin order for type " << ordertype << " and price " << price << endl;
    if (ordertype == "buy") {
        if (selltree.root != selltree.NIL && price >= selltree.sellMin->price) {
            // Order can be executed immediately, no need to insert
            executeorder(nullptr, selltree.sellMin, buytree, selltree);
        } else {
            Node *buynode = new Node(price, ID);
            buytree.insert_price(buynode);
            //TODO update hash (similarly for other functions)
        }
    } else if (ordertype == "sell") {
        // cout << buytree.buyMax->price << endl;
        if (buytree.root != buytree.NIL && price <= buytree.buyMax->price) {
            // Order can be executed immediately, no need to insert
            executeorder(buytree.buyMax, nullptr, buytree, selltree);
        } else {
            Node *sellnode = new Node(price, ID);
            selltree.insert_price(sellnode);
        }
    } else if (ordertype == "delete") {
        ;  // search has function instead
    } else {
        throw runtime_error("Invalid input. Valid input: buy, sell, delete");
    }
}
// ------------------------------------------------------------------------------------ //
// int main() {
//     RBtree sellTree = RBtree("sell");
//     RBtree buyTree = RBtree("buy");

//     vector<float> orderlog;

//     // newOrder("buy", 13, 1115, buyTree, sellTree);
//     // newOrder("buy", 15, 1115, buyTree, sellTree);

//     clock_t c_start = clock();
//     for (int i = 1; i <= 1000000; i++) {
//         newOrder("buy", i, 11, buyTree, sellTree);
//     }
//     clock_t c_end = clock();
//     cout << "Seconds = " << (c_end - c_start) / CLOCKS_PER_SEC << endl;

//     // while (true) {
//     //     std::string details;
//     //     cout << "enter details" << endl;
//     //     cin >> details;
//     //     if (details == "quit") {
//     //         break;
//     //     }
//     //     parseInput(&testtree, details);
//     // }

//     return 0;
// }

// ------------------------------------------------------------------------------------ //

// TODO add delete functionality from order
// TODO add compare function
// Add functionality for buy and sell
// If buy or sell is greater than min or max sell buy then dont need to do anything , just execute
// Change int ID to uint32_t