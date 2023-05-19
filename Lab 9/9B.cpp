#include <iostream>
#include <vector>

void dfs(std::vector<std::vector<int>> &vertices, int i, std::vector<bool> &used, int prev) {
    used[i] = true;

    for (int &j: vertices[i]) {
        if (!used[j]) {
            dfs(vertices, j, used, i);
        } else if (j != prev) {
            std::cout << "YES";
            exit(0);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> vertices(n);

    int u, v;
    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;

        --u, --v;
        vertices[v].push_back(u);
        vertices[u].push_back(v);
    }

    std::vector<bool> used(n, false);
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(vertices, i, used, i);
        }
    }

    std::cout << "NO";
    return 0;
}
