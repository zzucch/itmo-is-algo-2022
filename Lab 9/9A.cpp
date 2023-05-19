#include <iostream>
#include <cmath>

std::string decimalToBinary(int num, int digits) {
    std::string reversed(digits, '0');

    int i = 0;
    while (num > 0) {
        reversed[i] = (num % 2) == 1 ? '1' : '0';
        num /= 2;
        ++i;
    }

    return {reversed.rbegin(), reversed.rend()};
}

void toGray(int num, int digits) {
    num ^= (num >> 1);

    std::cout << decimalToBinary(num, digits) << '\n';
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int amount = pow(2, n);

    for (int i = 0; i < amount; ++i) {
        toGray(i, n);
    }

    return 0;
}
