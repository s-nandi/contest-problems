// dp with probability, binomial EV (repeated failure)
// https://atcoder.jp/contests/dp/tasks/dp_j

#include <bits/stdc++.h>
using namespace std;

using ld = long double;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

int n;
const int MAXN = 300;
ld dp[MAXN + 5][MAXN + 5][MAXN + 5];

ld get(int i, int j, int k) {
  if (dp[i][j][k] != -1) return dp[i][j][k];
  if (i + j + k == 0) return 0;
  ld expected_turns = (ld) n / (i + j + k);
  dp[i][j][k] = expected_turns;
  if (i) dp[i][j][k] += (ld) i / (i + j + k) * get(i - 1, j, k);
  if (j) dp[i][j][k] += (ld) j / (i + j + k) * get(i + 1, j - 1, k);
  if (k) dp[i][j][k] += (ld) k / (i + j + k) * get(i, j + 1, k - 1);
  return dp[i][j][k];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  vi a(4);
  rep(i, 0, n) {
    int v;
    cin >> v;
    a[v]++;
  }
  rep(i, 0, MAXN + 1) rep(j, 0, MAXN + 1) rep(k, 0, MAXN + 1)
    dp[i][j][k] = -1;
  cout << fixed << setprecision(11) << get(a[1], a[2], a[3]) << '\n';
}
