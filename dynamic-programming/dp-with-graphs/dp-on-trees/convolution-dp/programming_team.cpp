// binary search on answer (convert ratio to single value), tree conv. dp
// https://open.kattis.com/problems/programmingteam
// 2016 NAIPC

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = double;
using vi = vector<int>;
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr int MAXS = 10000;
constexpr int ITERS = 40;
constexpr ld INF = 1e10;

auto maxx(auto& a, auto b){a = max(a, b);}

int dfs_size(const auto& g, int i, auto& sizes) {
  sizes[i] = 1;
  trav(e, g[i]) sizes[i] += dfs_size(g, e.to, sizes);
  return sizes[i];
}

void dfs(const auto& g, int i, const auto& costof, auto& dp, const auto& sizes) {
  dp[i][0] = 0;
  dp[i][1] = costof(i);
  trav(e, g[i]) dfs(g, e.to, costof, dp, sizes);
  trav(e, g[i]) {
    for (int k1 = sizes[i] - sizes[e.to]; k1 >= 1; k1--)
      for (int k2 = sizes[e.to]; k2 >= 1; k2--) {
        maxx(dp[i][k1 + k2], dp[i][k1] + dp[e.to][k2]);
      }
  }
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  cout << setprecision(3) << fixed;

  int k, n;
  cin >> k >> n;
  n++, k++;
  graph g(n);
  vi s(n), p(n), par(n);
  rep(i, 1, n) {
    cin >> s[i] >> p[i] >> par[i];
    g[par[i]].PB({i});
  }

  vi sizes(n);
  dfs_size(g, 0, sizes);

  auto check = [&](ld c) {
                 auto costof = [&](int i){return p[i] - c * s[i];};
                 auto dp = vector(n, vector<ld>(n + 1, -INF));
                 rep(i, 0, n) dp[i][0] = 0;
                 dfs(g, 0, costof, dp, sizes);
                 return dp[0][k] > 0;
               };
  
  ld lo = 0., hi = MAXS + 1;
  rep(it, 0, ITERS) {
    auto mid = (lo + hi) / 2;
    auto feas = check(mid);
    if (feas) lo = mid;
    else hi = mid;
  }
  cout << lo << '\n';
}
