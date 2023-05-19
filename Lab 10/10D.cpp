#include <iostream>
#include <vector>
#include <deque>

struct vertex {
  std::vector<int> adjacent;
};

void Dfs(std::vector<vertex> &vertices, std::vector<bool> &used, std::deque<int> &sorted, int current) {
  used[current] = true;

  for (int i : vertices[current].adjacent) {
    if (!used[i]) {
      Dfs(vertices, used, sorted, i);
    }
  }
  sorted.push_back(current);
}

void TopologicalSort(std::vector<vertex> &vertices, std::deque<int> &sorted, int n) {
  std::vector<bool> used(n, false);

  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      Dfs(vertices, used, sorted, i);
    }
  }
}

void RenameVertices(std::deque<int> &sorted, int n) {
  int placement;
  int id = 1;
  std::vector<int> result(n);

  while (!sorted.empty()) {
    placement = sorted.back();
    sorted.pop_back();

    result[placement] = id++;
  }

  for (int i : result) {
    std::cout << i << ' ';
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<vertex> vertices(n);

  int tmp_a, tmp_b;
  for (int i = 0; i < m; ++i) {
    std::cin >> tmp_a >> tmp_b;
    --tmp_a, --tmp_b;

    vertices[tmp_a].adjacent.push_back(tmp_b);
  }

  std::deque<int> sorted;

  TopologicalSort(vertices, sorted, n);
  RenameVertices(sorted, n);

  return 0;
}
