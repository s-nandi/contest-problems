// dp with probability
// https://atcoder.jp/contests/dp/tasks/dp_i

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<ld> p(n);
  trav(i, p) cin >> i;
  vector<vector<ld>> dp(n + 1, vector<ld>(n + 1));
  dp[0][0] = 1;
  rep(i, 0, n) {
    rep(j, 0, n) {
      dp[i + 1][j + 1] += p[i] * dp[i][j];
      dp[i + 1][j] += (1 - p[i]) * dp[i][j];
    }
  }
  auto res = 0.L;
  auto lb = (n + 1) / 2;
  rep(i, lb, n + 1)
    res += dp[n][i];
  cout << fixed << setprecision(11) << res << '\n';
}
