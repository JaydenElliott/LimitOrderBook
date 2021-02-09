

#include "../datastructures/hashtable.hpp"
#include "../datastructures/rbtree.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } else {
        RBtree buyTree = RBtree("buy");
        RBtree sellTree = RBtree("sell");
        HashTable table = HashTable(24);
        ifstream inFile(argv[1]);
        if (inFile.is_open()) {
            // Read input
            ifstream inFile(argv[1]);
            // Read in algorithm to test and number
            // of elements to read through (file header)
            int n;
            inFile >> n;

            vector<tuple<string, float, string>> insertOrders(n);

            // READ IN  ORDERS AND GENERATE ID's
            string insertOrderType;  // buy, sell, delete-buy, delete-sell
            float price;
            for (int i = 0; i < n; i++) {
                inFile >> insertOrderType >> price;
                string ID = generate_uuid();
                insertOrders.at(i) = tuple<string, float, string>(insertOrderType, price, ID);
            }

            // INSERTION
            for (tuple<string, float, string> order : insertOrders) {
                Node *currnode = new Node(get<1>(order), get<2>(order));
                if (get<0>(order) == "buy") {
                    table.insert(currnode->price, currnode->ID, currnode, buyTree);
                } else if (get<0>(order) == "sell") {
                    table.insert(currnode->price, currnode->ID, currnode, sellTree);
                }
            }
            // table.print();
            // DELETION
            for (tuple<string, float, string> order : insertOrders) {
                if (get<0>(order) == "buy") {
                    table.del(get<2>(order), buyTree);
                } else if (get<0>(order) == "sell") {
                    table.del(get<2>(order), sellTree);
                }
            }
        }
        return 0;
    }
}
