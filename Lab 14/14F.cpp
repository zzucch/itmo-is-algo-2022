#include <iostream>
#include <vector>

bool Check(const std::vector<int> &cards, int i) {
  int index_1 = i - 1;
  int index_2 = i;
  while (index_1 >= 0 && index_2 < cards.size()) {
    if (cards[index_1--] != cards[index_2++]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int n, m;
  std::cin >> n >> m;
  std::vector<int> cards(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> cards[i];
  }

  std::vector<int> answer;
  answer.reserve(n / 2);
  for (int i = 0; i <= n / 2; ++i) {
    if (Check(cards, i)) {
      answer.push_back(n - i);
    }
  }
  for (std::reverse_iterator
           r_it = answer.rbegin(); r_it != answer.rend(); ++r_it) {
    std::cout << *r_it << ' ';
  }
  return 0;
}
