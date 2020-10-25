#include "importsGlobal.hpp"
using namespace std;

void countSort(vector<int>& inputArray, vector<int>& outputArray) {
    vector<int> countArray(10, 0);
    for (int j = 0; j < inputArray.size() - 1; j++) {
        countArray[inputArray[j]] = countArray[inputArray[j]] + 1;
    }

    for (int i = 1; i < countArray.size(); i++) {
        countArray[i] = countArray[i] + countArray[i - 1];
    }

    for (int j = inputArray.size() - 1; j >= 0; j--) {
        outputArray[countArray[inputArray[j]] - 1] = inputArray[j];
        countArray[inputArray[j]] = countArray[inputArray[j]] - 1;
    }

}

// for (int i = 0; i < arr.size(); i++)
//     count[arr[i] - min]++;

// for (int i = 1; i < count.size(); i++)
//     count[i] += count[i - 1];

// for (int i = arr.size() - 1; i >= 0; i--) {
//     output[count[arr[i] - min] - 1] = arr[i];
//     count[arr[i] - min]--;
// }

// for (int i = 0; i < arr.size(); i++)
//     arr[i] = output[i];
// }

int main() {
    vector<int> inputArray{1, 3, 5, 2, 9, 4, 5};
    vector<int> outputArray(inputArray.size());
    countSort(inputArray, outputArray);

    cout << endl;
    cout << endl;
    cout << endl;
    for (int i : outputArray) {
        cout << i << ", ";
    }
    return 0;
}
