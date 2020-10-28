#include "../imports/importsGlobal.hpp"
#pragma once

using namespace std;

class RBtree {
   public:
    Node *buyMax = nullptr;
    Node *sellMin = nullptr;
    Node *NIL = new Node();
    Node *root = NIL;
    RBtree(string treetype) {
        this->treetype = treetype;
    }
    ~RBtree() {
        // TODO create deconstructor
    }
    string treetype;

    void insert_price(Node *currnode);
    void insert_fixup(Node *currnode);
    Node *search_tree(float tofind, size_t ID);
    void delete_price(Node *todelete);
    void delete_fixup(Node *n);
    void rbTransplant(Node *n, Node *v);
    void rotate_left(Node *currnode);
    void rotate_right(Node *currnode);
    Node *findMin(Node *n);
    void preorderPrint(Node *node, bool withColour = false);
    Node *findmax();
    Node *findmin();
};

void RBtree::insert_price(Node *currnode) {
    Node *y = new Node();
    Node *x = new Node();
    y = this->NIL;
    x = this->root;

    while (x != this->NIL) {
        y = x;
        if (currnode->price < x->price) {
            x = x->left;
        } else if (currnode->price > x->price) {
            x = x->right;
        } else {
            break;  // same price
        }
    }

    if (y == this->NIL) {
        currnode->parent = y;
        root = currnode;
        currnode->left = this->NIL;
        currnode->right = this->NIL;
        if (this->treetype == "buy") {
            this->buyMax = currnode;
        } else {
            this->sellMin = currnode;
        }

    } else if (currnode->price < y->price) {
        currnode->parent = y;
        y->left = currnode;
        currnode->left = this->NIL;
        currnode->right = this->NIL;
        currnode->colour = RED;
        if (this->treetype == "sell" && currnode->price < this->sellMin->price) {
            this->sellMin = currnode;
        }
    } else if (currnode->price > y->price) {
        currnode->parent = y;
        y->right = currnode;
        currnode->left = this->NIL;
        currnode->right = this->NIL;
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

void RBtree::insert_fixup(Node *currnode) {
    while (currnode != root && currnode->parent->colour == RED) {
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

// Search tree and find ID associated with price `tofind'
Node *RBtree::search_tree(float tofind, size_t ID) {
    Node *n = new Node();
    n = root;
    while (n == this->NIL || n->price != tofind) {
        if (n == this->NIL) {
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

void RBtree::delete_price(Node *todelete) {
    Node *y = this->NIL;
    Node *x = this->NIL;
    bool ycolour;
    y = todelete;
    ycolour = y->colour;
    if (todelete->left == this->NIL) {
        x = todelete->right;
        rbTransplant(todelete, todelete->right);
    } else if (todelete->right == this->NIL) {
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

    // Update max in buy-tree or min in sell-tree
    if (this->treetype == "buy" && (this->root->right != nullptr || this->root->left != nullptr)) {
        cout << "Updating max" << endl;
        this->buyMax = findmax();
        cout << "finis chercher la maximum" << endl;
    } else if (this->treetype == "sell" && (this->root->right != nullptr || this->root->left != nullptr)) {
        this->sellMin = findmin();
    }

    delete todelete;
    todelete = nullptr;
}

// Delete helper function
void RBtree::delete_fixup(Node *n) {
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

// Delete node helper function
void RBtree::rbTransplant(Node *n, Node *v) {
    if (n->parent == this->NIL) {
        this->root = v;
    } else if (n == n->parent->left) {
        n->parent->left = v;
    } else {
        n->parent->right = v;
    }
    v->parent = n->parent;
}

// Insert/Delete helper function
void RBtree::rotate_left(Node *currnode) {
    Node *y = currnode->right;
    currnode->right = y->left;
    if (y->left != this->NIL) {
        y->left->parent = currnode;
    }
    y->parent = currnode->parent;
    if (currnode->parent == this->NIL) {
        this->root = y;
    } else if (currnode == currnode->parent->left) {
        currnode->parent->left = y;
    } else {
        currnode->parent->right = y;
    }
    y->left = currnode;
    currnode->parent = y;
}

// Insert/Delete helper function
void RBtree::rotate_right(Node *currnode) {
    Node *y = currnode->left;
    currnode->left = y->right;
    if (y->right != this->NIL) {
        y->right->parent = currnode;
    }
    y->parent = currnode->parent;
    if (currnode->parent == this->NIL) {
        this->root = y;
    } else if (currnode == currnode->parent->right) {
        currnode->parent->right = y;
    } else {
        currnode->parent->left = y;
    }
    y->right = currnode;
    currnode->parent = y;
}

Node *RBtree::findMin(Node *n) {
    while (n->left != this->NIL) {
        n = n->left;
    }
    return n;
}

/*
* Helper function for printing tree
* @param node: node to begin printing from
*/
void RBtree::preorderPrint(Node *node, bool withColour) {
    if (node == nullptr)
        return;
    if (withColour == true) {
        cout << "price = " << node->price << " colour = " << (node->colour == RED ? "RED" : "BLACK") << endl;
    } else {
        cout << "price = " << node->price << " ID = " << node->ID << endl;
    }

    preorderPrint(node->left);
    preorderPrint(node->right);
}

Node *RBtree::findmax() {
    if (this->root == nullptr) {
        throw runtime_error("No elements in the tree");
    }
    Node *node = this->root;
    while (node->right->price != 0 && node->right != nullptr) {
        node = node->right;
    }
    return node;
}

Node *RBtree::findmin() {
    if (this->root == nullptr) {
        throw runtime_error("No elements in the tree");
    }
    Node *node = this->root;
    while (node->left->price != 0 && node->left != nullptr) {
        node = node->left;
    }
    return node;
}
