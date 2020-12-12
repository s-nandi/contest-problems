// dp on trees, combo (counting inverse), # of disconnected nodes is nc2(n - 1) - sum_{child} size(child)^2, can greedily join largest children to maximize connections
// https://open.kattis.com/problems/ontrack
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

constexpr auto dbg = false;

int nc2(int n){return n * (n - 1) / 2;}

int dfs(auto& g, int i, auto& below, auto& above, int p = -1) {
  below[i] = 1;
  trav(e, g[i]) if (e.to != p)
    below[i] += dfs(g, e.to, below, above, i);
  above[i] = sz(g) - below[i];
  return below[i];
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n; ++n;
  graph g(n);
  rep(it, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    g[u].PB({v});
    g[v].PB({u});
  }
  vi below(n), above(n);
  dfs(g, 0, below, above);

  const auto total = nc2(n - 1);
  int critical = 0;
  int max_disconnected = -1;
  rep(i, 0, n) {
    int excluded = 0;
    trav(e, g[i]) if (below[e.to] < below[i])
      excluded += nc2(below[e.to]);
    excluded += nc2(above[i]);
    auto possible = total - excluded;
    if (possible > max_disconnected) {
      max_disconnected = possible;
      critical = i;
    }
  }

  int max_recovered = 0;
  {
    vi subtrees;
    trav(e, g[critical]) if (below[e.to] < below[critical])
      subtrees.PB(below[e.to]);
    subtrees.PB(above[critical]);
    sort(all(subtrees), greater<>{});
    if (sz(subtrees) > 1) {
      max_recovered = subtrees[0] * subtrees[1];
    }
  }
  cout << max_disconnected << " " << (max_disconnected - max_recovered) << '\n';
}
