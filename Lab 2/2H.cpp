#include <iostream>
#include <algorithm>

using namespace std;

void merge(int a[], int b[], int left, int mid, int right) {
    int it1 = 0, it2 = 0;
    int resulta[right - left], resultb[right-left];
    while ((left + it1 < mid) && (mid + it2 < right)) {
        if (a[left + it1] < a[mid + it2]) {
            resulta[it1 + it2] = a[left + it1];
            resultb[it1 + it2] = b[left + it1];
            ++it1;
        } else if (a[left + it1] == a[mid + it2]) {
            if (b[left + it1] <= b[mid + it2]) {
                resulta[it1 + it2] = a[mid + it2];
                resultb[it1 + it2] = b[mid + it2];
                ++it2;
            } else {
                resulta[it1 + it2] = a[left + it1];
                resultb[it1 + it2] = b[left + it1];
                ++it1;
            }
        } else {
            resulta[it1 + it2] = a[mid + it2];
            resultb[it1 + it2] = b[mid + it2];
            ++it2;
        }
    }
    while (left + it1 < mid) {
        resulta[it1 + it2] = a[left + it1];
        resultb[it1 + it2] = b[left + it1];
        ++it1;
    }
    while (mid + it2 < right) {
        resulta[it1 + it2] = a[mid + it2];
        resultb[it1 + it2] = b[mid + it2];
        ++it2;
    }
    for (int i = 0; i < (it1 + it2); ++i) {
        a[left + i] = resulta[i];
        b[left + i] = resultb[i];
    }
}

void mergeSortRecursive(int a[], int b[], int left, int right) {
    if (left + 1 >= right) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSortRecursive(a, b, left, mid);
    mergeSortRecursive(a, b, mid, right);
    merge(a, b, left, mid, right);
}

int main() {
    int n, paintedCount = 0, currMax;
    cin >> n;
    int a[n], b[n];
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
    }

    mergeSortRecursive(a, b, 0, n);

    paintedCount += b[0] - a[0] + 1;
    currMax = b[0];

    for (int i = 1; i < n; ++i) {
        if (b[i] > currMax) {
            if (a[i] > currMax) {
                paintedCount += b[i] - a[i] + 1;
            } else if (b[i] > currMax) {
                paintedCount += b[i] - currMax;
            }
        }
        currMax = max(currMax, b[i]);
    }

    cout << paintedCount;
    return 0;
}
