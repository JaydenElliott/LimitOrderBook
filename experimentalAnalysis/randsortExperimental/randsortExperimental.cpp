

#include <algorithm>  // std::random_shuffle
#include <cstdlib>    // std::rand, std::srand

#include "../../algorithms/randquicksort.cpp"

using namespace std;
using namespace std::chrono;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cout << "Please supply the name of the input file\n";
    } else {
        ifstream inFile(argv[1]);
        if (inFile.is_open()) {
            // Read input
            ifstream inFile(argv[1]);
            int n;
            inFile >> n;
            vector<float> orders(n);
            float price;
            for (int i = 0; i < n; i++) {
                inFile >> price;
                orders.at(i) = price;
            }
            // -------- TIMING START --------- //
            vector<double> sortTimes;
            int repeats = 15;
            // random_device rd3;  // for the shuffle
            for (int i = 1; i <= repeats; i++) {
                auto start = high_resolution_clock::now();
                randQuickSort(&orders, 0, orders.size() - 1);
                auto end = high_resolution_clock::now();
                duration<double> duration = duration_cast<milliseconds>(end - start);
                sortTimes.push_back(duration.count());
                // Shuffle the vector
                // shuffle(orders.begin(), orders.end(), rd3);
            }

            double sum = 0;
            for (double i : sortTimes) {
                sum += i;
            }

            ofstream myfile;
            myfile.open("randsortExperimental/randSortResults.txt", fstream::app);
            // myfile << n << endl;
            myfile << sum / (double)repeats << ", ";
            cout << endl;
            myfile.close();
            return 0;
        }
    }
}