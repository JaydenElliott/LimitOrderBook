
#include "rbtree.h"

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
        }

        if (currnode != root) {
            insert_fixup(currnode);
        }
    }

    void insert_fixup(Node *currnode) {
        // cout << "Start fix";

        Node *pNode;
        Node *gpNode;
        while (currnode != root && currnode->parent->colour == RED) {
            pNode = currnode->parent;
            gpNode = currnode->parent->parent;
            // Category 1
            if (pNode == gpNode->left) {
                cout << "category 1 start" << endl;
                Node *y = new Node();
                y = gpNode->right;  // BUG seg fault
                cout << y->price;
                // C1 Case 1
                cout << "check 1st" << endl;

                if (y->colour == RED and y != NULL) {
                    cout << "category 1 case 1 start" << endl;
                    pNode->colour = BLACK;
                    y->colour = BLACK;
                    gpNode->colour = RED;
                    currnode = gpNode;
                }
                // C1 Case 2

                else if (currnode == pNode->right) {
                    cout << "category 1 case 2 start" << endl;
                    currnode = pNode;       //
                    rotate_left(currnode);  // TODO maybe swap these
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_right(gpNode);
                    // TODO: see line 275 on their

                }
                // Category 3
                else {
                    cout << "category 1 case 3 start" << endl;
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_right(gpNode);
                }

            }
            // Category 2
            else {
                Node *y = new Node();
                cout << "category 2 start" << endl;
                y = gpNode->left;
                // C2 Case 1
                if (y->price != 0 && y->colour == RED) {
                    cout << "category 2 case 2 start" << endl;
                    pNode->colour = BLACK;
                    y->colour = BLACK;
                    gpNode->colour = RED;
                    currnode = gpNode;
                    if (pNode == nullptr) {
                        break;
                    }
                    cout << "category 2 case 2 finish" << endl;

                }
                // C2 Case 2
                else if (currnode == pNode->left) {
                    cout << "category 2 case 2 start" << endl;
                    currnode = pNode;
                    rotate_right(currnode);
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_left(gpNode);
                    // C3 Case 3
                } else {
                    cout << "category 2 case 3 start" << endl;
                    pNode->colour = BLACK;
                    gpNode->colour = RED;
                    rotate_left(gpNode);
                }
            }
        }

        root->colour = BLACK;
    }

    void insert_fixup2(Node *currnode) {
        // cout << "Start fix";
        Node *y = new Node();
        Node *pNode = new Node();
        Node *gpNode = new Node();
        while (currnode->parent->colour == RED) {
            cout << "while loop iteration ++ " << endl;
            // Category 1

            if (currnode->parent == currnode->parent->parent->left) {
                cout << "category 1 start" << endl;
                y = currnode->parent->parent->right;  // BUG seg fault
                cout << y->price;
                // C1 Case 1
                cout << "check 1st" << endl;

                if (y->colour == RED) {
                    cout << "category 1 case 1 start" << endl;
                    currnode->parent->colour = BLACK;
                    y->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    currnode = currnode->parent->parent;
                }
                // C1 Case 2

                else if (currnode == currnode->parent->right) {
                    cout << "category 1 case 2 start" << endl;
                    currnode = currnode->parent;
                    rotate_left(currnode);
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_right(currnode->parent->parent);

                }
                // Category 3
                else {
                    cout << "category 1 case 3 start" << endl;
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_right(currnode->parent->parent);
                }

            }
            // Category 2
            else {
                cout << "category 2 start" << endl;
                y = currnode->parent->parent->left;
                // C2 Case 1
                if (y->colour == RED) {
                    cout << "category 2 case 2 start" << endl;
                    currnode->parent->colour = BLACK;
                    y->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    currnode = currnode->parent->parent;
                    if (currnode->parent == nullptr) {
                        break;
                    }
                    cout << "category 2 case 2 finish" << endl;

                }
                // C2 Case 2
                else if (currnode == currnode->parent->left) {
                    cout << "category 2 case 2 start" << endl;
                    currnode = currnode->parent;
                    rotate_right(currnode);
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_left(currnode->parent->parent);
                    // C3 Case 3
                } else {
                    cout << "category 2 case 3 start" << endl;
                    currnode->parent->colour = BLACK;
                    currnode->parent->parent->colour = RED;
                    rotate_left(currnode->parent->parent);
                }
            }
        }
    }

    // TODO: update hash table and deletion cases
    Node *delete_price(float price, int ID, Node *currnode, Node *parent = nullptr, bool execute = false) {
        return currnode;
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

    void invariance_check() {}

    void update_tree(float price, int ID, string func = "add", bool execute = false) {
        if (func == "add") {
            Node *currnode = new Node(price, ID);
            insert_price(currnode);
            if (currnode != root) {
                // cout << "currnode = " << currnode->price << " & parent =" << currnode->parent->price << endl;
            }

        }

        else if (func == "del") {
            delete_price(price, ID, root, nullptr, execute);
        }
    }

    // good one
    void printPreorder(Node *node) {
        if (node == nullptr)
            return;

        /* first print data of node */
        cout << node->price << " ";

        /* then recur on left sutree */
        printPreorder(node->left);

        /* now recur on right subtree */
        printPreorder(node->right);
    }
};

// TODO: Testing file (e.g. test that the prices are in the queue)

int main() {
    RBtree testtree = RBtree();
    // if (testtree.NIL->right == nullptr) {
    //     cout << "hi" << endl;
    // }

    // testtree.update_tree(7, 103, "add");
    // testtree.update_tree(3, 104, "add");

    // cout << testtree.root->left->left->price << endl;
    // cout << NULL;

    testtree.update_tree(7, 103, "add");
    testtree.update_tree(3, 104, "add");
    testtree.update_tree(18, 101, "add");
    testtree.update_tree(10, 105, "add");
    testtree.update_tree(8, 105, "add");
    testtree.update_tree(11, 105, "add");
    testtree.update_tree(22, 105, "add");
    testtree.update_tree(26, 105, "add");
    testtree.update_tree(15, 105, "add");

    testtree.printPreorder(testtree.root);

    // cout << endl;//
    // testtree.rotate_right(testtree.root->right);
    // cout << testtree.root->left->left->price; // BUG the seg fault is coming from the leaf nodes not being defined

    // testtree.printPreorder(testtree.root);

    return 0;
}

// TODO: Deletion
// TODO: Maintenance
// TODO: Invariance check