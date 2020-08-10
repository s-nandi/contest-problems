// bitmask dp, 4x4 (or bigger) submatrices aren't feasible because they contain an even number of 2x2 submatrices
// https://codeforces.com/contest/1391/problem/D

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

auto minn(auto& a, auto b){a = min(a, b);}

const int INF = 1031231234;
auto solve(const auto& grid) {
  auto n = sz(grid), m = sz(grid[0]);
  auto compatible = vector(1 << n, vi(1 << n));
  rep(bm, 0, 1 << n) {
    rep(tm, 0, 1 << n) { // bm = prev column, tm = curr column
      auto total = bm | (tm << n);
      auto feasible = true;
      rep(start, 0, n - 1) {
	auto num1 = 0;
	rep(row, start, start + 2) rep(col, 0, 2)
	  num1 += !!(total & (1 << (row + col * n)));
	feasible &= (num1 & 1);
      }
      compatible[bm][tm] = feasible;
    }
  }
  auto dp = vector(m + 1, vi(1 << n, INF));
  dp[0][0] = 0;
  rep(i, 0, m) {
    rep(bm, 0, 1 << n) {
      rep(tm, 0, 1 << n) {
	if (i != 0 and !compatible[bm][tm]) continue;
	auto cost = 0;
	rep(k, 0, n) cost += !!(tm & (1 << k)) != grid[k][i];
	minn(dp[i + 1][tm], dp[i][bm] + cost);
      }
    }
  }
  return *min_element(all(dp[m]));
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  auto [mn, mx] = minmax(n, m);
  auto grid = vector(mn, vi(mx));
  rep(i, 0, n) rep(j, 0, m) {
    char c;
    cin >> c;
    (n == mn ? grid[i][j] : grid[j][i]) = c - '0';
  }
  if (mn < 2) cout << 0 << '\n';
  else if (mn > 3) cout << -1 << '\n';
  else cout << solve(grid) << '\n';
}
