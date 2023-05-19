#include <iostream>

struct Node {
    int value;
    Node *left;
    Node *right;
};

void addNode(Node a[], int i, int l, int r) {
    if (l != 0) {
        a[i].left = &a[l - 1];
    } else {
        a[i].left = nullptr;
    }
    if (r != 0) {
        a[i].right = &a[r - 1];
    } else {
        a[i].right = nullptr;
    }
}

void inOrderTraversalInsert(Node *x, int &i) {
    if (x != nullptr) {
        inOrderTraversalInsert(x->left, i);
        x->value = i++;
        inOrderTraversalInsert(x->right, i);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int left;
    int right;

    int k = 1;

    std::cin >> n;

    Node a[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> left >> right;
        addNode(a, i, left, right);
    }

    inOrderTraversalInsert(a, k);

    for (int i = 0; i < n; ++i) {
        std::cout << a[i].value << ' ';
    }
    return 0;
}
