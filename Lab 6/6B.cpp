#include <iostream>

struct Node {
    int value;
    Node *left;
    Node *right;
    int position;
};

int height(Node *&root) {
    if (!root) {
        return 0;
    }

    return std::max(height(root->left), height(root->right)) + 1;
}

bool balance(Node *&root) {
    return height(root->left) <= height(root->right);
}

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

void traversalPlacement(Node *root, int &i) {
    if (!root) {
        return;
    }
    root->position = i++;
    traversalPlacement(root->left, i);
    traversalPlacement(root->right, i);
}

void traversal(Node *root) {
    if (!root) {
        return;
    }

    std::cout << '\n' << root->value << ' ';

    if (!root->left) {
        std::cout << 0 << ' ';
    } else {
        std::cout << root->left->position << ' ';
    }
    if (!root->right) {
        std::cout << 0;
    } else {
        std::cout << root->right->position;
    }


    traversal(root->left);
    traversal(root->right);
}

Node *rotateLeft(Node *&a) {
    if (balance(a->right)) {
        Node *b = a->right;

        a->right = b->left;
        b->left = a;

        return b;
    } else {
        Node *b = a->right;
        Node *c = b->left;

        a->right = c->left;
        b->left = c->right;

        c->left = a;
        c->right = b;

        return c;
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int K, L, R;
    Node *root;

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

    std::cout << n;

    root = rotateLeft(array[0]);

    int i = 1;
    traversalPlacement(root, i);

    traversal(root);

    return 0;
}
