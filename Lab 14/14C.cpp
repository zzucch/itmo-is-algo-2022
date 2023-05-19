#include <iostream>
#include <string>

std::string MySubstr(const std::string &str, const int start, const int length) {
  std::string result;
  for (int i = start; i < start + length && i < str.size(); i++) {
    result += str[i];
  }
  return result;
}

int main() {
  int n, m;

  std::string string;
  std::cin >> n >> m >> string;

  int answer = 0;

  int first, second, length;
  for (int i = 0; i < m; i++) {
    std::cin >> first >> second >> length;
    if (MySubstr(string, first - 1, length)
        == MySubstr(string, second - 1, length)) {
      answer++;
    }
  }
  std::cout << answer;

  return 0;
}
