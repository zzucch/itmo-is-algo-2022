#include <iostream>
#include <vector>

template<typename T>
struct Node {
    T value{};

    int parent = -1;
    int left = -1;
    int right = -1;
};

template<typename T>
void buildTree(std::vector<Node<T>> &tree, int &n) {
    T tmp;
    for (int i = 1; i <= n; ++i) {
        std::cin >> tmp;
        tree[i - 1].value = tmp;

        if (2 * i - 1 < n) {
            tree[i - 1].left = 2 * i - 1;
            tree[2 * i - 1].parent = i - 1;
        }
        if (2 * i < n) {
            tree[i - 1].right = 2 * i;
            tree[2 * i].parent = i - 1;
        }
    }
}

template<typename T>
void changeTree(std::vector<Node<T>> &tree, int &q) {
    int i;
    for (int j = 0; j < q; ++j) {
        std::cin >> i;
        --i;

        if (tree[i].parent == -1) {
            continue;
        }

        int il = tree[i].left;
        int ir = tree[i].right;
        int p = tree[i].parent;
        int pp = tree[p].parent;

        if (p == tree[pp].left) {
            tree[i].parent = pp;
            tree[pp].left = i;
        } else {
            tree[i].parent = pp;
            tree[pp].right = i;
        }

        if (i == tree[p].left) {
            if (il != -1) {
                tree[il].parent = p;
            }
            tree[p].left = il;

            tree[p].parent = i;
            tree[i].left = p;
        } else {
            if (ir != -1) {
                tree[ir].parent = p;
            }
            tree[p].right = ir;

            tree[p].parent = i;
            tree[i].right = p;
        }
    }
}

template<typename T>
void postorderTraversal(std::vector<Node<T>> &tree, int j, std::vector<T> &tree_LRV, int &i) {
    if (tree[j].left != -1) {
        postorderTraversal(tree, tree[j].left, tree_LRV, i);
    }
    if (tree[j].right != -1) {
        postorderTraversal(tree, tree[j].right, tree_LRV, i);
    }
    tree_LRV[i++] = tree[j].value;
}

template<typename T>
int findRoot(std::vector<Node<T>> &tree) {
    for (int i = 0; i < tree.size(); ++i) {
        if (tree[i].parent == -1) {
            return i;
        }
    }
    return 0;
}

template<typename T>
void initialBuild(std::vector<Node<T>> &tree, std::vector<T> &tree_LRV, int &n, int &q) {
    buildTree(tree, n);
    changeTree(tree, q);

    int root = findRoot(tree);
    int i = 0;
    postorderTraversal(tree, root, tree_LRV, i);
}

std::string decompressRLE(std::vector<int> &counts, std::vector<char> &letters, int &n) {
    std::string result;

    for (int i = 0; i < n; ++i) {
        std::string tmp(counts[i], letters[i]);
        result += tmp;
    }

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q1, q2;

    std::cin >> n >> q1;

    std::vector<Node<int>> tree1(n);
    std::vector<int> tree_LRV1(n);

    initialBuild(tree1, tree_LRV1, n, q1);

    std::cin >> n >> q2;

    std::vector<Node<char>> tree2(n);
    std::vector<char> tree_LRV2(n);
    initialBuild(tree2, tree_LRV2, n, q2);

    std::cout << decompressRLE(tree_LRV1, tree_LRV2, n) << std::endl;

    return 0;
}
