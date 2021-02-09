/**
 * Conducts timing checks on insert, delete and search
 * 
 * Due to the hashtable and rbtree links, lines 86 and
 * 144 in datastructures/hashtable.hpp need to be commented
 * out. This allows the hashtable operations to be tested
 * independently
 */

#include "../../datastructures/hashtable.hpp"
#include "../../datastructures/rbtree.hpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } else {
        HashTable table = HashTable(24);
        RBtree buyTree = RBtree("buy");
        ifstream inFile(argv[1]);
        if (inFile.is_open()) {
            // Read input
            ifstream inFile(argv[1]);
            // Read in algorithm to test and number
            // of elements to read through (file header)
            int n;
            inFile >> n;

            vector<tuple<string, float, string>> insertOrders(n);

            // READ IN INSERT ORDERS AND GENERATE ID's
            string insertOrderType;  // buy, sell, delete-buy, delete-sell
            float price;
            for (int i = 0; i < n; i++) {
                inFile >> insertOrderType >> price;
                string ID = generate_uuid();
                insertOrders.at(i) = tuple<string, float, string>(insertOrderType, price, ID);
            }

            int repeats = 15;
            vector<double> insertTimes;
            vector<double> deleteTimes;
            vector<double> searchTimes;
            // START INSERT TIMING
            for (int i = 1; i <= repeats; i++) {
                table = HashTable(24);
                // Time Insert

                auto startI = high_resolution_clock::now();
                for (tuple<string, float, string> order : insertOrders) {
                    Node *currnode = new Node(get<1>(order), get<2>(order));  // arbritrary node
                    table.insert(currnode->price, currnode->ID, currnode, buyTree);
                }
                auto endI = high_resolution_clock::now();
                duration<double> durationI = duration_cast<milliseconds>(endI - startI);
                insertTimes.push_back(durationI.count());

                // Time search
                auto startS = high_resolution_clock::now();
                for (tuple<string, float, string> order : insertOrders) {
                    HashNode hnode;
                    table.get(get<2>(order), hnode);
                }
                auto endS = high_resolution_clock::now();
                duration<double> durationS = duration_cast<milliseconds>(endS - startS);
                searchTimes.push_back(durationS.count());

                // Time Delete
                auto startD = high_resolution_clock::now();
                for (tuple<string, float, string> order : insertOrders) {
                    table.del(get<2>(order), buyTree);
                };
                auto endD = high_resolution_clock::now();
                duration<double> durationD = duration_cast<milliseconds>(endD - startD);
                deleteTimes.push_back(durationD.count());
            }

            // GET AVERAGE INSERTS
            double insertSum = 0;
            for (double i : insertTimes) {
                insertSum += i;
                // cout << i << endl;
            }

            double deleteSum = 0;
            for (double i : deleteTimes) {
                deleteSum += i;
                // cout << i << ", ";
            }

            double searchSum = 0;
            for (double i : searchTimes) {
                searchSum += i;
                // cout << i << ", ";
            }

            ofstream myfile;
            myfile.open("hashtableExperimental/hashresults.txt", fstream::app);
            myfile << n << endl;
            myfile << "insert: " << insertSum / repeats << endl;
            myfile << "delete: " << deleteSum / repeats << endl;
            myfile << "search: " << searchSum / repeats << endl;
            cout << endl;
            myfile.close();
            return 0;
        }
    }
}