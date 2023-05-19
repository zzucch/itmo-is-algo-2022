#include <iostream>

struct Node {
    int value{};
    Node *left{};
    Node *right{};
};

void addNode(Node *a[], int i, int K, int L, int R) {
    a[i]->value = K;

    if (L == 0) {
        a[i]->left = nullptr;
    } else {
        a[i]->left = a[L - 1];
    }
    if (R == 0) {
        a[i]->right = nullptr;
    } else {
        a[i]->right = a[R - 1];
    }
}

bool check(Node *v, int min, int max) {
    if (v == nullptr) {
        return true;
    }
    if (v->value <= min || v->value >= max) {
        return false;
    }
    return check(v->left, min, v->value) && check(v->right, v->value, max);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int K, L, R;

    std::cin >> n;

    if (n == 0) {
        std::cout << "YES";
        return 0;
    }

    Node *array[n];

    for (int i = 0; i < n; ++i) {
        Node *newNode = new Node;
        array[i] = newNode;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> K >> L >> R;
        addNode(array, i, K, L, R);
    }

    std::cout << (check(array[0], INT_MIN, INT_MAX) ? "YES" : "NO");
    return 0;
}
