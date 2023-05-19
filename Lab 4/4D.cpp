#include <iostream>

int digit(std::string a, int i) {
    return a[i] - 'a';
}

void radixSort(int n, int position, std::string a[]) {
    int index;
    int count = 0;
    int alphabetVolume = 26;
    std::string b[n];
    int c[alphabetVolume];

    for (int i = 0; i < alphabetVolume; ++i) {
        c[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        index = digit(a[i], position);
        ++c[index];
    }

    for (int i = 0; i < alphabetVolume; ++i) {
        int tmp = c[i];
        c[i] = count;
        count += tmp;
    }

    for (int i = 0; i < n; ++i) {
        index = digit(a[i], position);
        b[c[index]] = a[i];
        ++c[index];
    }

    for (int i = 0; i < n; ++i) {
        a[i] = b[i];
    }
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::string array[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    while (k > 0) {
        --m;
        --k;
        radixSort(n, m, array);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << array[i] << '\n';
    }

    return 0;
}
