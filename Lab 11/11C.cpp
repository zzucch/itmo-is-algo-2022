#include <iostream>
#include <vector>

struct edge {
  int start;
  int end;
  int length;
};

struct graph {
  int vertices{};
  std::vector<edge> edges;
  std::vector<int> paths;
  std::vector<int> prev;
};

void BellmanFord(graph &graph, int k) {
  graph.paths[0] = 0;
  int v = -1;

  for (int i = 0; i < graph.vertices; ++i) {
    bool changed = false;

    for (const edge &e : graph.edges) {
      if (graph.paths[e.start] != INT_MAX) {
        if (graph.paths[e.end] > graph.paths[e.start] + e.length) {
          graph.paths[e.end] = graph.paths[e.start] + e.length;
          graph.prev[e.end] = e.start;
          v = e.end;
          changed = true;
        }
      }
    }
    if (!changed) {
      std::cout << "YES\n";
      return;
    }
  }

  for (int i = 0; i < graph.vertices - 1; ++i) {
    v = graph.prev[v];
  }

  int len = 0;
  int tmp = v;

  while (tmp != graph.prev[v]) {
    if (++len == k) {
      break;
    }
    tmp = graph.prev[tmp];
  }

  if (len < k) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int number_of_graphs, k;
  std::cin >> number_of_graphs >> k;

  int n, m;
  int s, e, l;
  for (int i = 0; i < number_of_graphs; ++i) {
    graph graph;
    std::cin >> n >> m;
    graph.vertices = n;
    graph.edges.reserve(m);

    graph.paths.resize(n, INT_MAX);
    graph.prev.resize(n, -1);

    for (int j = 0; j < m; ++j) {
      std::cin >> s >> e >> l;
      --s, --e;

      graph.edges.push_back({s, e, l});
    }

    BellmanFord(graph, k);
  }

  return 0;
}
