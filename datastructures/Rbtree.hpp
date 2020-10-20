#include "../importsGlobal.hpp"
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
        //TODO delete everything from bottom up
    }
    string treetype;

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
    Node *search_tree(float tofind, size_t ID) {
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

    // Delete helper function
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

    // Delete node helper function
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

    // Insert/Delete helper function
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

    // Insert/Delete helper function
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

    Node *findMin(Node *n) {
        while (n->left != NIL) {
            n = n->left;
        }
        return n;
    }
};

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