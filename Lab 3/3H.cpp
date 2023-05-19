#include <iostream>

bool check(long long x, const int a[], int n, int k) {
    int partsCount = 1;
    long long currentSum = 0;

    for (int i = 0; i < n; ++i) {
        currentSum += a[i];

        if (currentSum > x){
            ++partsCount;
            currentSum = a[i];
        }
    }
    return partsCount <= k;
}

long long maxSearch(const int a[], int maxElement, long long maxSum, int n, int k) {
    long long l = maxElement;
    long long r = maxSum;

    while (l < r) {
        long long mid = (l + r) / 2;

        if (check(mid, a, n, k)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    return l;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    long long maxSum = 0;
    int maxElement = 0;

    std::cin >> n >> k;

    int ans[k - 1];
    int a[n];

    for (long long i = 0; i < n; ++i) {
        std::cin >> a[i];
        maxSum += a[i];
        maxElement = std::max(a[i], maxElement);
    }

    maxSum = maxSearch(a, maxElement, maxSum, n, k);

    long long currentSum = 0;
    int partCount = 1, j = 0;

    for (int i = 0; i < n; ++i) {
        currentSum += a[i];

        if (currentSum == maxSum && n - i != k - partCount) {
            ans[j++] = i + 1;
            currentSum = 0;
            ++partCount;
        } else if (currentSum > maxSum && n - i != k - partCount) {
            ans[j++] = i;
            currentSum = a[i];
            ++partCount;
        } else if (n - i == k - partCount) {
            while (i < n) {
                ans[j++] = i;
                ++i;
            }
        }
    }

    for (int i = 0; i < k - 1; ++i) {
        std::cout << ans[i] << ' ';
    }

    return 0;
}
