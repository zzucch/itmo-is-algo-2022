#include <iostream>
#include <vector>
#include <algorithm>

struct edge {
  int start;
  int end;
  int weight;
  bool in_mst;

  bool operator<(const edge &rhs) const {
    return (weight < rhs.weight);
  }

  bool operator!=(const edge &rhs) const {
    return start != rhs.start || end != rhs.end;
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
      edge.in_mst = true;
      result += edge.weight;
    }
  }
  return result;
}

int SecondMST(std::vector<edge> &edges,
              std::vector<int> &parents,
              std::vector<int> &ranks,
              int mst) {
  int result = 1e9;
  int tmp;

  for (edge &excluded : edges) {
    if (excluded.in_mst) {
      std::fill(parents.begin(), parents.end(), -1);
      std::fill(ranks.begin(), ranks.end(), 0);
      tmp = 0;

      for (edge &edge : edges) {
        if (edge != excluded
            && UnionSets(parents, ranks, edge.start, edge.end)) {
          edge.in_mst = true;
          tmp += edge.weight;
        }
      }
      if (tmp < result && tmp > mst) {
        result = tmp;
      }
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
    edges[i] = {u - 1, v - 1, w, false};
  }
  std::sort(edges.begin(), edges.end());

  std::vector<int> parents(n, -1);
  std::vector<int> ranks(n, 0);

  int mst = Kruskal(edges, parents, ranks);
  std::cout << mst << ' ';
  std::cout << SecondMST(edges, parents, ranks, mst);

  return 0;
}
