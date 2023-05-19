#include <iostream>
#include <vector>
#include <deque>

struct Node {
  bool used = false;
  int distance = 0;
  std::vector<int> adjacent;
};

int bfs(std::vector<Node> &vertices, int start, int finish) {
  std::deque<int> queue;
  vertices[start].used = true;
  queue.push_back(start);

  int current;

  while (!queue.empty()) {
    current = queue.back();
    queue.pop_back();

    if (current == finish) {
      return vertices[current].distance;
    }

    for (int i : vertices[current].adjacent) {
      if (!vertices[i].used) {
        vertices[i].used = true;
        vertices[i].distance = vertices[current].distance + 1;

        queue.push_front(i);
      }
    }
  }

  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<Node> vertices(n);

  int u, v;
  for (int i = 0; i < m; ++i) {
    std::cin >> u >> v;

    --u, --v;
    vertices[v].adjacent.push_back(u);
    vertices[u].adjacent.push_back(v);
  }

  int start, finish;
  std::cin >> start >> finish;
  --start, --finish;

  std::cout << bfs(vertices, start, finish);

  return 0;
}
