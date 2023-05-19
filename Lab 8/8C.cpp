#include <iostream>

void correctError(std::string &input) {
    int error = 0;

    for (int i = 0; i < input.length(); ++i) {
        if (input[i] == '1') {
            error ^= i + 1;
        }
    }

    if (error > 0) {
        if (input[error - 1] == '1') {
            input[error - 1] = '0';
        } else {
            input[error - 1] = '1';
        }
    }
}

std::string calculateDecodedHamming(std::string &input) {
    std::string result;

    correctError(input);

    int i = 1;

    for (int j = 0; j < input.length(); ++j) {
        if (j > (i - 1)) {
            i *= 2;
        }
        if (j < (i - 1)) {
            result += input[j];
        }
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;

    for (int i = 0; i < t; ++i) {
        std::string input;
        std::cin >> input;

        std::cout << calculateDecodedHamming(input) << '\n';
    }
  
    return 0;
}
