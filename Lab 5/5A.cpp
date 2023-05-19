#include <iostream>

struct Node {
    int K{};
    Node *left{};
    Node *right{};

    int height = 1;
};

void addNode(Node a[], int i, int K, int L, int R) {
    a[i].K = K;

    if (L == 0) {
        a[i].left = nullptr;
    } else {
        a[i].left = &a[L - 1];
        a[i].left->height += a[i].height;
    }

    if (R == 0) {
        a[i].right = nullptr;
    } else {
        a[i].right = &a[R - 1];
        a[i].right->height += a[i].height;
    }
}

int maxHeight(Node a[], int n) {
    int result = 0;

    for (int i = 0; i < n; ++i) {
        result = std::max(result, a[i].height);
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int K, L, R;

    std::cin >> n;
    Node array[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> K >> L >> R;
        addNode(array, i, K, L, R);
    }

    std::cout << maxHeight(array, n);
    return 0;
}
