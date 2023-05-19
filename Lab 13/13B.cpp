#include <iostream>
#include <memory>
#include <vector>

class Set {
 public:
  struct Node {
    size_t value{};
    int max_letter{};
    int min_letter{};
    int length{};
    bool found{false};
    std::unique_ptr<Node> next{nullptr};
  };

  explicit Set(int n) : n_(n) {
    set_.resize(n);
  }

  size_t Hash(const size_t i) const {
    return i % n_;
  }

  void Insert(const size_t value,
              const int max_letter,
              const int min_letter,
              const int length) {
    size_t index = Hash(value);
    if (set_[index] == nullptr) {
      set_[index] = std::make_unique<Node>();
      set_[index]->value = value;
      set_[index]->max_letter = max_letter;
      set_[index]->min_letter = min_letter;
      set_[index]->length = length;
    } else {
      Node *placement = set_[index].get();
      while (placement->next != nullptr) {
        placement = placement->next.get();
      }
      placement->next = std::make_unique<Node>();
      placement->next->value = value;
      placement->next->max_letter = max_letter;
      placement->next->min_letter = min_letter;
      placement->next->length = length;
    }
  }

  bool Find(const size_t value,
            const int max_letter,
            const int min_letter,
            const int length) const {
    Node *placement = set_[Hash(value)].get();
    while (placement != nullptr) {
      if (placement->value == value && placement->length == length
          && placement->max_letter == max_letter
          && placement->min_letter == min_letter
          && !placement->found) {
        placement->found = true;
        return true;
      }
      placement = placement->next.get();
    }
    return false;
  }

 private:
  std::vector<std::unique_ptr<Node>> set_;
  size_t n_{};
};

size_t Hash64(size_t hash) {
  hash = (hash ^ (hash >> 30)) * UINT64_C(0xbf58476d1ce4e5b9);
  hash = (hash ^ (hash >> 27)) * UINT64_C(0x94d049bb133111eb);
  hash = hash ^ (hash >> 31);
  return hash;
}

size_t GetValue(size_t hash_1,
                size_t hash_2,
                size_t hash_3,
                size_t max_letter,
                size_t min_letter) {
  return hash_1 ^ hash_2 ^ hash_3 >> min_letter ^ max_letter;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n;
  std::vector<int> first_word(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> first_word[i];
  }

  std::cin >> m;
  std::vector<int> second_word(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> second_word[i];
  }

  const size_t kSize = 9000000;
  const size_t kHash1 = 7;
  const size_t kHash2 = 3;
  const size_t kHash3 = 13;
  const int kMaxLetter = 100001;
  const int kMinLetter = -1;

  Set set(kSize);
  int max_length = 0;
  size_t value, hash_1, hash_2, hash_3, tmp;

  int max_letter, min_letter;
  for (int start = 0; start < n; ++start) {
    hash_1 = kHash1;
    hash_2 = kHash2;
    hash_3 = kHash3;
    max_letter = kMinLetter;
    min_letter = kMaxLetter;
    for (int end = start; end < n; ++end) {
      max_letter = std::max(max_letter, first_word[end]);
      min_letter = std::min(min_letter, first_word[end]);
      tmp = Hash64(first_word[end]);
      hash_1 ^= tmp;
      hash_2 *= tmp;
      hash_3 += tmp;
      value = GetValue(hash_1, hash_2, hash_3, max_letter, min_letter);
      set.Insert(value,
                 max_letter,
                 min_letter,
                 end - start + 1);
    }
  }
  // i was lazy so yeah
  for (int start = 0; start < m; ++start) {
    hash_1 = kHash1;
    hash_2 = kHash2;
    hash_3 = kHash3;
    max_letter = kMinLetter;
    min_letter = kMaxLetter;
    for (int end = start; end < m; ++end) {
      max_letter = std::max(max_letter, second_word[end]);
      min_letter = std::min(min_letter, second_word[end]);
      tmp = Hash64(second_word[end]);
      hash_1 ^= tmp;
      hash_2 *= tmp;
      hash_3 += tmp;
      value = GetValue(hash_1, hash_2, hash_3, max_letter, min_letter);
      if (set.Find(value,
                   max_letter,
                   min_letter,
                   end - start + 1)) {
        max_length = std::max(max_length, end - start + 1);
      }
    }
  }
  std::cout << max_length;

  return 0;
}
