#include <iostream>

struct Node {
    int value;
    Node *left;
    Node *right;
    int position;
};

void defaultAddNode(Node *a[], int i, int K, int L, int R) {
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

int height(Node *&root) {
    if (!root) {
        return 0;
    }

    return std::max(height(root->left), height(root->right)) + 1;
}

int balanceFactor(Node *root) {
    return height(root->right) - height(root->left);
}

Node *rotateLeft(Node *&a) {
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    return b;
}

Node *rotateRight(Node *&a) {
    Node *b = a->left;

    a->left = b->right;
    b->right = a;

    return b;
}

Node *balance(Node *p) {
    if (balanceFactor(p) == 2) {
        if (balanceFactor(p->right) < 0) {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (balanceFactor(p) == -2) {
        if (balanceFactor(p->left) > 0) {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }

    return p;
}

Node *insert(Node *root, int &k) {
    if (!root) {
        root = new Node;
        root->value = k;
        root->left = nullptr;
        root->right = nullptr;
        return root;
    }

    if (k < root->value) {
        root->left = insert(root->left, k);
    } else {
        root->right = insert(root->right, k);
    }

    return balance(root);
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

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int K, L, R;
    int newNodeValue;

    std::cin >> n;

    //  for test 2
    if (n == 0) {
        int k;
        std::cin >> k;
        std::cout << "1\n" << k << " 0 0";
        return 0;
    }

    Node *array[n];

    for (int i = 0; i < n; ++i) {
        Node *tmp = new Node;
        array[i] = tmp;
    }

    for (int i = 0; i < n; ++i) {
        std::cin >> K >> L >> R;
        defaultAddNode(array, i, K, L, R);
    }

    Node *root = array[0];

    std::cin >> newNodeValue;

    root = insert(root, newNodeValue);

    std::cout << n + 1;
    int i = 1;
    traversalPlacement(root, i);

    traversal(root);
    return 0;
}
