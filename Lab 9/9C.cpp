#include <iostream>
#include <vector>

struct vertex {
  bool used = false;
  std::vector<int> adjacent;
};

void FindAdjacent(std::vector<std::vector<int>> &floor_plan, std::vector<vertex> &vertices, int i, int j) {
  if (floor_plan[i + 1][j] != -1) {
    vertices[floor_plan[i][j]].adjacent.push_back(floor_plan[i + 1][j]);
  }
  if (floor_plan[i - 1][j] != -1) {
    vertices[floor_plan[i][j]].adjacent.push_back(floor_plan[i - 1][j]);
  }
  if (floor_plan[i][j + 1] != -1) {
    vertices[floor_plan[i][j]].adjacent.push_back(floor_plan[i][j + 1]);
  }
  if (floor_plan[i][j - 1] != -1) {
    vertices[floor_plan[i][j]].adjacent.push_back(floor_plan[i][j - 1]);
  }
}

void dfs(std::vector<vertex> &vertices, int current) {
  vertices[current].used = true;

  for (int i : vertices[current].adjacent) {
    if (!vertices[i].used) {
      dfs(vertices, i);
    }
  }

}

int RoomCount(std::vector<vertex> &vertices, int free_count) {
  int room_count = 0;

  for (int i = 0; i < free_count; ++i) {
    if (!vertices[i].used) {
      ++room_count;

      dfs(vertices, i);
    }
  }
  return room_count;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;

  std::vector<std::vector<int>> floor_plan(n);

  char tmp;
  int free_count = 0;

  for (std::vector<int> &i : floor_plan) {
    for (int j = 0; j < m; ++j) {
      std::cin >> tmp;

      if (tmp == '#') {
        i.push_back(-1);
      } else {
        i.push_back(free_count++);
      }
    }
  }

  std::vector<vertex> vertices(free_count);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (floor_plan[i][j] != -1) {
        FindAdjacent(floor_plan, vertices, i, j);
      }
    }
  }

  std::cout << RoomCount(vertices, free_count);

  return 0;
}
