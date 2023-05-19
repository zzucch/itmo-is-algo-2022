#include <iostream>
#include <vector>

void update(std::vector<int> &a, int i, int &newValue, char &operation) {
    int n = a.size() / 2;
    i += n - 1;

    if (operation == '+') {
        a[i] += newValue;
    } else if (newValue <= a[i]) {
        a[i] -= newValue;
    } else {
        a[i] = 0;
    }

    while (i > 1) {
        i /= 2;
        a[i] = a[2 * i] + a[2 * i + 1];
    }
}

int rsq(std::vector<int> &a, int l, int r) {
    int result = 0;

    int n = a.size() / 2;
    l += n - 1;
    r += n - 1;

    while (l <= r) {
        if (l & 1) {
            result += a[l];
        }
        if (!(r & 1)) {
            result += a[r];
        }
        l = (l + 1) / 2;
        r = (r - 1) / 2;
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int numberOfCats;
    int numberOfEvents;
    int i; // bowl number or L for '?' operation
    int k; // meat number or R for '?' operation
    int newMem = 2;
    char operation;
    std::cin >> numberOfCats >> numberOfEvents;

    while (numberOfCats > newMem) {
        newMem *= 2;
    }
    numberOfCats = newMem * 2;

    std::vector<int> array(numberOfCats, 0);

    for (int j = 0; j < numberOfEvents; ++j) {
        std::cin >> operation >> i >> k;
        --i;

        if (operation == '+' || operation == '-') {
            update(array, i, k, operation);
        } else if (operation == '?') {
            --k;
            std::cout << rsq(array, i, k) << '\n';
        }
    }
    return 0;
}
