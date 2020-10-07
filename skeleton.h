// Text file input example:
// buy 13 0
// sell 20 0
// delete 0 1111
// ordertype price id

#include <iostream>
#include <string>

#include "/rbtree.cpp"

using namespace std;

int main(int argc, char *argv[]) {
    RBtree sellTree = RBtree("sell");
    RBtree buyTree = RBtree("buy");
    vector<float> orderlog;

    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } else {
        // Read input
        ifstream inFile(argv[1]);
        int n;
        string orderType;
        int idPrice;  // id or price
        inFile >> n;

        for (int i = 0; i < n; i++) {
            inFile >> orderType >> idPrice;
            if (orderType == "buy" || orderType == "sell") {
            }