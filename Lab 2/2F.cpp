#include <iostream>

using namespace std;

void merge(int a[], int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    int result[right - left];
    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (a[left + it1] <= a[mid + it2]) {
            result[it1 + it2] = a[left + it1];
            ++it1;
        } else {
            result[it1 + it2] = a[mid + it2];
            ++it2;
        }
    }
    while (left + it1 < mid) {
        result[it1 + it2] = a[left + it1];
        ++it1;
    }
    while (mid + it2 < right) {
        result[it1 + it2] = a[mid + it2];
        ++it2;
    }
    for (int i = 0; i < (it1 + it2); ++i) {
        a[left + i] = result[i];
    }
}

void mergeSortRecursive(int a[], int left, int right) {
    if (left + 1 >= right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSortRecursive(a, left, mid);
    mergeSortRecursive(a, mid, right);
    merge(a, left, mid, right);
}

int main() {
    int n;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    mergeSortRecursive(array, 0, n);
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    return 0;
}
