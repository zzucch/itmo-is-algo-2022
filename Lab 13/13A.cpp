#include <iostream>
#include <vector>

class Set {
 public:
  struct Node {
    int value{};
    bool used{false};
  };

  explicit Set(int size) : n_(size) {
    set_.resize(size);
  }

  int Hash(const int i) const {
    return i % n_;
  }

  void Insert(const int value) {
    int index = Hash(value);
    while (set_[index].used && set_[index].value != value) {
      index = (index + 1) % n_;
    }
    if (set_[index].value != value) {
      set_[index].value = value;
      set_[index].used = true;
    }
  }

  bool Find(const int value) {
    int index = Hash(value);
    while (set_[index].used && set_[index].value != value) {
      index = (index + 1) % n_;
    }
    return set_[index].value == value;
  }

 private:
  std::vector<Node> set_;
  int n_{};
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  const int kSize = 500000;

  Set set_x(kSize);
  Set set_y(kSize);

  int x, y;
  int count = 0;
  for (int i = 0; i < n; ++i) {
    std::cin >> x >> y;
    if (!(set_x.Find(x) || set_y.Find(y))) {
      set_x.Insert(x);
      set_y.Insert(y);
      ++count;
    }
  }

  if (count <= 3) {
    std::cout << "YES";
  } else {
    std::cout << "NO";
  }

  return 0;
}
