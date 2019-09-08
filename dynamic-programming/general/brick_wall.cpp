// dp (state reduction), using count of elements used as state
// https://open.kattis.com/problems/brickwall
// 2014 Northeast North America Regional

#include <bits/stdc++.h>
using namespace std;

constexpr auto MAXC = 300;
bool dp[MAXC + 5][MAXC + 5][MAXC + 5];

int main() {
  int n, c1, c2, c3;
  cin >> n >> c1 >> c2 >> c3;

  auto row = vector<int>(n);
  for (auto &brick : row) {
    cin >> brick;
  }

  partial_sum(begin(row), end(row), begin(row));
  auto total_length = row.back();

  memset(dp, 0, sizeof dp);
  auto sol = vector<int>(total_length + 1);
  dp[0][0][0] = true;
  for (int n1 = 0; n1 <= c1; n1++) {
    for (int n2 = 0; n2 <= c2; n2++) {
      for (int n3 = 0; n3 <= c3; n3++) {
        int len = n1 + 2 * n2 + 3 * n3;
        if (binary_search(begin(row), end(row) - 1, len)) {
          dp[n1][n2][n3] = false;
        }
        if (len <= total_length) {
          sol[len] |= dp[n1][n2][n3];
        }
        for (int p = 1; p <= 3; p++) {
          auto nn1 = n1 + (p == 1);
          auto nn2 = n2 + (p == 2);
          auto nn3 = n3 + (p == 3);
          dp[nn1][nn2][nn3] |= dp[n1][n2][n3];
        }
      }
    }
  }
  if (sol[total_length])
    cout << "YES" << '\n';
  else
    cout << "NO" << '\n';
}
