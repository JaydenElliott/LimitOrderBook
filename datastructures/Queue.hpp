#include "../imports/importsGlobal.hpp"
#pragma once

using namespace std;

/**
 * Queue class for the red-black tree nodes
 */
class Queue {
   public:
    Queue() {}
    ~Queue() {}

    string pop() {
        if (ID_Queue.size() == 0) {
            throw out_of_range("No more IDs, delete Node!");
        }
        string last{ID_Queue.back()};
        ID_Queue.pop_back();
        return last;
    }

    void push(string ID) {
        ID_Queue.insert(ID_Queue.begin(), ID);
        // cout << "appending " << ID << endl;
    }

    void find_and_remove(string ID) {
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
        for (string i : ID_Queue) {
            cout << i << ", ";
        }
        cout << endl;
    }

    size_t size() {
        return ID_Queue.size();
    }

   private:
    vector<string> ID_Queue;
};