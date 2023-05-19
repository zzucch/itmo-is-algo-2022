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

int duplicatesRemoval(int a[], int n) {
    int result[n];
    int j = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] != a[i + 1]) {
            result[j++] = a[i];
        }
    }
    result[j++] = a[n - 1];
    for (int i = 0; i < j; ++i) {
        a[i] = result[i];
    }
    return j;
}

int main() {
    int n1, n2;
    cin >> n1;
    int array1[n1];
    for (int i = 0; i < n1; ++i) {
        cin >> array1[i];
    }
    cin >> n2;
    int array2[n2];
    for (int i = 0; i < n2; ++i) {
        cin >> array2[i];
    }

    mergeSortRecursive(array1, 0, n1);
    mergeSortRecursive(array2, 0, n2);

    int n12 = duplicatesRemoval(array1, n1);
    int n22 = duplicatesRemoval(array2, n2);

    bool equality = true;

    if (n12 != n22) {
        equality = false;
    } else {
        for (int i = 0; i < n12; ++i) {
            if (array1[i] != array2[i]) {
                equality = false;
            }
        }
    }

    cout << (equality ? "YES" : "NO");
    return 0;
}
