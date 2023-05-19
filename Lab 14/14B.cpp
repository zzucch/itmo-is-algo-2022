#include <iostream>
#include <vector>
#include <string>

void Solve(const std::string &string) {
  std::vector<int> prefixes(string.length(), 0);

  int count;
  for (int i = 1; i < string.length(); i++) {
    count = prefixes[i - 1];
    while (count > 0 && string[i] != string[count]) {
      count = prefixes[count - 1];
    }
    if (string[i] == string[count]) {
      ++count;
    }
    prefixes[i] = count;
  }

  for (int i : prefixes) {
    std::cout << i << " ";
  }
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  
  std::string string;
  std::cin >> string;
  Solve(string);
  return 0;
}
