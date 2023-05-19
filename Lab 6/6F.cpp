#include <iostream>
#include <vector>

struct Node {
    std::string value{};
    Node *left = nullptr;
    Node *right = nullptr;

    int height = 1;
};

int balanceFactor(Node *&root) {
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

void duplicationCost(int &answer, const std::string &contact) {
    auto unique = contact.size();

    for (int i = 0; i < contact.size(); ++i) {
        if (contact.find(contact[i], i + 1) != std::string::npos) {
            --unique;
        }
    }
    answer += unique;
}

Node *addNode(Node *&root, std::string &k, int &answer) {
    if (!root) {
        root = new Node;
        root->value = k;

        return root;
    }

    if (k < root->value) {
        root->left = addNode(root->left, k, answer);
    } else if (k > root->value) {
        root->right = addNode(root->right, k, answer);
    } else if (k == root->value) {
        duplicationCost(answer, k);
    }

    return balance(root);
}

Node *search(Node *&root, std::string &x) {
    if (!root || root->value == x) {
        return root;
    }
    if (root->value > x) {
        return search(root->left, x);
    } else {
        return search(root->right, x);
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Node *root = nullptr;

    int n;
    int answer = 0;
    std::string contactName;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> contactName;

        root = addNode(root, contactName, answer);
    }

    std::cout << answer;
    return 0;
}
