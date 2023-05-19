#include <iostream>

using namespace std;

int partition(int a[], int l, int r) {
    int x = a[(l + r) / 2];
    int i = l, j = r;
    while (true) {
        while (a[i] < x) {
            ++i;
        }
        while (a[j] > x) {
            --j;
        }
        if (i >= j) {
            return j;
        }
        swap(a[i++], a[j--]);
    }
}

void quicksort(int a[], int l, int r) {
    if (l < r) {
        int q = partition(a, l, r);
        quicksort(a, l, q);
        quicksort(a, q + 1, r);
    }
}

int main() {
    int n;
    cin >> n;
    int array[n];
    for (int i = 0; i < n; ++i) {
        cin >> array[i];
    }
    quicksort(array, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        cout << array[i] << " ";
    }
    return 0;
}
