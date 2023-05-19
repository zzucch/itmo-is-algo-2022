#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int s, n;
    std::cin >> s >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int d[n + 1][s + 1];
    for (int i = 0; i <= s; ++i) {
        d[0][i] = 0;
    }
    for (int i = 0; i <= n; ++i) {
        d[i][0] = 0;
    }

    std::sort(a.begin(), a.end());

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= s; ++j) {
            if (j >= a[i - 1]) {
                d[i][j] = std::max(d[i - 1][j], d[i - 1][j - a[i - 1]] + a[i - 1]);
            } else {
                d[i][j] = d[i - 1][j];
            }
        }
    }

    std::cout << d[n][s];
    return 0;
}
