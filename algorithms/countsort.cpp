#include "importsGlobal.hpp"
using namespace std;

// Count sort implementation
void sort(vector<int>& inputArray) {
    vector<int> outputArray(inputArray.size());
    vector<int> countArray(10, 0);
    for (int j = 0; j < inputArray.size(); j++) {
        countArray[inputArray[j]] = countArray[inputArray[j]] + 1;
    }

    for (int i = 1; i < countArray.size(); i++) {
        countArray[i] = countArray[i] + countArray[i - 1];
    }

    for (int j = inputArray.size() - 1; j >= 0; j--) {
        outputArray[countArray[inputArray[j]] - 1] = inputArray[j];
        countArray[inputArray[j]] = countArray[inputArray[j]] - 1;
    }

    for (int j = 0; j < inputArray.size(); j++) {
        inputArray[j] = outputArray[j];
    }
}

int main() {
    vector<int> inputArray{1, 3, 5, 2, 9, 4, 5};
    countSort1(inputArray);

    cout << endl;
    cout << endl;
    cout << endl;
    for (int i : inputArray) {
        cout << i << ", ";
    }

    return 0;
}
