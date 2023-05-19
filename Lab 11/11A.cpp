#include <iostream>
#include <vector>

struct edge {
  int vertex;
  int length;
};

struct vertex {
  std::vector<edge> adjacent;
};

bool CanBeTransferredThrough(int i, int j, int k, int max_difference) {
  return abs(i - k) <= max_difference &&
      abs(j - k) <= max_difference;
}

void FloydWarshall(std::vector<vertex> &graph,
                   std::vector<std::vector<int>> &paths,
                   int n,
                   int max_difference) {
  for (int i = 0; i < n; ++i) {
    paths[i][i] = 0;
    for (edge e : graph[i].adjacent) {
      paths[i][e.vertex] = e.length;
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if ((paths[i][k] != INT_MAX && paths[k][j] != INT_MAX)
            && CanBeTransferredThrough(i, j, k, max_difference)) {
          paths[i][j] = std::min(paths[i][j], paths[i][k] + paths[k][j]);
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, max_difference;
  std::cin >> n >> m >> max_difference;

  std::vector<vertex> graph(n);

  int s, e, l;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> e >> l;
    --s, --e;

    graph[s].adjacent.push_back({e, l});
  }

  std::vector<std::vector<int>> paths(n, std::vector<int>(n, INT_MAX));
  FloydWarshall(graph, paths, n, max_difference);

  int requests, a, b;
  std::cin >> requests;

  for (int i = 0; i < requests; ++i) {
    std::cin >> a >> b;
    --a, --b;

    if (paths[a][b] != INT_MAX) {
      std::cout << paths[a][b] << '\n';
    } else {
      std::cout << -1 << '\n';
    }
  }

  return 0;
}
