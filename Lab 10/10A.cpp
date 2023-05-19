#include <iostream>
#include <vector>

struct vertex {
  bool safe = true;
  bool used = false;
  int component = -1;
  std::vector<int> adjacent;
};

struct component {
  bool safe = true;
};

void Dfs(std::vector<vertex> &vertices,
         std::vector<component> &connected_components,
         int current,
         int current_component) {
  vertices[current].used = true;
  vertices[current].component = current_component + 1;

  if (connected_components[current_component].safe && !vertices[current].safe) {
    connected_components[current_component].safe = false;
  }

  for (int i : vertices[current].adjacent) {
    if (!vertices[i].used) {
      Dfs(vertices, connected_components, i, current_component);
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int room_amount, door_amount;
  std::cin >> room_amount >> door_amount;

  std::vector<vertex> rooms(room_amount);

  int a, b;
  for (int i = 0; i < door_amount; ++i) {
    std::cin >> a >> b;
    --a, --b;

    rooms[a].adjacent.push_back(b);
    rooms[b].adjacent.push_back(a);
  }

  int tmp;

  for (int i = 0; i < room_amount; ++i) {
    std::cin >> tmp;
    if (tmp == 1) {
      rooms[i].safe = false;
    }
  }

  std::vector<component> connected_components;
  int component_amount = 0;

  for (int i = 0; i < room_amount; ++i) {
    if (!rooms[i].used) {
      connected_components.push_back({true});
      ++component_amount;
      Dfs(rooms, connected_components, i, component_amount - 1);
    }
  }

  std::cout << component_amount << '\n';

  for (const vertex &i : rooms) {
    std::cout << i.component << " ";
  }
  std::cout << '\n';

  for (component i : connected_components) {
    if (i.safe) {
      std::cout << "0 ";
    } else {
      std::cout << "1 ";
    }
  }

  return 0;
}
