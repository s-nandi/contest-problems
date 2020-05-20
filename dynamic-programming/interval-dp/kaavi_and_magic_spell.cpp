// interval dp, precomputing boundaries is useful (dp[len][m]), pattern matching
// https://codeforces.com/contest/1337/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define sz(x) (int)(x).size()

const int MOD = 998244353;
const int MAXN = 3000;
int dp[MAXN + 5][MAXN + 5]; // len, start
int pow2[MAXN + 5];

void self_add(auto& a, auto b){a = ((ll) a + b) % MOD;}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  pow2[0] = 1;
  rep(i, 1, MAXN + 1)
    pow2[i] = 2 * pow2[i - 1] % MOD;

  string s, t;
  cin >> s >> t;
  int n = sz(s);
  int m = sz(t);

  rep(i, 0, m + 1) dp[0][i] = 1;
  rep(len, 0, n + 1) dp[len][m] = pow2[len];
  rep(len, 1, n + 1) {
    auto c = s[len - 1];
    rep(i, 0, m) {
      auto j = i + len - 1;
      if (t[i] == c)
        self_add(dp[len][i], dp[len - 1][i + 1]);
      if (j >= m or t[j] == c)
        self_add(dp[len][i], dp[len - 1][i]);
    }
  }
  int res = 0;
  rep(len, m, n + 1)
    self_add(res, dp[len][0]);
  cout << res << '\n';
}
