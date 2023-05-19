#include <iostream>

void heapify(int a[], int n, int i) {
    int largest = i;

    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && a[l] > a[largest]) {
        largest = l;
    }
    if (r < n && a[r] > a[largest]) {
        largest = r;
    }

    if (largest != i) {
        std::swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void buildHeap(int a[], int n) {
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(a, n, i);
    }
}

void heapSort(int a[], int n) {
    buildHeap(a, n);

    for (int i = n - 1; i >= 0; --i) {
        std::swap(a[0], a[i]);

        heapify(a, i, 0);
    }
}

int main() {
    int n;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    heapSort(a, n);

    for (int i = 0; i < n; ++i) {
        std::cout << a[i] << ' ';
    }
    return 0;
}
