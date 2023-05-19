#include <iostream>
#include <vector>

struct Node {
    std::string value;
    Node *left = nullptr;
    Node *right = nullptr;
};

Node *insert(Node *&root, const std::string &k) {
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

void buildTree(Node *&root, std::vector<std::string> &a, int n) {
    for (int i = 0; i < n; ++i) {
        insert(root, a[i]);
    }
}

Node *search(Node *x, const std::string &k) {
    if (x == nullptr || x->value == k) {
        return x;
    }

    if (x->value > k) {
        return search(x->left, k);
    } else {
        return search(x->right, k);
    }
}

void justice(int result[], int studentID, const std::vector<std::string> &domain, Node *peerOne, Node *peerTwo) {
    int troubleCount;

    for (const std::string &i: domain) {
        troubleCount = 0;
        if (search(peerOne, i)) {
            ++troubleCount;
        }
        if (search(peerTwo, i)) {
            ++troubleCount;
        }

        if (troubleCount == 0) {
            result[studentID] += 3;
        } else if (troubleCount == 1) {
            result[studentID] += 1;
        }
    }


}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    int result[3] = {0, 0, 0};
    Node *firstRoot = nullptr;
    Node *secondRoot = nullptr;
    Node *thirdRoot = nullptr;

    std::cin >> n;

    std::vector<std::string> first(n);
    std::vector<std::string> second(n);
    std::vector<std::string> third(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> first[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> second[i];
    }
    for (int i = 0; i < n; ++i) {
        std::cin >> third[i];
    }

    buildTree(firstRoot, first, n);
    buildTree(secondRoot, second, n);
    buildTree(thirdRoot, third, n);

    justice(result, 0, first, secondRoot, thirdRoot);
    justice(result, 1, second, firstRoot, thirdRoot);
    justice(result, 2, third, firstRoot, secondRoot);

    for (auto i: result) {
        std::cout << i << ' ';
    }
    return 0;
}
