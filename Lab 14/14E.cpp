#include <iostream>
#include <string>
#include <regex>

std::regex pattern
    (R"([A-Z][a-z]+\s[A-Z][a-z]+\s[A-Z][a-z]+\s(\d{2})\s(((\+7)|8|7)((\d{10})|(\(\d{3}\)((\d{3}-\d{4})|(-\d{3}(-\d{2}){2})))))\s(g\.[A-Z]{3}\,\sul\.[A-Z][a-z]+\,\sd\.\d{2,}))");
  
bool Check(const std::string &data) {
  return regex_match(data, pattern);
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);

  int m;
  std::cin >> m;

  std::string data;
  std::cin.ignore();
  for (int i = 0; i < m; i++) {
    getline(std::cin, data);

    if (Check(data)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
  return 0;
}
