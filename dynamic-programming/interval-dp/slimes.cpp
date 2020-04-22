// interval dp (MCM style pivot), prefix sums
// https://atcoder.jp/contests/dp/tasks/dp_n

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)

const int MAXN = 400;
const ll INF = 1e15;
ll psum[MAXN + 5];
ll dp[MAXN + 5][MAXN + 5]; // len, start

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n);
  trav(i, a) cin >> i;
  psum[0] = a[0];
  rep(i, 1, n)
    psum[i] = psum[i - 1] + a[i];
  auto sum = [&](int i, int j){return i ? (psum[j] - psum[i - 1]) : psum[j];};

  rep(len, 0, n + 1) rep(i, 0, n)
    dp[len][i] = INF;
  rep(i, 0, n) {
    dp[1][i] = 0;
    if (i + 1 < n)
      dp[2][i] = a[i] + a[i + 1];
  }
  rep(len, 3, n + 1) {
    rep(i, 0, n - len + 1) {
      int j = i + len - 1;
      rep(step, 1, len) {
        int k = i + step;
        auto possible = dp[step][i] + dp[len - step][k] + sum(i, k - 1) + sum(k, j);
        dp[len][i] = min(dp[len][i], possible);
      }
    }
  }
  cout << dp[n][0] << '\n';
}
