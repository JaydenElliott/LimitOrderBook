
#include "rbtree.h"

#include <iostream>
#include <string>
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
        cout << last << endl;
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
    Node *max = nullptr;  // if buy tree
    Node *min = nullptr;  // if sell tree
    Node *NIL = new Node();
    Node *root = NIL;
    RBtree() {}
    ~RBtree() {}

    void insert_price(Node *currnode) {
        cout << "inserting price " << currnode->price << endl;
        Node *y = new Node();
        Node *x = new Node();
        y = NIL;
        x = this->root;

        while (x != NIL) {
            y = x;
            if (currnode->price < x->price) {
                x = x->left;
            } else if (currnode->price > x->price) {
                x = x->right;
            } else {
                // need to insert price at similar price
                break;
            }
        }

        if (y == NIL) {
            currnode->parent = y;
            root = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
        } else if (currnode->price < y->price) {
            currnode->parent = y;
            y->left = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
            currnode->colour = RED;
        } else if (currnode->price > y->price) {
            currnode->parent = y;
            y->right = currnode;
            currnode->left = NIL;
            currnode->right = NIL;
            currnode->colour = RED;
        } else {
            // y price = currnode price
            y->queue.push(currnode->ID);
            currnode->queue.~Queue();
            cout << "pushing to queue" << endl;
        }

        if (currnode != root) {
            insert_fixup(currnode);
        }
    }

    void insert_fixup(Node *currnode) {
        cout << "Start fix at price" << currnode->price << endl;

        Node *pNode;
        Node *gpNode;

        while (currnode != root && currnode->parent->colour == RED) {
            pNode = currnode->parent;
            gpNode = currnode->parent->parent;

            cout << endl;
            cout << "testing begin" << endl;
            cout << "currnode = " << currnode->price << endl;
            cout << "currnode parent = " << currnode->parent->price << endl;
            cout << "testing end" << endl;
            cout << endl;
            // TODO figured out that the problem is occuring when node = 16.

            // Category 1
            if (pNode == gpNode->left) {
                Node *y = new Node();
                y = gpNode->right;
                // C1 Case 1

                if (y->colour == RED and y != NULL) {
                    pNode->colour = BLACK;
                    y->colour = BLACK;
                    gpNode->colour = RED;
                    currnode = gpNode;
                }
                // C1 Case 2

                else if (currnode == pNode->right) {
                    currnode = pNode;
                    rotate_left(currnode);  // TODO maybe swap these
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_right(gpNode);
                    // TODO: see line 275 on their
                }

                else {
                    // Category 3
                    cout << "cat 3 " << endl;
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_right(gpNode);
                }
            }
            // Category 2

            else {
                Node *y = new Node();
                y = gpNode->left;  // BUG: error is here
                cout << "error begins here" << endl;

                cout << y->price;

                cout << endl;
                cout << "error ends here" << endl;

                // C2 Case 1
                if (y->price != 0 && y->colour == RED) {
                    cout << "cat 2 case 1" << endl;
                    pNode->colour = BLACK;
                    y->colour = BLACK;
                    gpNode->colour = RED;
                    currnode = gpNode;
                    if (pNode == NIL) {
                        break;
                    }
                }
                // C2 Case 2

                else if (currnode == pNode->left) {
                    currnode = pNode;
                    rotate_right(currnode);
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_left(gpNode);
                    // C3 Case 3

                } else {
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_left(gpNode);
                }
            }
        }

        root->colour = BLACK;
        cout << "finished fixing price " << currnode->price << endl;
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

    // TODO: update hash table and deletion cases
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
            cout << "finished inserting" << endl;
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

    // good one
    void printPreorder(Node *node) {
        if (node == nullptr)
            return;

        /* first print data of node */
        cout << "price = " << node->price << " colour = " << (node->colour == RED ? "RED" : "BLACK") << endl;
        // cout << node->price << " ";

        /* then recur on left sutree */
        printPreorder(node->left);

        /* now recur on right subtree */
        printPreorder(node->right);
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

// TODO: Testing file (e.g. test that the prices are in the queue)

int main() {
    RBtree testtree = RBtree();

    // while (true) {
    //     std::string details;
    //     cout << "enter details" << endl;
    //     cin >> details;
    //     if (details == "quit") {
    //         break;
    //     }
    //     parseInput(&testtree, details);
    // }
    testtree.update_tree(7, 103, "add");
    testtree.update_tree(3, 104, "add");
    testtree.update_tree(18, 101, "add");
    testtree.update_tree(16, 102, "add");
    testtree.update_tree(10, 105, "add");
    testtree.update_tree(8, 105, "add");
    testtree.update_tree(11, 105, "add");
    testtree.update_tree(22, 105, "add");
    testtree.update_tree(26, 105, "add");
    testtree.update_tree(15, 105, "add");

    // testtree.printPreorder(testtree.root);

    // testtree.insert_price(7);
    // testtree.insert_price(3);
    // testtree.insert_price(18);
    // testtree.insert_price(16);
    // testtree.insert_price(10);
    // testtree.insert_price(7);

    cout << endl;

    // testtree.update_tree(15, 105, "del");

    testtree.printPreorder(testtree.root);

    // cout << testtree.root->right->left->right->right->parent->parent->left->price << endl;

    return 0;
}

// TODO: Deletion
// TODO: Maintenance
// TODO: Invariance check