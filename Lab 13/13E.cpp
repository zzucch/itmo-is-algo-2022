#include <iostream>
#include <vector>
#include <memory>

class Set {
 public:
  struct Node {
    int value{};
    int count{0};
    std::unique_ptr<Node> next{nullptr};
  };

  explicit Set(int n) : n_(n) {
    set_.resize(n);
  }

  int Hash(int key) const {
    return (key % n_ + n_) % n_;
  }

  void IncrementCount(const int value) {
    int index = Hash(value);

    if (set_[index] == nullptr) {
      set_[index] = std::make_unique<Node>();
      set_[index]->value = value;
    } else {
      Node *placement = set_[index].get();

      while (true) {
        if (placement->value == value) {
          ++placement->count;
          count_ += placement->count;
          return;
        }
        if (placement->next == nullptr) {
          placement->next = std::make_unique<Node>();
          placement->next->value = value;
          return;
        }
        placement = placement->next.get();
      }
    }
  }

  int GetCount() const {
    return count_;
  }

 private:
  std::vector<std::unique_ptr<Node>> set_;
  int n_{};
  int count_{0};
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Set frequency(n);

  int tmp;
  for (int i = 0; i < n; ++i) {
    std::cin >> tmp;
    frequency.IncrementCount(tmp - i);
  }

  std::cout << frequency.GetCount();

  return 0;
}
