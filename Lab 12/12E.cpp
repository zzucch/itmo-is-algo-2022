#include <iostream>
#include <vector>
#include <deque>

struct vertex {
  std::vector<int> adjacent;
};

int Bfs(std::vector<vertex> &graph,
        std::vector<int> &parents,
        std::vector<std::vector<int>> &residual,
        int source,
        int sink) {
  std::deque<int> q;
  q.push_back(source);

  parents[source] = -1;

  while (!q.empty()) {
    int current = q.front();
    q.pop_front();

    for (int i : graph[current].adjacent) {
      if (parents[i] == -1 && residual[current][i] > 0) {
        parents[i] = current;
        q.push_back(i);
      }
    }
  }

  if (parents[sink] == -1) {
    return 0;
  }

  int path_flow = INT_MAX;
  for (int i = sink; i != source; i = parents[i]) {
    int j = parents[i];
    path_flow = std::min(path_flow, residual[j][i]);
  }

  for (int i = sink; i != source; i = parents[i]) {
    int j = parents[i];
    residual[j][i] -= path_flow;
    residual[i][j] += path_flow;
  }

  return path_flow;
}

int MaxFlow(std::vector<vertex> &graph,
            std::vector<std::vector<int>> &residual,
            int source,
            int sink,
            int n) {
  std::vector<int> parents(n, -1);
  int path_flow = 123;

  int max_flow = 0;
  while (path_flow != 0) {
    path_flow = Bfs(graph, parents, residual, source, sink);
    max_flow += path_flow;

    std::fill(parents.begin(), parents.end(), -1);
  }

  return max_flow;
}

int main() {
  int n, m;
  std::cin >> n >> m;

  std::vector<vertex> graph(n);
  std::vector<std::vector<int>> capacity(n, std::vector<int>(n, 0));

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    --u, --v;

    graph[u].adjacent.push_back(v);
    capacity[u][v] += w;
  }

  int source = 0;
  int sink = n - 1;

  std::cout << MaxFlow(graph, capacity, source, sink, n);

  return 0;
}
