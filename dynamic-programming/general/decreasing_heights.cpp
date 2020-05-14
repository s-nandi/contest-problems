// dp/combo, normalize trick (-dist for each square dist away from start)
// https://codeforces.com/contest/1353/problem/F

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
using ll = long long;
using ld = long double;

#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

const ll INF = 1e18;
auto minn(auto& a, auto b){a = min(a, b);}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    auto grid = vector(n, vector<ll>(m));
    trav(row, grid) {
      trav(c, row) cin >> c;
    }

    vector<ll> values;
    rep(i, 0, n) {
      rep(j, 0, m) {
        grid[i][j] -= (i + j);
        values.PB(grid[i][j]);
      }
    }

    auto best = INF;
    auto dp = vector(n, vector<ll>(m, INF));
    trav(base, values) {
      if (grid[0][0] < base) continue;
      rep(i, 0, n) fill(all(dp[i]), INF);
      dp[0][0] = grid[0][0] - base;
      rep(i, 0, n) {
        rep(j, 0, m) {
          auto cost = (grid[i][j] < base) ? INF : (grid[i][j] - base);
          if (i) minn(dp[i][j], dp[i - 1][j] + cost);
          if (j) minn(dp[i][j], dp[i][j - 1] + cost);
        }
      }
      minn(best, dp[n - 1][m - 1]);
    }
    cout << best << '\n';
  }
}
