// dp with bitmasks (enumerating 3^n submasks)
// https://atcoder.jp/contests/dp/tasks/dp_u

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

const int MAXN = 16;
int a[MAXN + 5][MAXN + 5];
ll v[1 << MAXN];
ll dp[1 << MAXN];

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  rep(i, 0, n) rep(j, 0, n)
    cin >> a[i][j];
  rep(bm, 0, 1 << n) {
    rep(i, 0, n) {
      rep(j, 0, n) {
        if ((1 << i) & bm and (1 << j) & bm)
          v[bm] += a[i][j];
      }
    }
    v[bm] /= 2;
  }
  rep(bm, 0, 1 << n) {
    dp[bm] = v[bm];
    for (int sm = bm; sm; sm = (sm - 1) & bm)
      dp[bm] = max(dp[bm], dp[bm - sm] + v[sm]);
  }
  cout << dp[(1 << n) - 1] << '\n';
}
