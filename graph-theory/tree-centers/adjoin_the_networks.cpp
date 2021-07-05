// tree diameter, greedy
// https://open.kattis.com/problems/adjoin
// 2015 Nordic Subregional

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back

using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

pii diameter(const auto& g, int i, auto& vis, int p = -1) {
  assert(!vis[i]);
  vis[i] = true;

  int bestpath = 0, bestdip = 0;
  int mx = -1, mx2 = -1;
  trav(e, g[i]) if (e.to != p) {
    auto [path, dip] = diameter(g, e.to, vis, i);
    if (path > mx) {
      mx2 = mx;
      mx = path;
    } else if (path > mx2) {
      mx2 = path;
    }
    bestdip = max(bestdip, dip);
  }
  bestpath = max(bestpath, 1 + mx);
  bestdip = max(bestdip, 2 + mx + mx2);
  return {bestpath, bestdip};
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].PB({v});
    g[v].PB({u});
  }

  int res = 0;
  vi chains;
  vi vis(n);
  rep(i, 0, n) if (!vis[i]) {
    auto [bla, diam] = diameter(g, i, vis);
    chains.PB((diam + 1) / 2);
    res = max(res, diam);
  }
  sort(all(chains), greater<>{});
  if (sz(chains) >= 2) {
    res = max(res, chains[0] + chains[1] + 1);
  }
  if (sz(chains) >= 3) {
    res = max(res, chains[1] + chains[2] + 2);
  }
  cout << res << '\n';
}
