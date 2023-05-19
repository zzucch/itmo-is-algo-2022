#include <iostream>
#include <vector>

struct Node {
    int value{};
    Node *left = nullptr;
    Node *right = nullptr;

    int height = 1;
};

int balanceFactor(Node *root) {
    int hR = 0;
    int hL = 0;

    if (root->right) {
        hR = root->right->height;
    }
    if (root->left) {
        hL = root->left->height;
    }
    return hR - hL;
}

void fixHeight(Node *&root) {
    int hR = 0;
    int hL = 0;

    if (root->right) {
        hR = root->right->height;
    }
    if (root->left) {
        hL = root->left->height;
    }

    root->height = std::max(hR, hL) + 1;
}

Node *rotateLeft(Node *a) {
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node *rotateRight(Node *a) {
    Node *b = a->left;

    a->left = b->right;
    b->right = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node *balance(Node *root) {
    fixHeight(root);

    int bFactor = balanceFactor(root);

    if (bFactor == 2) {
        if (balanceFactor(root->right) < 0) {
            root->right = rotateRight(root->right);
        }
        return rotateLeft(root);
    }
    if (bFactor == -2) {
        if (balanceFactor(root->left) > 0) {
            root->left = rotateLeft(root->left);
        }
        return rotateRight(root);
    }

    return root;
}

Node *addNode(Node *root, int k) {
    if (!root) {
        root = new Node;
        root->value = k;

        return root;
    }

    if (k < root->value) {
        root->left = addNode(root->left, k);
    } else {
        root->right = addNode(root->right, k);
    }

    return balance(root);
}

Node *findMax(Node *root) { // & ruins
    while (root->right) {
        root = root->right;
    }

    return root;
}

Node *removeMax(Node *root) {
    if (!root->right) {
        return root->left;
    }
    root->right = removeMax(root->right);

    return balance(root);
}

Node *deleteNode(Node *root, int x) {
    if (!root) {
        return root;
    }

    if (x < root->value) {
        root->left = deleteNode(root->left, x);
    } else if (x > root->value) {
        root->right = deleteNode(root->right, x);
    } else {
        Node *l = root->left;
        Node *r = root->right;

        delete root;

        if (l == nullptr) {
            return r;
        }

        Node *newRoot = findMax(l);
        newRoot->left = removeMax(l);
        newRoot->right = r;

        return balance(newRoot);
    }

    return balance(root);
}

Node *search(Node *root, int x) {
    if (!root || root->value == x) {
        return root;
    }
    if (root->value > x) {
        return search(root->left, x);
    } else {
        return search(root->right, x);
    }
}

void check(Node *root, int x) {
    if (search(root, x)) {
        std::cout << "Y\n";
    } else {
        std::cout << "N\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node *root = nullptr;

    int n;
    int newValue;
    char operation;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> operation >> newValue;

        if (operation == 'A') {
            if (!search(root, newValue)) {
                root = addNode(root, newValue);
            }

            std::cout << balanceFactor(root) << '\n';
        } else if (operation == 'D') {
            root = deleteNode(root, newValue);

            if (!root) {
                std::cout << "0\n";
            } else {
                std::cout << balanceFactor(root) << '\n';
            }
        } else if (operation == 'C') {
            check(root, newValue);
        }
    }

    return 0;
}
