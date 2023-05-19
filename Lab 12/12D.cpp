#include <iostream>
#include <vector>

struct vertex {
  std::vector<int> adjacent;
};

bool DfsKuhn(std::vector<vertex> &graph,
             std::vector<bool> &used,
             std::vector<int> &matching,
             int current) {
  if (used[current]) {
    return false;
  }
  used[current] = true;

  for (int i : graph[current].adjacent) {
    if (matching[i] == -1 || DfsKuhn(graph, used, matching, matching[i])) {
      matching[i] = current;
      return true;
    }
  }
  return false;
}

int Kuhn(std::vector<vertex> &graph, int n, int m) {
  int result = 0;
  std::vector<bool> used(n * m, false);
  std::vector<int> matching(n * m, -1);

  for (int i = 0; i < n * m; ++i) {
    std::fill(used.begin(), used.end(), false);
    if (DfsKuhn(graph, used, matching, i)) {
      ++result;
    }
  }

  return result;
}

int GetId(int x, int y, int m) {
  return x * m + y;
}

void BuildGraph(std::vector<vertex> &graph,
                std::vector<std::vector<bool>> &crossed,
                int n,
                int m) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!crossed[i][j]) {
        if (i > 0 && !crossed[i - 1][j]) {
          graph[GetId(i, j, m)].adjacent.push_back(GetId(i - 1, j, m));
          graph[GetId(i - 1, j, m)].adjacent.push_back(GetId(i, j, m));
        }
        if (j > 0 && !crossed[i][j - 1]) {
          graph[GetId(i, j, m)].adjacent.push_back(GetId(i, j - 1, m));
          graph[GetId(i, j - 1, m)].adjacent.push_back(GetId(i, j, m));
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<std::vector<bool>> crossed(n, std::vector<bool>(m, false));

  int x, y;
  for (int i = 0; i < q; ++i) {
    std::cin >> x >> y;
    crossed[x - 1][y - 1] = true;
  }

  std::vector<vertex> graph(n * m);
  BuildGraph(graph, crossed, n, m);

  std::cout << Kuhn(graph, n, m);

  return 0;
}
