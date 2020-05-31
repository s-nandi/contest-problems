// dfs, greedy, dsu on tree-esque but no need for smaller to larger
// https://codeforces.com/contest/1363/problem/E

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using vi = vector<int>;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

void dfs(graph& g, int i, auto& a, int p = -1) {
  trav(e, g[i]) if (e.to != p) {
    a[e.to] = min(a[e.to], a[i]);
    dfs(g, e.to, a, i);
  }
}

using state = tuple<ll, int, int>; // cost, num 0, num 1
state solve(auto& g, int i, auto& a, auto& changeto, int p = -1) {
  ll acc = 0;
  int tot0 = (changeto[i] == 0), tot1 = (changeto[i] == 1);
  trav(e, g[i]) if (e.to != p) {
    auto [cost, n0, n1] = solve(g, e.to, a, changeto, i);
    tot0 += n0;
    tot1 += n1;
    acc += cost;
  }
  int canfix = min(tot0, tot1);
  auto delta = (ll) 2 * a[i] * canfix;
  acc += delta;
  tot0 -= canfix;
  tot1 -= canfix;
  //cout << "At " << i << " : " << acc << " " << tot0 << " " << tot1 << endl;
  return {acc, tot0, tot1};
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vi a(n), b(n), c(n);
  rep(i, 0, n)
    cin >> a[i] >> b[i] >> c[i];
  graph g(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }

  vi changeto(n, -1);
  rep(i, 0, n) {
    if (b[i] == c[i]) continue;
    changeto[i] = c[i];
  }
  dfs(g, 0, a);
  auto [cost, rem0, rem1] = solve(g, 0, a, changeto);
  if (rem0 + rem1 > 0) cout << -1 << '\n';
  else cout << cost << '\n';
}
