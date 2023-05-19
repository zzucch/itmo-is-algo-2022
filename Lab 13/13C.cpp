#include <iostream>
#include <vector>
#include <memory>

class Set {
 public:
  struct Node {
    int value{};
    bool found{false};
    std::unique_ptr<Node> next{nullptr};
  };

  explicit Set(int n) : n_(n) {
    set_.resize(n);
  }

  int Hash(const int i) const {
    return i % n_;
  }

  void Insert(const int i) {
    int index = Hash(i);

    if (set_[index] == nullptr) {
      set_[index] = std::make_unique<Node>();
      set_[index]->value = i;
    } else {
      Node *placement = set_[index].get();

      while (placement->next != nullptr) {
        placement = placement->next.get();
      }
      placement->next = std::make_unique<Node>();
      placement->next->value = i;
    }
  }

  bool Find(const int i) const {
    Node *placement = set_[Hash(i)].get();
    while (placement != nullptr) {
      if (placement->value == i && !placement->found) {
        placement->found = true;
        return true;
      }
      placement = placement->next.get();
    }
    return false;
  }

  bool operator==(const Set &rhs) const {
    Node *placement;
    for (int i = 0; i < n_; ++i) {
      placement = set_[i].get();
      while (placement != nullptr) {
        if (rhs.Find(placement->value)) {
          placement = placement->next.get();
        } else {
          return false;
        }
      }
    }
    return true;
  }

 private:
  std::vector<std::unique_ptr<Node>> set_;
  int n_{};
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Set set_1(n), set_2(n);

  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    set_1.Insert(tmp);
  }
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    set_2.Insert(tmp);
  }

  if (set_1 == set_2) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}
