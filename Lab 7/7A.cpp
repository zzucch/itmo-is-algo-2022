#include <iostream>
#include <vector>

void findLIS(const std::vector<int> &a) {
    std::vector<int> answer;
    int n = a.size();

    int prev[n - 1];
    int d[n];

    for (int i = 0; i < n; ++i) {
        d[i] = 1;
        prev[i] = -1;
        for (int j = 0; j < i; ++j) {
            if (a[j] < a[i] && d[j] + 1 > d[i]) {
                d[i] = d[j] + 1;
                prev[i] = j;
            }
        }
    }

    int pos = 0;
    int length = d[0];

    for (int i = 0; i < n; ++i) {
        if (d[i] > length) {
            pos = i;
            length = d[i];
        }
    }

    while (pos != -1) {
        answer.push_back(a[pos]);
        pos = prev[pos];
    }

    int q = answer.size();
    std::cout << q << '\n';
    for (int i = q - 1; i >= 0; --i) {
        std::cout << answer[i] << ' ';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> array(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    findLIS(array);
    return 0;
}
