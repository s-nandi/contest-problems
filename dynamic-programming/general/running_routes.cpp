// dp (min-cost triangulation style), dp on a circle (duplicate trick)
// https://open.kattis.com/problems/runningroutes
// 2019 North American Qualifier

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(int i = a; i < (b); ++i)

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    auto mat = vector(2 * n, vi(2 * n));
    rep(i, 0, n) {
      rep(j, 0, n) {
        cin >> mat[i][j];
        mat[i + n][j] = mat[i][j + n] = mat[i + n][j + n] = mat[i][j];
      }
    }

    auto dp = vector(n + 1, vi(2 * n));
    rep(i, 0, 2 * n - 1)
      dp[2][i] = mat[i][i + 1];

    rep(len, 3, n + 1) {
      rep(i, 0, 2 * n - len + 1) {
        int j = i + len - 1;
        dp[len][i] = dp[len - 1][i + 1];
        for (int k = i + 1; k <= j; k++) {
          auto possible = mat[i][k];
          auto pref_len = k - i + 1;
          auto suff_len = j - k + 1;
          if (pref_len >= 4) {
            possible += dp[pref_len - 2][i + 1];
          }
          if (suff_len >= 3) {
            possible += dp[suff_len - 1][k + 1];
          }
          dp[len][i] = max(dp[len][i], possible);
        }
      }
    }
    cout << dp[n][0] << '\n';
}
