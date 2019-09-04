// ad-hoc
// https://open.kattis.com/problems/apples
// 2016 Mid-Central Regional

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

vector<char> fixed(const vector<char> &col) {
  auto res = col;
  int lowest_free = res.size() - 1;
  for (int pos = res.size() - 1; pos >= 0; pos--) {
    char c = res[pos];
    if (c == 'a') {
      swap(res[lowest_free], res[pos]);
      lowest_free = lowest_free - 1;
    } else if (c == '#') {
      lowest_free = pos - 1;
    }
  }
  return res;
}

int main() {
  int r, c;
  cin >> r >> c;

  vector<vector<char>> grid(r, vector<char>(c));
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cin >> grid[i][j];
    }
  }

  for (int j = 0; j < c; j++) {
    vector<char> col(r);
    for (int i = 0; i < r; i++) {
      col[i] = grid[i][j];
    }
    auto new_col = fixed(col);
    for (int i = 0; i < r; i++) {
      grid[i][j] = new_col[i];
    }
  }

  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      cout << grid[i][j];
    }
    cout << '\n';
  }
}
