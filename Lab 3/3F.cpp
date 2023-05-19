#include <iostream>

int binarySearchLeft(int array[], int x, int length) {
    int l = -1;
    int r = length;

    while (r > l + 1) {
        int m = (l + r) / 2;

        if (array[m] < x) {
            l = m;
        } else {
            r = m;
        }
    }
    if (r < length && array[r] == x) {
        return r + 1;
    } else {
        return -1;
    }
}

int binarySearchRight(int array[], int x, int length) {
    int l = -1;
    int r = length;

    while (r > l + 1) {
        int m = (l + r) / 2;

        if (array[m] <= x) {
            l = m;
        } else {
            r = m;
        }
    }
    if (l < length && array[l] == x) {
        return l + 1;
    } else {
        return -1;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n;
  
    int array[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    std::cin >> m;

    for (int i = 0; i < m; ++i) {
        int tmp;
        std::cin >> tmp;
        std::cout << binarySearchLeft(array, tmp, n) << ' ' << binarySearchRight(array, tmp, n) << '\n';
    }

    std::cout << std::endl;
    return 0;
}
