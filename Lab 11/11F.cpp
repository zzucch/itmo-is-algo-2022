#include <iostream>
#include <vector>
#include <unordered_map>

struct edge {
  int a{};
  int b{};

  bool operator==(const edge &other) const {
    return a == other.a && b == other.b;
  }
};

template<>
struct std::hash<edge> {
  size_t operator()(const edge &e) const {
    return hash<int>()(e.a * e.b) ^ hash<int>()(e.b);
  }
};

struct request {
  bool edge_deletion;
  int a;
  int b;
};

int FindSet(std::vector<int> &parents, int v) {
  if (parents[v] == -1) {
    return v;
  }
  return parents[v] = FindSet(parents, parents[v]);
}

void UnionSets(std::vector<int> &parents,
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
  }
}

void AreFriends(std::vector<int> &parents,
                int a,
                int b,
                std::vector<bool> &r_answer) {
  if (FindSet(parents, a) == FindSet(parents, b)) {
    r_answer.push_back(true);
  } else {
    r_answer.push_back(false);
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m, requests_amount;
  std::cin >> n >> m >> requests_amount;

  std::vector<int> parents(n, -1);
  std::vector<int> rank(n, 0);

  std::vector<edge> initial_edges;
  initial_edges.reserve(m);

  std::unordered_map<edge, bool> available;


  int a, b;
  for (int i = 0; i < m; ++i) {
    std::cin >> a >> b;
    --a, --b;

    initial_edges.push_back({a, b});
    available[{a, b}] = true;
    available[{b, a}] = true;
  }

  std::vector<request> requests;
  requests.reserve(requests_amount);

  char operation;
  for (int i = 0; i < requests_amount; ++i) {
    std::cin >> operation >> a >> b;
    --a, --b;

    requests.push_back({operation == '-', a, b});
  }

  for (request i : requests) {
    if (i.edge_deletion) {
      available[{i.a, i.b}] = false;
      available[{i.b, i.a}] = false;
    }
  }

  for (edge i : initial_edges) {
    if (available[i]) {
      UnionSets(parents, rank, i.a, i.b);
    }
  }

  std::vector<bool> r_answer;
  r_answer.reserve(requests_amount);

  for (auto r_it = requests.rbegin(); r_it != requests.rend(); ++r_it) {
    if (r_it->edge_deletion) {
      UnionSets(parents, rank, r_it->a, r_it->b);
    } else {
      AreFriends(parents, r_it->a, r_it->b, r_answer);
    }
  }

  for (auto r_it = r_answer.rbegin(); r_it != r_answer.rend(); ++r_it) {
    std::cout << (*r_it ? "YES\n" : "NO\n");
  }

  return 0;
}
