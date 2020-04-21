// dp/combo, number of down/right paths from corner to corner with obstacles
// https://atcoder.jp/contests/dp/tasks/dp_h

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const int MOD = 1000000007;
const int MAXN = 1000;
char grid[MAXN + 5][MAXN + 5];
int dp[MAXN + 5][MAXN + 5];

auto add(auto& a, auto b){a = ((ll) a + b) % MOD;}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int r, c;
  cin >> r >> c;
  rep(i, 0, r) rep(j, 0, c)
    cin >> grid[i][j];
  memset(dp, 0, sizeof(dp));
  dp[0][0] = 1;
  rep(i, 0, r) {
    rep(j, 0, c) {
      if (i == 0 and j == 0) continue;
      if (i - 1 >= 0 and grid[i - 1][j] != '#')
        add(dp[i][j], dp[i - 1][j]);
      if (j - 1 >= 0 and grid[i][j - 1] != '#')
        add(dp[i][j], dp[i][j - 1]);
    }
  }
  cout << dp[r - 1][c - 1] << '\n';
}
