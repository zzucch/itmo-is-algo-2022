#include <iostream>
#include <vector>
#include <deque>

struct vertex {
  bool used = false;
  std::vector<int> adjacent;
};

struct reverse_vertex {
  int component_id = -1;
  std::vector<int> adjacent;
};

void Dfs1(std::vector<vertex> &vertices, std::deque<int> &queue, int current) {
  vertices[current].used = true;

  for (int i : vertices[current].adjacent) {
    if (!vertices[i].used) {
      Dfs1(vertices, queue, i);
    }
  }
  queue.push_back(current);
}

void Dfs2(std::vector<reverse_vertex> &reversed_vertices, int component_id, int current) {
  reversed_vertices[current].component_id = component_id;

  for (int i : reversed_vertices[current].adjacent) {
    if (reversed_vertices[i].component_id == -1) {
      Dfs2(reversed_vertices, component_id, i);
    }
  }
}

void Kosaraju(std::vector<vertex> &vertices, std::vector<reverse_vertex> &reverse_vertices, int n) {
  std::deque<int> queue;

  for (int i = 0; i < n; ++i) {
    if (!vertices[i].used) {
      Dfs1(vertices, queue, i);
    }
  }

  int component_id = 0;
  while (!queue.empty()) {
    int current = queue.back();
    queue.pop_back();

    if (reverse_vertices[current].component_id == -1) {
      Dfs2(reverse_vertices, component_id, current);
      ++component_id;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, q;
  std::cin >> n >> m >> q;

  std::vector<vertex> vertices(n);
  std::vector<reverse_vertex> reversed_vertices(n);

  int start, end;
  for (int i = 0; i < m; ++i) {
    std::cin >> start >> end;
    --start, --end;

    vertices[start].adjacent.push_back(end);
    reversed_vertices[end].adjacent.push_back(start);
  }

  Kosaraju(vertices, reversed_vertices, n);

  int a, b;
  for (int i = 0; i < q; ++i) {
    std::cin >> a >> b;
    --a, --b;

    if (reversed_vertices[a].component_id == reversed_vertices[b].component_id) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }

  return 0;
}
