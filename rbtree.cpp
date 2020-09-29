
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

class Node {
   public:
    Node() {}
    Node(float price, int ID) {
        this->colour = BLACK;
        this->price = price;
        queue = Queue();
        queue.push(ID);
    }
    ~Node(){};
    bool colour;
    Queue queue;
    double price;
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    // Node *sucessor = nullptr;
};

class RBtree {
   public:
    Node *root = nullptr;
    Node *max = nullptr;  // if buy tree
    Node *min = nullptr;  // if sell tree

    RBtree() {}
    ~RBtree() {}

    // FIXME: Need to update colours etc.. dont forget to account for NIL nodes = black
    Node *insert_price(float price, int ID, Node *currnode, Node *parent = nullptr) {
        if (currnode == nullptr) {
            Node *order = new Node(price, ID);
            // Node *rchild = new Node();
            // Node *lchild = new Node();

            if (root == nullptr) {
                root = order;
                order->colour = BLACK;
            }
            else
            {
                order->colour = RED;
                // cout << "checking parent" << endl;
                // cout << order->parent->colour;
                // cout << "checking colour" << endl;
                // if (order->parent->colour == RED){
                //     // insert_fixup(order);
                //     cout << "checked colour" << endl;
                // }
            }
            

            if (max == nullptr || price > max->price) {
                max = order;  // update max
            }

            // Setting up NIL child nodes
            // rchild->colour = BLACK;
            // lchild->colour = BLACK;
            // rchild->parent = order;
            // lchild->parent = order;
            // order->right = rchild;
            // order->left = lchild;

   


            return order;
        }

        if (currnode->price < price) {
            // cout << "new price > old" << endl;
            currnode->right = insert_price(price, ID, currnode->right, parent = currnode);
            currnode->right->parent = currnode;

        } else if (currnode->price > price) {
            // cout << "new price < old" << endl;
            currnode->left = insert_price(price, ID, currnode->left, parent = currnode);
            currnode->left->parent = currnode;

        } else {
            // cout << "new price = old" << endl;
            currnode->queue.push(ID);
        }
        return currnode;
    }



    Node  *insert_fixup(Node *currnode){

        // Category 1:
        cout << "Checking cat 1 condition" << endl;
        if (currnode->parent->parent->left == currnode->parent){
            cout << "Finished checking cat 1 condition" << endl;
            // Case 1: Uncle is red
            cout << "Starting Cat 1, Case 1:" << endl;
            if (currnode->parent->parent->right->colour == RED){
                currnode->parent->colour = BLACK;
                currnode->parent->parent->left->colour = BLACK;
                currnode->parent->parent->colour = RED;
                return insert_fixup(currnode->parent->parent);
                cout << "Finishing Cat 1, Case 1:" << endl;
            }

            // Case 2: Uncle is black and currnode is right child
            else if (currnode->parent->parent->left->colour == BLACK && currnode->parent->right == currnode){
                cout << "Starting Cat 1, Case 2:" << endl;
                rotate_left(currnode->parent);

                // CONTINUE CASE 3
                currnode->parent->colour = BLACK;
                currnode->parent->parent->colour = RED;
                rotate_right(currnode->parent->parent);
                cout << "Finishing Cat 1, Case 1:" << endl;
            }
            // Case 3:
            else if (currnode->parent->parent->left->colour == BLACK && currnode->parent->left == currnode){
                cout << "Starting Cat 1, Case 3:" << endl;
                currnode->parent->colour = BLACK;
                currnode->parent->parent->colour = RED;
                rotate_right(currnode->parent->parent);
                cout << "Finishing Cat 1, Case 1:" << endl;

            }
    

        }


        return currnode;
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

    // TODO: change to look not as similar as programiz
    void rotate_left(Node *currnode) {
        Node *rightchild = currnode->right;

        currnode->right = rightchild->left;

        if (rightchild->left != nullptr) {
            rightchild->left->parent = currnode;
        }

        rightchild->parent = currnode->parent;
        if (currnode->parent == nullptr) {
            this->root = rightchild;

        } else if (currnode == currnode->parent->left) {
            currnode->parent->left = rightchild;

        } else {
            currnode->parent->right = rightchild;
        }
        rightchild->left = currnode;
        currnode->parent = rightchild;
    }

    void rotate_right(Node *currnode) {
        Node *leftchild = currnode->left;

        currnode->left = leftchild->right;

        if (leftchild->right != nullptr) {
            leftchild->right->parent = currnode;
        }

        leftchild->parent = currnode->parent;
        if (currnode->parent == nullptr) {
            root = leftchild;

        } else if (currnode == currnode->parent->right) {
            currnode->parent->right = leftchild;

        } else {
            currnode->parent->left = leftchild;
        }
        leftchild->right = currnode;
        currnode->parent = leftchild;
    }

    void invariance_check() {}

    void update_tree(float price, int ID, string func = "add", bool execute = false) {
        if (func == "add") {
            insert_price(price, ID, root);
        }

        else if (func == "del") {
            delete_price(price, ID, root, nullptr, execute);
        }
    }

    void printInorder(Node *node) {
        if (node == nullptr)
            return;

        /* first recur on left child */
        printInorder(node->left);

        /* then print the data of node */
        cout << node->price << " ";

        /* now recur on right child */
        printInorder(node->right);
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

int main() {
    RBtree testtree = RBtree();

    cout<< "insert 1st elem"<<endl;
    testtree.update_tree(5, 103, "add");
    cout<< "insert 2st elem"<<endl;
    testtree.update_tree(7, 104, "add");
    testtree.update_tree(2, 101, "add");
    testtree.update_tree(6, 101, "add");
    testtree.update_tree(8, 101, "add");
    testtree.update_tree(5, 111, "add");
    testtree.update_tree(5, 144, "add");
    testtree.update_tree(5, 122, "add");

    // check non-execute;
    // testtree.printPreorder(testtree.root);
    cout << endl;
    // testtree.rotate_left(testtree.root);
    // testtree.rotate_right(testtree.root);
    // testtree.update_tree(2,101,"del",false);
    // testtree.delete_price(2, 101, testtree.root, nullptr, false);

    // delete testtree.root->right;
    // testtree.root->right = nullptr;
    // cout << endl;
    // testtree.printPreorder(testtree.root);
    // cout << endl;

    return 0;
}

// TODO: Deletion
// TODO: Maintenance
// TODO: Invariance check