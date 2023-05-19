#include <iostream>
#include <vector>
#include <deque>

struct edge {
  int vertex;
  int length;
};

struct vertex {
  std::vector<edge> adjacent;
};

void Dfs(std::vector<vertex> &vertices,
         std::vector<bool> &used,
         std::deque<int> &sorted,
         int current) {
  used[current] = true;

  for (edge e : vertices[current].adjacent) {
    if (!used[e.vertex]) {
      Dfs(vertices, used, sorted, e.vertex);
    }
  }
  sorted.push_back(current);
}

void TopologicalSort(std::vector<vertex> &vertices,
                     std::deque<int> &sorted,
                     int n) {
  std::vector<bool> used(n, false);

  for (int i = 0; i < n; ++i) {
    if (!used[i]) {
      Dfs(vertices, used, sorted, i);
    }
  }
}

void DagPaths(std::vector<vertex> &graph, std::vector<int> &paths, int start,
              int n) {
  std::deque<int> sorted;
  TopologicalSort(graph, sorted, n);

  paths[start] = 0;

  for (auto r_it = sorted.rbegin(); r_it != sorted.rend(); ++r_it) {
    for (edge e : graph[*r_it].adjacent) {
      if (paths[*r_it] != INT_MAX) {
        paths[e.vertex] = std::min(paths[e.vertex], paths[*r_it] + e.length);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, start, target;
  std::cin >> n >> m >> start >> target;
  --start, --target;

  std::vector<vertex> graph(n);

  int s, e, l;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> e >> l;
    --s, --e;

    graph[s].adjacent.push_back({e, l});
  }

  std::vector<int> paths(n, INT_MAX);
  DagPaths(graph, paths, start, n);

  if (paths[target] != INT_MAX) {
    std::cout << paths[target];
  } else {
    std::cout << -1;
  }

  return 0;
}
