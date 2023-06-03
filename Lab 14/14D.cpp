#include <iostream>
#include <vector>

struct Node {
  std::string value{};
  int amount_left{0};
  int amount_right{0};
  Node *left{nullptr};
  Node *right{nullptr};
  int height{1};
};

int BalanceFactor(Node *root) {
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

void FixHeight(Node *&root) {
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

Node *RotateLeft(Node *a) {
  Node *b = a->right;

  a->amount_right = b->amount_left;
  b->amount_left = a->amount_right + a->amount_left + 1;

  a->right = b->left;
  b->left = a;

  FixHeight(a);
  FixHeight(b);

  return b;
}

Node *RotateRight(Node *a) {
  Node *b = a->left;

  a->amount_left = b->amount_right;
  b->amount_right = a->amount_right + a->amount_left + 1;

  a->left = b->right;
  b->right = a;

  FixHeight(a);
  FixHeight(b);

  return b;
}

Node *Balance(Node *root) {
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

Node *Add(Node *root, const std::string &value) {
  if (!root) {
    root = new Node;
    root->value = value;
    return root;
  }
  if (value < root->value) {
    root->left = Add(root->left, value);
    ++root->amount_left;
  } else {
    root->right = Add(root->right, value);
    ++root->amount_right;
  }
  return Balance(root);
}

void FindInOrder(Node *root, int number) {
  Node *tmp = root;
  int current_number;
  while (tmp) {
    current_number = tmp->amount_left + 1;
    if (current_number == number) {
      std::cout << tmp->value << '\n';
      return;
    } else if (current_number > number) {
      tmp = tmp->left;
    } else {
      tmp = tmp->right;
      number -= current_number;
    }
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n;
  std::cin >> n;

  Node *root = nullptr;

  std::string input;
  for (int i = 0; i < n; ++i) {
    std::cin >> input;
    if (std::isdigit(*input.begin())) {
      FindInOrder(root, std::stoi(input));
    } else {
      root = Add(root, input);
    }
  }

  return 0;
}
