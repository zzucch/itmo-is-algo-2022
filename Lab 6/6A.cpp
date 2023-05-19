#include <iostream>

struct Node {
    int K{};
    Node *left{};
    Node *right{};
    int height = 0;
};

void addNode(Node *a[], int i, int K, int L, int R) {
    a[i]->K = K;

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

int height(Node *&root) {
    if (!root) {
        return 0;
    }

    if (root->height != 0) {
        return root->height;
    }

    return std::max(height(root->left), height(root->right)) + 1;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int K, L, R;

    std::cin >> n;
    Node *array[n];

    for (int i = 0; i < n; ++i) {
        Node *tmp = new Node;
        array[i] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> K >> L >> R;
        addNode(array, i, K, L, R);
    }

    for (int i = n - 1; i >= 0; --i) {
        array[i]->height = height(array[i]);
    }

    for (int i = 0; i < n; ++i) {
        if (array[i]->left && array[i]->right) {
            std::cout << array[i]->right->height - array[i]->left->height << '\n';
        } else if (array[i]->left) {
            std::cout << -array[i]->left->height << '\n';
        } else if (array[i]->right) {
            std::cout << array[i]->right->height << '\n';
        } else {
            std::cout << 0 << '\n';
        }
    }
    return 0;
}
