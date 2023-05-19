#include <iostream>
#include <vector>

struct Node {
    std::string value;
    Node *left = nullptr;
    Node *right = nullptr;

    unsigned char height;

    int timesUsed = 1;
    bool usedFirst = false;
    bool usedSecond = false;
    bool usedThird = false;
};

unsigned char height(Node *&root) {
    if (root) {
        return root->height;
    }
    return 0;
}

int balanceFactor(Node *&root) {
    return height(root->right) - height(root->left);
}

void fixHeight(Node *&root) {
    unsigned char hL = height(root->left);
    unsigned char hR = height(root->right);

    root->height = std::max(hL, hR) + 1;
}

Node *rotateLeft(Node *&a) {
    Node *b = a->right;

    a->right = b->left;
    b->left = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node *rotateRight(Node *&a) {
    Node *b = a->left;

    a->left = b->right;
    b->right = a;

    fixHeight(a);
    fixHeight(b);

    return b;
}

Node *balance(Node *&root) {
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

Node *insert(Node *&root, std::string &k, int number) {
    if (!root) {
        root = new Node;
        root->value = k;

        if (number == 1) {
            root->usedFirst = true;
        } else if (number == 2) {
            root->usedSecond = true;
        } else if (number == 3) {
            root->usedThird = true;
        }

        return root;
    }

    if (k < root->value) {
        root->left = insert(root->left, k, number);
    } else if (k == root->value) {
        if (number == 1) {
            root->usedFirst = true;
        } else if (number == 2) {
            root->usedSecond = true;
        } else if (number == 3) {
            root->usedThird = true;
        }
        ++root->timesUsed;

        return root;
    } else {
        root->right = insert(root->right, k, number);
    }

    return balance(root);
}

void buildTree(Node *&root) {
    int n;
    std::string newValue;
    std::cin >> n;

    for (int friendNum = 1; friendNum <= 3; ++friendNum) {
        for (int j = 0; j < n; ++j) {
            std::cin >> newValue;
            root = insert(root, newValue, friendNum);
        }
    }
}

void traversalPenalty(Node *&root, int result[]) {
    if (!root) {
        return;
    }

    if (root->timesUsed == 1) {
        if (root->usedFirst) {
            result[0] += 3;
        } else if (root->usedSecond) {
            result[1] += 3;
        } else if (root->usedThird) {
            result[2] += 3;
        }
    } else if (root->timesUsed == 2) {
        if (root->usedFirst) {
            result[0] += 1;
        }
        if (root->usedSecond) {
            result[1] += 1;
        }
        if (root->usedThird) {
            result[2] += 1;
        }
    }

    traversalPenalty(root->left, result);
    traversalPenalty(root->right, result);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int result[3] = {0, 0, 0};
    Node *root = nullptr;

    buildTree(root);

    traversalPenalty(root, result);

    for (auto i: result) {
        std::cout << i << ' ';
    }
    return 0;
}
