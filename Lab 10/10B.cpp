#include <iostream>
#include <vector>

struct vertex {
  std::vector<int> adjacent;
};

void Dfs(std::vector<vertex> &vertices, std::vector<bool> &used, int current, int goal) {
  used[current] = true;

  for (int i : vertices[current].adjacent) {
    if (!used[i]) {
      Dfs(vertices, used, i, goal);
    }
  }
}

void AreFriends(std::vector<vertex> &vertices, std::vector<bool> &used, int first, int second) {
  for (auto &&i : used) {
    i = false;
  }
  Dfs(vertices, used, first, second);

  if (used[second]) {
    std::cout << "YES\n";
  } else {
    std::cout << "NO\n";
  }
}

void RemoveFriendship(std::vector<vertex> &vertices, int first, int second) {
  for (int i = 0; i < vertices[first].adjacent.size(); ++i) {
    if (vertices[first].adjacent[i] == second) {
      vertices[first].adjacent.erase(vertices[first].adjacent.begin() + i);
      break;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int vertices_amount, edges_amount, operations_amount;
  std::cin >> vertices_amount >> edges_amount >> operations_amount;

  std::vector<vertex> vertices(vertices_amount);

  int a, b;

  for (int i = 0; i < edges_amount; ++i) {
    std::cin >> a >> b;
    --a, --b;

    vertices[a].adjacent.push_back(b);
    vertices[b].adjacent.push_back(a);
  }

  char operation;
  int first, second;
  std::vector<bool> used(vertices_amount, false);

  for (int i = 0; i < operations_amount; ++i) {
    std::cin >> operation >> first >> second;
    --first, --second;

    switch (operation) {
      case '?': {
        AreFriends(vertices, used, first, second);
        break;
      }
      case '-': {
        RemoveFriendship(vertices, first, second);
        RemoveFriendship(vertices, second, first);
        break;
      }
      default: break;
    }
  }

  return 0;
}
