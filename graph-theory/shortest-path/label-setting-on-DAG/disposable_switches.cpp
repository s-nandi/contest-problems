// sh. path on DAG (time expansion induces DAG so no need for dijkstra), path length can be: total_weight + (constant >= 0) * num_edges => find sh. path while fixing num_edges
// https://open.kattis.com/problems/disposableswitches
// 2019 Northwestern Europe Regional

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
constexpr bool dbg = false;
 
struct edge {int to, w;};
using graph = vector<vector<edge>>;

bool minn(auto& a, auto b){return b < a ? a = b, true : false;}
 
constexpr ll INF = 1e18;
constexpr auto EPS = 1e-9;
 
void dfs(const auto& g, const auto& dists, int i, int ed, auto& vis, auto& isbad) {
  if (vis[i][ed]) return;
  vis[i][ed] = true;
  isbad[i] = false;
  if (ed > 0) {
    trav(e, g[i]) if (dists[i][ed] == dists[e.to][ed - 1] + e.w and !vis[e.to][ed - 1]) {
      dfs(g, dists, e.to, ed - 1, vis, isbad);
    }
  }
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    g[u].PB({v, w});
    g[v].PB({u, w});
  }
 
  auto dists = vector(n, vector(n, INF));
  dists[0][0] = 0;
  rep(ed, 0, n - 1) {
    rep(i, 0, n) {
      minn(dists[i][ed + 1], dists[i][ed]);
      trav(e, g[i])
        minn(dists[e.to][ed + 1], dists[i][ed] + e.w);
    }
  }
 
  vi candidate{0};
  rep(y, 1, n) if (dists[n - 1][y] < INF) {
    ld ub = INF;
    rep(x, 0, y) {
      auto atmost = (ld)(dists[n - 1][x] - dists[n - 1][y]) / (y - x);
      ub = min(ub, atmost);
    }
    ld lb = -INF;
    rep(z, y + 1, n) {
      auto atleast = (ld)(dists[n - 1][y] - dists[n - 1][z]) / (z - y);
      lb = max(lb, atleast);
    }
    if (lb < ub + EPS)
      candidate.PB(y);
  }
 
  vector isbad(n, true);
  auto vis = vector(n, vector(n, false));
  trav(ed, candidate) dfs(g, dists, n - 1, ed, vis, isbad);
 
  cout << accumulate(all(isbad), 0) << '\n';
  rep(i, 0, n) if (isbad[i]) cout << (i + 1) << " "; cout << '\n';
}
