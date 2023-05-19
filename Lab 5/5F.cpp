#include <iostream>

struct Node {
    int value{};
    Node *left = nullptr;
    Node *right = nullptr;
};

void recoverFromPreorder(int const a[], Node *root, int n, int &i, int min, int max) {
    if (i == n || a[i] < min || a[i] > max) {
        return;
    }

    if (a[i] < root->value) {
        root->left = new Node;
        root->left->value = a[i++];

        recoverFromPreorder(a, root->left, n, i, min, root->value);

        if (i == n || a[i] < min || a[i] > max) {
            return;
        }
    }
    if (a[i] > root->value) {
        root->right = new Node;
        root->right->value = a[i++];

        recoverFromPreorder(a, root->right, n, i, root->value, max);
    }
}

void postorderTraversalPrint(Node *tmp) {
    if (tmp != nullptr) {
        postorderTraversalPrint(tmp->left);
        postorderTraversalPrint(tmp->right);
        std::cout << tmp->value << ' ';
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;

    int outset[n];

    for (int i = 0; i < n; ++i) {
        std::cin >> outset[i];
    }

    Node *root = new Node;
    int i = 0;
    root->value = outset[i++];

    recoverFromPreorder(outset, root, n, i, INT_MIN, INT_MAX);

    postorderTraversalPrint(root);
    return 0;
}
