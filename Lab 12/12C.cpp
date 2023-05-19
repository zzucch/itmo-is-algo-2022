#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define int long long

struct edge {
  int start{};
  int end{};
  int weight{};

  int id{};
  bool in_mst = false;

  bool operator<(const edge &rhs) const {
    return (weight < rhs.weight);
  }
};

struct vertex {
  bool dfs_used = false;
  std::vector<edge> adjacent;
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

int Kruskal(std::vector<vertex> &vertices,
            std::vector<edge> &edges,
            std::vector<edge> &initial_edges,
            std::vector<int> &parents,
            std::vector<int> &rank) {
  int result = 0;
  for (edge &edge : edges) {
    if (UnionSets(parents, rank, edge.start, edge.end)) {
      initial_edges[edge.id].in_mst = true;
      result += edge.weight;

      vertices[edge.start].adjacent.push_back({edge.start, edge.end,
                                               edge.weight});
      vertices[edge.end].adjacent.push_back({edge.end, edge.start,
                                             edge.weight});
    }
  }
  return result;
}

void LcaDfs(std::vector<vertex> &vertices,
            std::vector<int> &h,
            std::vector<std::vector<std::pair<int, int>>> &up,
            int current,
            int prev,
            int weight,
            int l) {
  vertices[current].dfs_used = true;
  h[current] = 1 + h[prev];
  up[current][0] = {prev, weight};

  for (int i = 1; i < l; ++i) {
    up[current][i] = {up[up[current][i - 1].first][i - 1].first,
                      std::max(up[current][i - 1].second,
                               up[up[current][i - 1].first][i - 1].second)};
  }

  for (edge &edge : vertices[current].adjacent) {
    if (!vertices[edge.end].dfs_used) {
      LcaDfs(vertices, h, up, edge.end, current, edge.weight, l);
    }
  }
}

int LcaMaxWeightEdge(std::vector<int> &h,
                     std::vector<std::vector<std::pair<int, int>>> &up,
                     int a,
                     int b,
                     int l) {
  int result = 0;
  if (h[a] < h[b]) {
    std::swap(a, b);
  }

  for (int i = l; i >= 0; --i) {
    if (h[a] - h[b] >= (1 << i)) {
      result = std::max(result, up[a][i].second);
      a = up[a][i].first;
    }
  }
  if (a == b) {
    return result;
  }
  for (int i = l; i >= 0; --i) {
    if (up[a][i].first != up[b][i].first) {
      result = std::max(result, up[a][i].second);
      result = std::max(result, up[b][i].second);
      a = up[a][i].first;
      b = up[b][i].first;
    }
  }

  result = std::max(result, std::max(up[a][0].second, up[b][0].second));
  return result;
}

main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<edge> edges(m);
  std::vector<vertex> vertices(m);

  int u, v, w;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v >> w;
    --u, --v;
    edges[i] = {u, v, w, i};
  }

  std::vector<edge> initial_edges = edges;
  std::sort(edges.begin(), edges.end());

  std::vector<int> parents(n, -1);
  std::vector<int> ranks(n, 0);
  int mst = Kruskal(vertices, edges, initial_edges, parents, ranks);

  const int l = 21;
  std::vector<std::vector<std::pair<int, int>>> up
      (n, std::vector<std::pair<int, int>>(l));
  std::vector<int> h(n, 0);

  LcaDfs(vertices, h, up, 0, 0, 0, l);

  int heaviest;
  for (edge &edge : initial_edges) {
    if (!edge.in_mst) {
      heaviest = LcaMaxWeightEdge(h, up, edge.start, edge.end, l);
      std::cout << mst + edge.weight - heaviest << '\n';
    } else {
      std::cout << mst << '\n';
    }
  }

  return 0;
}
