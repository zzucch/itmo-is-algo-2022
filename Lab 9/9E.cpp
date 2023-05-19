#include <iostream>
#include <vector>
#include <deque>

struct coordinates {
  int x;
  int y;
  int z;
};

void MakeBuildings(std::vector<std::vector<std::vector<bool>>> &space, const int building_amount) {
  int x, y, z, height;

  for (int i = 0; i < building_amount; ++i) {
    std::cin >> x >> y >> z >> height;

    for (int j = 0; j < height; ++j) {
      space[x][y][z + j] = false;
    }
  }
}

bool Finish(coordinates &current, coordinates &finish) {
  return (current.x == finish.x)
      && (current.y == finish.y)
      && (current.z == finish.z);
}

void GetAdjacent(std::vector<coordinates> &adjacent, coordinates &current) {
  adjacent.clear();

  adjacent.push_back({current.x + 1, current.y, current.z});
  adjacent.push_back({current.x - 1, current.y, current.z});
  adjacent.push_back({current.x, current.y + 1, current.z});
  adjacent.push_back({current.x, current.y - 1, current.z});
  adjacent.push_back({current.x, current.y, current.z + 1});
  adjacent.push_back({current.x, current.y, current.z - 1});
}

bool AvailableSpace(std::vector<std::vector<std::vector<bool>>> &space,
                    coordinates &i,
                    const int max_dimension) {
  if ((i.x >= max_dimension || i.y >= max_dimension || i.z >= max_dimension) ||
      (i.x < 0 || i.y < 0 || i.z < 0)) {
    return false;
  } else {
    return space[i.x][i.y][i.z];
  }
}

int bfs(std::vector<std::vector<std::vector<bool>>> &space,
        coordinates start,
        coordinates finish,
        int energy,
        const int max_dimension) {
  std::vector<std::vector<std::vector<int>>>
      distance(max_dimension,
               std::vector<std::vector<int>>(max_dimension,
                                             std::vector<int>(max_dimension,
                                                              0)));
  std::deque<coordinates> queue;

  space[start.x][start.y][start.z] = false;
  queue.push_back(start);

  coordinates current{};

  const int adjacent_amount = 6;
  std::vector<coordinates> adjacent(adjacent_amount);

  while (!queue.empty()) {
    current = queue.back();
    queue.pop_back();

    if (Finish(current, finish)) {
      return distance[current.x][current.y][current.z];
    }

    GetAdjacent(adjacent, current);

    for (coordinates &i : adjacent) {
      if (AvailableSpace(space, i, max_dimension) && energy - distance[current.x][current.y][current.z] > 0) {
        space[i.x][i.y][i.z] = false;

        distance[i.x][i.y][i.z] = distance[current.x][current.y][current.z] + 1;

        queue.push_front(i);
      }
    }
  }

  return -1;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  const int max_dimension = 101;

  int building_amount, energy;
  std::cin >> building_amount >> energy;

  coordinates start{};
  std::cin >> start.x >> start.y >> start.z;
  coordinates finish{};
  std::cin >> finish.x >> finish.y >> finish.z;

  std::vector<std::vector<std::vector<bool>>>
      space(max_dimension,
            std::vector<std::vector<bool>>(max_dimension,
                                           std::vector<bool>(max_dimension,
                                                             true)));
  MakeBuildings(space, building_amount);

  std::cout << bfs(space, start, finish, energy, max_dimension);

  return 0;
}
