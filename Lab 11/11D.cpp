#include <iostream>
#include <vector>
#include <queue>

struct edge {
  int vertex;
  int length;
};

struct vertex {
  std::vector<edge> adjacent;
};

void Dijkstra(std::vector<vertex> &graph, std::vector<int> &paths, int start) {
  // first - path, second - vertex
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                      std::greater<>> queue;
  queue.emplace(0, start);

  paths[start] = 0;

  int current;
  while (!queue.empty()) {
    current = queue.top().second;
    queue.pop();

    for (edge e : graph[current].adjacent) {
      if (paths[e.vertex] > paths[current] + e.length) {
        paths[e.vertex] = paths[current] + e.length;
        queue.emplace(paths[e.vertex], e.vertex);
      }
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, requests, start;
  std::cin >> n >> m >> requests >> start;
  --start;

  std::vector<vertex> graph(n);

  int s, e, l;
  for (int i = 0; i < m; ++i) {
    std::cin >> s >> e >> l;
    --s, --e;

    graph[s].adjacent.push_back({e, l});
    graph[e].adjacent.push_back({s, l});
  }

  std::vector<int> paths(n, INT_MAX);
  Dijkstra(graph, paths, start);

  int end;
  for (int i = 0; i < requests; ++i) {
    std::cin >> end;
    --end;

    if (paths[end] != INT_MAX) {
      std::cout << paths[end];
    } else {
      std::cout << -1;
    }
    std::cout << '\n';
  }

  return 0;
}
