
#include <string>

#include "rbtree.h"
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
    Node() {}
    Node(float price, int ID) {
        this->colour = BLACK;
        this->price = price;
        this->ID = ID;
        queue = Queue();
        queue.push(ID);
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
    Node *NIL = nullptr;
    Node *root = NIL;

    RBtree() {}
    ~RBtree() {}

    // FIXME: Need to update colours etc.. dont forget to account for NIL nodes = black
    Node *insert_price(Node *currnode) {
        Node *y = NIL;
        Node *x = this->root;

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

        // currnode->parent = y;
        if (y == NIL) {
            currnode->parent = y;
            root = currnode;
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

        return currnode;

    }

    void insert_fixup(Node *currnode) {
        // // cout << "Start fix";
        // while (currnode->parent->colour == RED ) {
        //     cout << "while loop iteration ++ " << endl;
        //     // Category 1
            
        //     if (currnode->parent == currnode->parent->parent->left) {
        //         cout << "category 1 start" << endl;
        //         Node *y = currnode->parent->parent->right;
        //         // C1 Case 1
        //         cout << "check 1st"  << endl;
                
        //         if (y->colour == RED) {
        //             cout << "category 1 case 1 start" << endl;
        //             currnode->parent->colour = BLACK;
        //             y->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             currnode = currnode->parent->parent;
        //         }
        //         // C1 Case 2
                
        //         else if (currnode == currnode->parent->right) {
        //             cout << "category 1 case 2 start" << endl;
        //             currnode = currnode->parent;
        //             rotate_left(currnode);
        //             currnode->parent->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             rotate_right(currnode->parent->parent);

        //         }
        //         // Category 3
        //         else {
        //             cout << "category 1 case 3 start" << endl;
        //             currnode->parent->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             rotate_right(currnode->parent->parent);
        //         }

        //     }
        //     // Category 2
        //     else {
        //         cout << "category 2 start" << endl;
        //         Node *y = currnode->parent->parent->left;
        //         // C2 Case 1
        //         if (y->colour == RED) {
        //             cout << "category 2 case 2 start" << endl;
        //             currnode->parent->colour = BLACK;
        //             y->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             currnode = currnode->parent->parent;
        //             if (currnode->parent == nullptr){
        //                 break;
        //             }
        //             cout << "category 2 case 2 finish" << endl;

        //         }
        //         // C2 Case 2
        //         else if (currnode == currnode->parent->left) {
        //             cout << "category 2 case 2 start" << endl;
        //             currnode = currnode->parent;
        //             rotate_right(currnode);
        //             currnode->parent->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             rotate_left(currnode->parent->parent);
        //         // C3 Case 3
        //         } else {
        //             cout << "category 2 case 3 start" << endl;
        //             currnode->parent->colour = BLACK;
        //             currnode->parent->parent->colour = RED;
        //             rotate_left(currnode->parent->parent);
        //         }
        //     }
        // }
    }


// TODO: update hash table and deletion cases
Node *delete_price(float price, int ID, Node *currnode, Node *parent = nullptr, bool execute = false) {
    if (currnode->price < price) {
        currnode->right = delete_price(price, ID, currnode->right, parent, execute);
    } else if (currnode->price > price) {
        currnode->left = delete_price(price, ID, currnode->left, parent, execute);
    } else {
        // note that a mid queue deletion is going to be EXTREMELY RARE - not many people are going to delete trade (bad assumption but oh well lol :P )
        if (currnode->queue.size() == 1) {
            delete currnode;
            currnode = nullptr;
            return nullptr;
        } else {
            if (execute) {
                currnode->queue.pop();
                return currnode;
            } else {
                currnode->queue.find_and_remove(ID);
                return currnode;
            }
        }
    }
    return currnode;
}


void rotate_left(Node *currnode) {
    Node *y = currnode->right;
    currnode->right = y->left;
    if (y->left != NIL){
        y->left->parent = currnode;
    }
    y->parent = currnode->parent;
    if (currnode->parent == NIL){
        this->root = y;
    }
    else if (currnode == currnode->parent->left){
        currnode->parent->left = y;
    }
    else{
        currnode->parent->right = y;
    }
    y->left = currnode;
    currnode->parent = y;

}


    



void rotate_right(Node *currnode) {
    Node *y = currnode->left;
    currnode->left = y->right;
    if (y->right != NIL){
        y->right->parent = currnode;
    }
    y->parent = currnode->parent;
    if (currnode->parent == NIL){
        this->root = y;
    }
    else if (currnode == currnode->parent->right){
        currnode->parent->right = y;
    }
    else{
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
        insert_fixup(currnode);
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

    testtree.update_tree(20, 103, "add"); // g
    testtree.update_tree(18, 104, "add"); // u
    testtree.update_tree(24, 101, "add"); // p
    testtree.update_tree(22, 105, "add"); // x
    // testtree.update_tree(16, 101, "add"); // y
    // testtree.update_tree(17, 101, "add"); // gamma
    // testtree.update_tree(15, 101, "add"); // beta


    testtree.printPreorder(testtree.root);

    cout << endl;
    testtree.rotate_right(testtree.root->right);
    
    testtree.printPreorder(testtree.root);

    return 0;
}

// TODO: Deletion
// TODO: Maintenance
// TODO: Invariance check