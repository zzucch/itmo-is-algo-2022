#include <iostream>
#include <vector>

const int kAmountOfStudents = 3;
const int kMaxGrade = 3;
const int kLowerGrade = 1;
const int kLowestGrade = 0;

class BanMachine {
 public:
  struct Node {
    std::string value;
    std::vector<bool> used{std::vector<bool>(kAmountOfStudents, false)};
  };

  explicit BanMachine(size_t n) : n_(n) {
    set_.resize(n);
    results_.resize(kAmountOfStudents);
  }

  void Insert(const std::string &value, int number) {
    size_t index_1, index_2;
    index_1 = Hash1(value);
    index_2 = Hash2(value);
    if (set_[index_1] && set_[index_1]->value == value) {
      set_[index_1]->used[number] = true;
    } else if (set_[index_2] && set_[index_2]->value == value) {
      set_[index_2]->used[number] = true;
    } else {
      std::string tmp = value;
      int depth = 0;
      while (true) {
        index_1 = Hash1(tmp);
        index_2 = Hash2(tmp);
        if (!set_[index_1]) {
          set_[index_1] = new Node;
          set_[index_1]->value = tmp;
          set_[index_1]->used[number] = true;
          return;
        } else if (!set_[index_2]) {
          set_[index_2] = new Node;
          set_[index_2]->value = tmp;
          set_[index_2]->used[number] = true;
          return;
        } else {
          tmp = set_[index_1]->value;
          set_[index_1]->value = value;
          ++depth;
          if (depth > n_) {
            Rehash();
          }
        }
      }
    }
  }

  void Rehash() {
    n_ *= 13;
    std::vector<Node *> rehashed_set(n_);
    size_t index_1, index_2;
    for (Node *i : set_) {
      if (i) {
        index_1 = Hash1(i->value);
        index_2 = Hash2(i->value);
        if (rehashed_set[index_1] == nullptr) {
          rehashed_set[index_1] = i;
        } else if (rehashed_set[index_2] == nullptr) {
          rehashed_set[index_2] = i;
        } else {
          Rehash();
          return;
        }
      }
    }
    set_ = rehashed_set;
  }

  void PrintResults() {
    for (Node *i : set_) {
      if (i) {
        // i mean... yeah..
        if (i->used[0] && i->used[1] && i->used[2]) {
          results_[0] += kLowestGrade;
          results_[1] += kLowestGrade;
          results_[2] += kLowestGrade;
        } else if (i->used[0] && i->used[1]) {
          results_[0] += kLowerGrade;
          results_[1] += kLowerGrade;
        } else if (i->used[0] && i->used[2]) {
          results_[0] += kLowerGrade;
          results_[2] += kLowerGrade;
        } else if (i->used[1] && i->used[2]) {
          results_[1] += kLowerGrade;
          results_[2] += kLowerGrade;
        } else if (i->used[0]) {
          results_[0] += kMaxGrade;
        } else if (i->used[1]) {
          results_[1] += kMaxGrade;
        } else if (i->used[2]) {
          results_[2] += kMaxGrade;
        }
      }
    }
    for (size_t i : results_) {
      std::cout << i << ' ';
    }
  }

 private:
  std::vector<Node *> set_;
  std::vector<size_t> results_;
  size_t n_;

  size_t Hash1(const std::string &value) const {
    size_t hash = 0;
    for (char c : value) {
      hash = (2147 * hash + c) % 2147483647;
    }
    return hash % n_;
  }

  size_t Hash2(const std::string &value) const {
    size_t hash = 0;
    for (char c : value) {
      hash = (2147 * hash + c) % 2147483647;
    }
    return (hash % (n_ - 1)) + 1;
  }
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  size_t n;
  std::cin >> n;

  const size_t kSize = 2000000;
  BanMachine ban_machine(kSize);

  std::string value;
  for (int friend_num = 0; friend_num < kAmountOfStudents; ++friend_num) {
    for (int j = 0; j < n; ++j) {
      std::cin >> value;
      ban_machine.Insert(value, friend_num);
    }
  }
  ban_machine.PrintResults();

  return 0;
}
