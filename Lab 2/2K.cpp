#include <iostream>

using namespace std;

int partition(int a[], int l, int r) {
    int x = a[(l + r) / 2];
    int i = l, j = r;
    while (true) {
        while (a[i] < x) {
            ++i;
        }
        while (a[j] > x) {
            --j;
        }
        if (i >= j) {
            return j;
        }
        swap(a[i++], a[j--]);
    }
}

int kthInOrder(int a[], int l, int r, int k) {
    if (l < r) {
        int q = partition(a, l, r);
        if (k > q) {
            kthInOrder(a, q + 1, r, k);
        } else {
            kthInOrder(a, l, q, k);
        }
        return a[k];
    }
    return 0;
}

int main() {
    int n, k, A, B, C;
    cin >> n >> k;
    int *a;
    a = (int *) malloc(n * sizeof(int));
    cin >> A >> B >> C >> a[0] >> a[1];

    for (int i = 2; i < n; ++i) {
        a[i] = A * a[i - 2] + B * a[i - 1] + C;
    }

    cout << kthInOrder(a, 0, n - 1, k - 1);

    free(a);
    return 0;
}
