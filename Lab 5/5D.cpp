#include <iostream>

struct Node {
    int value{};
    Node *left = nullptr;
    Node *right = nullptr;
};

Node *minValueNode(Node *root) {
    Node *tmp = root;

    while (tmp && tmp->left) {
        tmp = tmp->left;
    }

    return tmp;
}

Node *search(Node *x, int k) {
    if (x == nullptr || x->value == k) {
        return x;
    }

    if (x->value > k) {
        return search(x->left, k);
    } else {
        return search(x->right, k);
    }
}

Node *insert(Node *&root, int k) {
    if (!root) {
        root = new Node;
        root->value = k;

        return root;
    } else if (k < root->value) {
        root->left = insert(root->left, k);
    } else if (k > root->value) {
        root->right = insert(root->right, k);
    }

    return root;
}

Node *next(Node *root, int x) {
    Node *current = root;
    Node *successor = nullptr;

    while (current != nullptr) {
        if (current->value > x) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    return successor;
}

Node *prev(Node *root, int x) {
    Node *current = root;
    Node *successor = nullptr;

    while (current != nullptr) {
        if (current->value >= x) {
            current = current->left;
        } else {
            successor = current;
            current = current->right;
        }
    }

    return successor;
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
        if (root->left == nullptr && root->right == nullptr) {
            return nullptr;
        } else if (root->left == nullptr) {
            root = root->right;
        } else if (root->right == nullptr) {
            root = root->left;
        } else {
            root->value = minValueNode(root->right)->value;
            root->right = deleteNode(root->right, root->value);
        }
    }

    return root;
}

void exists(Node *root, int x) {
    if (search(root, x) != nullptr) {
        std::cout << "true\n";
    } else {
        std::cout << "false\n";
    }
}

void nextResult(Node *root, int x) {
    if (next(root, x) != nullptr) {
        std::cout << next(root, x)->value << '\n';
    } else {
        std::cout << "none\n";
    }
}

void prevResult(Node *root, int x) {
    if (prev(root, x) != nullptr) {
        std::cout << prev(root, x)->value << '\n';
    } else {
        std::cout << "none\n";
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int x;
    std::string operation;

    Node *root = nullptr;

    while (std::cin >> operation) {
        std::cin >> x;
        if (operation == "insert") {
            insert(root, x);
        } else if (operation == "delete") {
            root = deleteNode(root, x);
        } else if (operation == "exists") {
            exists(root, x);
        } else if (operation == "next") {
            nextResult(root, x);
        } else if (operation == "prev") {
            prevResult(root, x);
        }
    }

    return 0;
}
