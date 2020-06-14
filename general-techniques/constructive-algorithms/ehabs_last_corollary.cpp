// constructive, coloring, cycle construction, if graph has no <= k length cycle it has some >= k node tree as a subgraph
// https://codeforces.com/contest/1364/problem/D

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

void flood(graph &g, int i, auto& vis, int& rem) {
  if (rem == 0) return;
  if (vis[i]) return;
  vis[i] = true;
  rem--;
  trav(e, g[i]) if (!vis[e.to])
    flood(g, e.to, vis, rem);
}

graph induced(graph& g, int s) {
  int n = sz(g);
  vi vis(n);
  int rem = s;
  flood(g, 0, vis, rem);
  graph res(n);
  rep(i, 0, n) {
    trav(e, g[i]) {
      if (vis[i] and vis[e.to]) {
        res[i].PB({e.to});
      }
    }
  }
  return res;
}

int dfs(graph& g, int i, auto& vis, auto& color, auto& cycle, int p = -1) {
  if (vis[i]) {cycle.PB(i); return true;}
  vis[i] = true;

  trav(e, g[i]) if (e.to != p) {
    color[e.to] = 1 - color[i];
    if (dfs(g, e.to, vis, color, cycle, i)) {
      cycle.PB(i);
      return true;
    }
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m, k;
  cin >> n >> m >> k;

  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  g = induced(g, k);

  vi cycle;
  vi color(n, -1);
  vi vis(n);
  color[0] = 0;
  auto has_cycle = dfs(g, 0, vis, color, cycle);
  if (has_cycle) {
    set<int> have;
    vi actual;
    for (int i = sz(cycle) - 1; i >= 0; i--) {
      int node = cycle[i];
      
      if (have.count(node)) break;
      have.insert(node);
      actual.PB(node);
     
      have.insert(node);
    }
    cout << 2 << '\n';
    cout << sz(actual) << '\n';
    trav(i, actual) cout << i + 1 << " "; cout << '\n';
  } else {
    int n0 = 0, n1 = 0;
    rep(i, 0, n) {
      if (color[i] == -1) continue;
      if (color[i] == 0) n0++;
      else n1++;
    }
    int bigger = 0;
    int cnt = n0;
    if (n0 < n1) {
      bigger = 1;
      cnt = n1;
    }
    int need = (k + 1) / 2;
    assert(cnt >= need);
    vi indep;
    rep(i, 0, n) {
      if (color[i] == bigger and sz(indep) < need)
        indep.PB(i);
    }
    cout << 1 << '\n';
    trav(i, indep) cout << i + 1 << " "; cout << '\n';
  }    
}
