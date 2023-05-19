#include <iostream>

using namespace std;

void merge(int aScore[], int aID[], int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    int resultID[right - left];
    int resultScore[right - left];
    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (aScore[left + it1] < aScore[mid + it2]) {
            resultID[it1 + it2] = aID[left + it1];
            resultScore[it1 + it2] = aScore[left + it1];
            ++it1;
        } else if (aScore[left + it1] == aScore[mid + it2]) {
            if (aID[left + it1] > aID[mid + it2]) {
                resultID[it1 + it2] = aID[left + it1];
                resultScore[it1 + it2] = aScore[left + it1];
                ++it1;
            } else {
                resultID[it1 + it2] = aID[mid + it2];
                resultScore[it1 + it2] = aScore[mid + it2];
                ++it2;
            }
        } else {
            resultID[it1 + it2] = aID[mid + it2];
            resultScore[it1 + it2] = aScore[mid + it2];
            ++it2;
        }
    }
    while (left + it1 < mid) {
        resultID[it1 + it2] = aID[left + it1];
        resultScore[it1 + it2] = aScore[left + it1];
        ++it1;
    }
    while (mid + it2 < right) {
        resultID[it1 + it2] = aID[mid + it2];
        resultScore[it1 + it2] = aScore[mid + it2];
        ++it2;
    }
    for (int i = 0; i < (it1 + it2); ++i) {
        aScore[left + i] = resultScore[i];
        aID[left + i] = resultID[i];
    }
}

void mergeSortRecursive(int aScore[], int aID[], int left, int right) {
    if (left + 1 >= right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSortRecursive(aScore, aID, left, mid);
    mergeSortRecursive(aScore, aID, mid, right);
    merge(aScore, aID, left, mid, right);
}

int main() {
    int n;
    cin >> n;
    int arrayID[n];
    int arrayScore[n];
    for (int i = 0; i < n; ++i) {
        cin >> arrayID[i];
        cin >> arrayScore[i];
    }
    mergeSortRecursive(arrayScore, arrayID, 0, n);
    for (int i = n - 1; i >= 0; --i) {
        cout << arrayID[i] << " " << arrayScore[i] << endl;
    }
    return 0;
}
