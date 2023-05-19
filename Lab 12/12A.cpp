#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
  int start;
  int end;
  int weight;

  bool operator<(const edge &rhs) const {
    return (weight < rhs.weight);
  }
};

int FindSet(std::vector<int> &parents, int v) {
  if (parents[v] == -1) {
    return v;
  }
  return parents[v] = FindSet(parents, parents[v]);
}

bool UnionSets(std::vector<int> &parents,
               std::vector<int> &rank,
               int a,
               int b) {
  a = FindSet(parents, a);
  b = FindSet(parents, b);

  if (a != b) {
    if (rank[a] < rank[b]) {
      std::swap(a, b); // now r(a) >= r(b)
    }
    parents[b] = a;
    if (rank[a] == rank[b]) {
      ++rank[a];
    }
    return true;
  }
  return false;
}

int Kruskal(std::vector<edge> &edges,
            std::vector<int> &parents,
            std::vector<int> &ranks) {
  int result = 0;

  for (edge &edge : edges) {
    if (UnionSets(parents, ranks, edge.start, edge.end)) {
      result += edge.weight;
    }
  }
  return result;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<edge> edges(m);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }
  std::sort(edges.begin(), edges.end());

  std::vector<int> parents(n, -1);
  std::vector<int> ranks(n, 0);

  std::cout << Kruskal(edges, parents, ranks);

  return 0;
}
