#include <iostream>
#include <vector>
#include <memory>

class Isu {
 public:
  explicit Isu(int m, int q) : n_(m), q_(q) {
    set_.resize(m);
    student_scores_.resize(q);
  }

  int Average(const int group) {
    int index = HashGroup(group);
    Group *placement = set_[index].get();

    if (placement == nullptr) {
      return 0;
    }

    while (true) {
      if (placement->group == group) {
        break;
      }
      placement = placement->next.get();
    }
    if (placement->student_amount != 0) {
      return placement->group_score / placement->student_amount;
    } else {
      return 0;
    }
  };

  void DeleteStudent(const int group, const int isu_id) {
    int index = HashGroup(group);
    Group *placement = set_[index].get();

    if (placement == nullptr) {
      return;
    }
    while (true) {
      if (placement->group == group) {
        break;
      }
      placement = placement->next.get();
    }

    int score_to_delete = FindScore(group, isu_id);
    if (score_to_delete == -1) {
      return;
    }
    Student *node_to_delete =
        Search(placement->root, score_to_delete);
    if (!node_to_delete) {
      return;
    }
    int deleted_score = node_to_delete->score;

    placement->root = DeleteNode(placement->root, node_to_delete->score);

    placement->group_score -= deleted_score;
    --placement->student_amount;
  }

  void AddStudent(const int group, const int isu_id, const int score) {
    int index = HashGroup(group);

    if (set_[index] == nullptr) {
      set_[index] = std::make_unique<Group>();
      set_[index]->group = group;
      set_[index]->root = Add(set_[index]->root, isu_id, score);
      set_[index]->group_score += score;
      ++set_[index]->student_amount;
    } else {
      Group *placement = set_[index].get();
      while (placement->next != nullptr) {
        if (placement->group == group) {
          break;
        }
        placement = placement->next.get();
      }
      if (placement->next == nullptr && placement->group != group) {
        placement->next = std::make_unique<Group>();
        placement = placement->next.get();
      }
      placement->group = group;
      placement->root = Add(placement->root, isu_id, score);
      placement->group_score += score;
      ++placement->student_amount;
    }

    InsertScore(group, isu_id, score);
  }

  int MaxScore(const int group) {
    int index = HashGroup(group);
    Group *placement = set_[index].get();

    if (placement == nullptr) {
      return 0;
    }

    while (true) {
      if (placement->group == group) {
        break;
      }
      placement = placement->next.get();
    }

    if (placement->root) {
      return FindMaxScore(placement->root)->score;
    } else {
      return 0;
    }
  }

 private:
  struct Student {
    int score{};
    Student *left = nullptr;
    Student *right = nullptr;

    int height = 1;
  };

  struct Group {
    int group{};
    int group_score{0};
    int student_amount{0};
    Student *root{nullptr};
    std::unique_ptr<Group> next{nullptr};
  };

  struct ScoreNode {
    int deleted{false};
    int group{};
    int isu_id{};
    int score{};
    std::unique_ptr<ScoreNode> next{nullptr};
  };

  void InsertScore(const int group, const int isu_id, const int score) {
    int index = HashIsuId(group, isu_id);

    if (student_scores_[index] == nullptr) {
      student_scores_[index] = std::make_unique<ScoreNode>();
      student_scores_[index]->group = group;
      student_scores_[index]->isu_id = isu_id;
      student_scores_[index]->score = score;
    } else {
      ScoreNode *placement = student_scores_[index].get();

      while (placement->next != nullptr) {
        placement = placement->next.get();
      }
      placement->next = std::make_unique<ScoreNode>();
      placement->next->group = group;
      placement->next->isu_id = isu_id;
      placement->next->score = score;
    }
  }

  int FindScore(const int group, const int isu_id) {
    ScoreNode *placement = student_scores_[HashIsuId(group, isu_id)].get();
    while (placement != nullptr) {
      if (placement->isu_id == isu_id
          && placement->group == group
          && !placement->deleted) {
        placement->deleted = true;
        return placement->score;
      }
      placement = placement->next.get();
    }
    return -1;
  }

  int HashGroup(const int group) const {
    int hash = (2147 * 13 + group * 3) % 2147483647;
    return hash % n_;
  }

  int HashIsuId(const int group, const int isu_id) const {
    return (isu_id + group * 13) % q_;
  }

  static int BalanceFactor(Student *root) {
    int h_r = 0;
    int h_l = 0;

    if (root->right) {
      h_r = root->right->height;
    }
    if (root->left) {
      h_l = root->left->height;
    }
    return h_r - h_l;
  }

  static void FixHeight(Student *&root) {
    int h_r = 0;
    int h_l = 0;

    if (root->right) {
      h_r = root->right->height;
    }
    if (root->left) {
      h_l = root->left->height;
    }

    root->height = std::max(h_r, h_l) + 1;
  }

  static Student *RotateLeft(Student *a) {
    Student *b = a->right;

    a->right = b->left;
    b->left = a;

    FixHeight(a);
    FixHeight(b);

    return b;
  }

  static Student *RotateRight(Student *a) {
    Student *b = a->left;

    a->left = b->right;
    b->right = a;

    FixHeight(a);
    FixHeight(b);

    return b;
  }

  static Student *Balance(Student *root) {
    FixHeight(root);

    int balance_factor = BalanceFactor(root);

    if (balance_factor == 2) {
      if (BalanceFactor(root->right) < 0) {
        root->right = RotateRight(root->right);
      }
      return RotateLeft(root);
    }
    if (balance_factor == -2) {
      if (BalanceFactor(root->left) > 0) {
        root->left = RotateLeft(root->left);
      }
      return RotateRight(root);
    }

    return root;
  }

  Student *Add(Student *root, const int isu_id, const int score) {
    if (!root) {
      root = new Student;
      root->score = score;

      return root;
    }

    if (score < root->score) {
      root->left = Add(root->left, isu_id, score);
    } else {
      root->right = Add(root->right, isu_id, score);
    }

    return Balance(root);
  }

  static Student *FindMaxScore(Student *root) { // & ruins
    while (root->right) {
      root = root->right;
    }
    return root;
  }

  Student *RemoveMax(Student *root) {
    if (!root->right) {
      return root->left;
    }
    root->right = RemoveMax(root->right);

    return Balance(root);
  }

  Student *DeleteNode(Student *root, const int x) {
    if (!root) {
      return root;
    }

    if (x < root->score) {
      root->left = DeleteNode(root->left, x);
    } else if (x > root->score) {
      root->right = DeleteNode(root->right, x);
    } else {
      Student *l = root->left;
      Student *r = root->right;

      delete root;

      if (l == nullptr) {
        return r;
      }

      Student *new_root = FindMaxScore(l);
      new_root->left = RemoveMax(l);
      new_root->right = r;

      return Balance(new_root);
    }

    return Balance(root);
  }

  Student *Search(Student *root, const int x) {
    if (!root || root->score == x) {
      return root;
    }
    if (root->score > x) {
      return Search(root->left, x);
    } else {
      return Search(root->right, x);
    }
  }

  std::vector<std::unique_ptr<Group>> set_;
  std::vector<std::unique_ptr<ScoreNode>> student_scores_;
  int n_;
  int q_;
};

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m, q;
  std::cin >> m >> q;

  Isu isu(m + 1, q + 1);

  char query;
  int group, isu_id, score;
  for (int i = 0; i < q; ++i) {
    std::cin >> query >> group;
    switch (query) {
      case 'a':
        std::cout << isu.Average(group) << '\n';
        break;
      case '-':
        std::cin >> isu_id;
        isu.DeleteStudent(group, isu_id);
        break;
      case '+':
        std::cin >> isu_id >> score;
        isu.AddStudent(group, isu_id, score);
        break;
      case 'm':
        std::cout << isu.MaxScore(group) << '\n';
        break;
      default:
        break;
    }
  }

  return 0;
}
