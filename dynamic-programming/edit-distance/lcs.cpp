// LCS (reconstruction)
// https://atcoder.jp/contests/dp/tasks/dp_f

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()

const int MAXN = 3000;
int dp[MAXN + 5][MAXN + 5];
int best[MAXN + 5][MAXN + 5];

bool maxx(auto& a, auto b) {
  if (a > b) return false;
  else {a = b; return true;}
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  string s, t;
  cin >> s >> t;
  int n = sz(s), m = sz(t);

  memset(dp, -1, sizeof(dp));
  rep(i, 0, n + 1)
    dp[i][0] = 0;
  rep(i, 0, m + 1)
    dp[0][i] = 0;
  rep(i, 1, n + 1) {
    rep(j, 1, m + 1) {
      if (maxx(dp[i][j], dp[i - 1][j]))
        best[i][j] = 0; // ignore i-th letter from s
      if (maxx(dp[i][j], dp[i][j - 1]))
        best[i][j] = 1; // ignore j-th letter from t
      if (s[i - 1] == t[j - 1] and maxx(dp[i][j], dp[i - 1][j - 1] + 1))
        best[i][j] = 2; // use i-th and j-th letter from s, t respectively
    }
  }

  string res;
  int ci = n, cj = m;
  while (ci != 0 and cj != 0) {
    if (best[ci][cj] == 2) {
      res += s[ci - 1];
      --ci; --cj;
    } else if (best[ci][cj] == 1) {
      --cj;
    } else {
      assert(best[ci][cj] == 0);
      --ci;
    }
  }
  reverse(all(res));
  cout << res << '\n';
}
