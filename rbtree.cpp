
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

    /// Very rare // FIXME:
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

    size_t size(){
        return ID_Queue.size();
    }

   private:
    vector<int> ID_Queue;
};

class Node {
   public:
    Node(){}
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

    Node *insert_price(float price, int ID, Node *currnode, Node *parent = nullptr) {
        if (currnode == nullptr) {
            Node *order = new Node(price, ID);

            if (root == nullptr) {
                root = order;
            }

            if (max == nullptr || price > max->price) {
                max = order;  // update max
            }

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
    // TODO: update hash table
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
                    cout << "before" << endl;
                    currnode->queue.print();
                    currnode->queue.find_and_remove(ID);
                    cout << "after" << endl;
                    currnode->queue.print();
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

    void update_tree(float price, int ID, string func = "add", bool execute=false) {
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

    void printPreorder(Node *node) {
        if (node == nullptr)
            return;

        /* first print data of node */
        cout << node->price << " ";
        cout << node << " ";

        /* then recur on left sutree */
        printPreorder(node->left);

        /* now recur on right subtree */
        printPreorder(node->right);
    }
};



int main() {
    RBtree testtree = RBtree();

    testtree.update_tree(5, 103, "add");
    testtree.update_tree(7, 104, "add");
    testtree.update_tree(2, 101, "add");
    testtree.update_tree(6, 101, "add");
    testtree.update_tree(8, 101, "add");
    testtree.update_tree(5, 111, "add");
    testtree.update_tree(5, 144, "add");
    testtree.update_tree(5, 122, "add");



    // check non-execute;
    testtree.printPreorder(testtree.root);
    cout << endl;
    // testtree.rotate_left(testtree.root);
    // testtree.rotate_right(testtree.root);
    // testtree.update_tree(2,101,"del",false);
    testtree.delete_price(2,101,testtree.root, nullptr,false);
    
    // delete testtree.root->right;
    // testtree.root->right = nullptr;
    cout << endl;
    testtree.printPreorder(testtree.root);
    cout << endl;




    
    return 0;
}

// TODO: Deletion
// TODO: Maintenance
// TODO: Invariance check