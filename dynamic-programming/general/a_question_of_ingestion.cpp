// dp
// https://open.kattis.com/problems/ingestion
// 2017 East-Central NA Regional

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;
using pii = pair<int, int>;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
#define cauto const auto

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = true;

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  vi a(n);
  trav(i, a) cin >> i;

  vi amt(n + 1);
  amt[0] = m;
  rep(i, 1, n + 1) amt[i] = 2 * amt[i - 1] / 3;

  constexpr auto INF = 1031231234;
  auto dp = vector(n + 1, vector(n + 5, vector(2, -INF))); // dp[i][j][k] => considering course i (0 indexed), with max capacity amt[j],
                                                           //                and k == 1 if a break was taken last move
                                                           // (might be k == 0 if j == 0 since it doesn't matter)
  dp[0][0][0] = 0;
  auto maxx = [](auto& a, auto b){a = max(a, b);};
  rep(i, 0, n) {
    rep(j, 0, n + 1) {
      rep(k, 0, 2) {
        if (k + 1 >= 2)
          maxx(dp[i + 1][0][0], dp[i][j][k]);
        else
          maxx(dp[i + 1][max(0, j - 1)][k + 1], dp[i][j][k]);
        auto delta = min(amt[j], a[i]);
        maxx(dp[i + 1][j + 1][0], dp[i][j][k] + delta);
      }
    }
  }
  
  auto best = 0;
  trav(row, dp.back()) trav(elem, row) maxx(best, elem);
  cout << best << '\n';
}
