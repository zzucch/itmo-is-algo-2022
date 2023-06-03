#include <iostream>
#include <string>
#include <vector>

bool MySubstr(const std::string &t,
                     const std::string &x,
                     const int start,
                     const int length) {
  std::string result;
  for (int i = start; i < start + length && i < t.size(); i++) {
    if (t[i] != x[i - start]) {
      return false;
    }
  }
  return true;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  std::string t, x;
  std::cin >> t >> x;

  std::vector<int> indexes;
  int count = 0;
  for (int i = 0; i <= t.size() - x.size(); i++) {
    if (MySubstr(t, x, i, x.size())) {
      indexes.push_back(i);
      ++count;
    }
  }

  std::cout << count << '\n';
  for (int i : indexes) {
    std::cout << i << " ";
  }

  return 0;
}
