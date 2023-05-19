#include <iostream>

bool isHeap(const int a[], int n) {
    bool result = true;
    for (int i = 1; i < n; ++i) {
        if (2 * i - 1 < n && a[i - 1] > a[2 * i - 1]) {
            result = false;
            break;
        }
        if (2 * i < n && a[i - 1] > a[2 * i]) {
            result = false;
            break;
        }
    }
    return result;
}

int main() {
    int n;
    bool ans;
    std::cin >> n;
    int a[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    ans = isHeap(a, n);

    std::cout << (ans ? "YES" : "NO");
    return 0;
}
