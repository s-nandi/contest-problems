// dfs, treating heavy (>= K) and light nodes differently, finding connected component with sum in range [K, 2K]
// https://dmoj.ca/problem/dmopc19c7p3

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

bool dfs(graph& g, int i, auto& a, auto& sol, auto& vis, ll k, ll& acc) {
  if (vis[i]) return false;
  vis[i] = true;
  acc += a[i];
  sol.PB(i);
  if (acc >= k and acc <= 2 * k) return true;
  trav(e, g[i]) if (!vis[e.to] and a[e.to] < k) {
    if (dfs(g, e.to, a, sol, vis, k, acc)) return true;
  }
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n; ll k;
  cin >> n >> k;
  vector<ll> a(n);
  trav(i, a) cin >> i;
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  vi sol;
  bool done = false;
  rep(i, 0, n) {
    if (a[i] >= k and a[i] <= 2 * k) sol = {i}, done = true;
  }
  if (!done) {
    vi vis(n);
    rep(i, 0, n) if (a[i] < k and !vis[i]) {
      sol.clear();
      ll total = 0;
      if (dfs(g, i, a, sol, vis, k, total)) {
        done = true;
        break;
      }
    }
  }
  if (!done) cout << -1 << '\n';
  else {
    cout << sz(sol) << '\n';
    trav(i, sol) cout << i + 1 << " "; cout << '\n';
  }
}
