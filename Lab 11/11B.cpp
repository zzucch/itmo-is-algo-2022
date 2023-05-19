#include <iostream>
#include <vector>

struct edge {
  int vertex;
  int length;
};

struct vertex {
  std::vector<edge> adjacent;
};

void FloydWarshall(std::vector<vertex> &graph,
                   std::vector<std::vector<int>> &paths, int n) {
  for (int i = 0; i < n; ++i) {
    paths[i][i] = 0;
    for (edge e : graph[i].adjacent) {
      paths[i][e.vertex] = e.length;
      paths[e.vertex][i] = e.length;
    }
  }

  for (int k = 0; k < n; ++k) {
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (paths[i][k] != INT_MAX && paths[k][j] != INT_MAX) {
          paths[i][j] = std::min(paths[i][j], paths[i][k] + paths[k][j]);
        }
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<vertex> graph(n);

  int s, e, l;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> e >> l;
    --s, --e;

    graph[s].adjacent.push_back({e, l});
    graph[e].adjacent.push_back({s, l});
  }

  std::vector<std::vector<int>> paths(n, std::vector<int>(n, INT_MAX));
  FloydWarshall(graph, paths, n);

  int answer = 0;
  for (std::vector<int> &i : paths) {
    for (int j : i) {
      if (j != INT_MAX) {
        answer = std::max(answer, j);
      }
    }
  }

  std::cout << answer;

  return 0;
}
