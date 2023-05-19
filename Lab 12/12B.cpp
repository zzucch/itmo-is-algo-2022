#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
  long long start;
  long long end;
  long long weight;

  bool operator<(const edge &rhs) const {
    return (weight < rhs.weight);
  }
};

long long FindSet(std::vector<long long> &parents, long long v) {
  if (parents[v] == -1) {
    return v;
  }
  return parents[v] = FindSet(parents, parents[v]);
}

bool UnionSets(std::vector<long long> &parents,
               std::vector<long long> &rank,
               long long a,
               long long b) {
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

long long Kruskal(std::vector<edge> &edges,
            std::vector<long long> &parents,
            std::vector<long long> &ranks) {
  long long result = 0;

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

  long long u, v, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    edges[i] = {u - 1, v - 1, w};
  }
  std::sort(edges.begin(), edges.end());

  std::vector<long long> parents(n, -1);
  std::vector<long long> ranks(n, 0);

  std::cout << Kruskal(edges, parents, ranks);

  return 0;
}
