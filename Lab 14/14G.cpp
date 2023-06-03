#include <iostream>
#include <vector>

void Precalculate(std::vector<std::vector<int>> &matrix,
                  std::vector<std::vector<size_t>> &hash,
                  std::vector<size_t> &pow,
                  int n,
                  int m) {
  for (int i = 0; i < n; ++i) {
    hash[i][0] = matrix[i][0] * pow[0];
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 1; j < m; ++j) {
      hash[i][j] = hash[i][j - 1] + matrix[i][j] * pow[j];
    }
  }
}

size_t GetHash(std::vector<std::vector<size_t>> &hash,
               int x,
               int y_1,
               int y_2) {
  size_t result = hash[x][y_2];
  if (y_1 > 0) {
    result -= hash[x][y_1 - 1];
  }
  return result;
}

bool Check(std::vector<std::vector<size_t>> &hash,
           std::vector<size_t> &pow,
           int ax_1,
           int ax_2,
           int ay_1,
           int ay_2,
           int bx_1,
           int bx_2,
           int by_1,
           int by_2,
           int m) {
  size_t hash_1, hash_2;
  if (ay_2 - ay_1 != by_2 - by_1 || ax_2 - ax_1 != bx_2 - bx_1) {
    return false;
  }
  int delta = bx_1 - ax_1;
  for (int i = ax_1; i <= ax_2; ++i) {
    hash_1 = GetHash(hash, i, ay_1, ay_2);
    hash_2 = GetHash(hash, i + delta, by_1, by_2);
    hash_1 *= pow[m - ay_1];
    hash_2 *= pow[m - by_1];
    if (hash_1 != hash_2) {
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
  std::vector<std::vector<int>> matrix(n, std::vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      std::cin >> matrix[i][j];
    }
  }

  size_t p = 3;
  int pow_size = m + 1;
  std::vector<size_t> pow(pow_size);
  pow[0] = 1;
  for (int i = 1; i < pow_size; ++i) {
    pow[i] = pow[i - 1] * p;
  }

  std::vector<std::vector<size_t>> hash(n, std::vector<size_t>(m));
  Precalculate(matrix, hash, pow, n, m);

  int q;
  std::cin >> q;
  int ax_1, ax_2, ay_1, ay_2, bx_1, bx_2, by_1, by_2;
  while (q--) {
    std::cin >> ax_1 >> ay_1 >> ax_2 >> ay_2 >> bx_1 >> by_1 >> bx_2 >> by_2;
    --ax_1, --ay_1, --ax_2, --ay_2, --bx_1, --by_1, --bx_2, --by_2;

    if (Check(hash, pow, ax_1, ax_2, ay_1, ay_2, bx_1, bx_2, by_1, by_2, m)) {
      std::cout << "YES\n";
    } else {
      std::cout << "NO\n";
    }
  }
  return 0;
}
