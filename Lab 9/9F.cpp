#include <iostream>
#include <vector>
#include <deque>

struct vertex {
  int distance = 0;
  bool used = false;
  std::vector<int> adjacent;
};

void bfs(std::vector<vertex> &vertices, int start) {
  std::deque<int> queue;
  queue.push_back(start);

  vertices[start].distance = 0;
  vertices[start].used = true;

  int current;

  while (!queue.empty()) {
    current = queue.back();
    queue.pop_back();

    for (int i : vertices[current].adjacent) {
      if (!vertices[i].used) {
        vertices[i].used = true;
        vertices[i].distance = vertices[current].distance + 1;

        queue.push_front(i);
      }
    }
  }
}

bool HasHamiltonianPath(std::vector<vertex> &vertices, int n) {
  bfs(vertices, 0);

  int max_distance_vertex = 0;
  for (int i = 0; i < n; ++i) {
    vertices[i].used = false;

    if (vertices[i].distance > vertices[max_distance_vertex].distance) {
      max_distance_vertex = i;
    }
  }

  bfs(vertices, max_distance_vertex);

  int max_distance = 0;
  for (const vertex& i : vertices) {
    max_distance = std::max(max_distance, i.distance);
  }

  if (max_distance == n - 1) {
    return true;
  } else {
    return false;
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<vertex> vertices(n);

  int u, v;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;

    --u, --v;
    vertices[v].adjacent.push_back(u);
    vertices[u].adjacent.push_back(v);
  }

  if (HasHamiltonianPath(vertices, n)) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}
