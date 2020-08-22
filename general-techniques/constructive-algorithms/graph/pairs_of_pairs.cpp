// dfs tree, constructive, either get long enough path (depth >= half) or at most 1 node is discarded per depth (so < half wasted nodes if depth < half => >= half nodes paired)
// https://codeforces.com/contest/1391/problem/E
// Note: Alternative constructions shown in https://codeforces.com/blog/entry/81265?#comment-677709 (very interesting partitioning idea -- extend while possible and pair "cleverly" when cannot extend) and in
//       https://codeforces.com/blog/entry/81265?#comment-677328 (uses gray/white/black labels during dfs)

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

auto ceildiv(auto a, auto b){return (a + b - 1) / b;}

void dfs(const graph& g, int i, auto& vis, auto& bydepth, auto& path, int d = 0) {
  if (vis[i]) return;
  vis[i] = true;
  bydepth[d].PB(i);
  if (sz(path) < ceildiv(sz(g), 2)) path.PB(i);
  trav(e, g[i])
    dfs(g, e.to, vis, bydepth, path, d + 1);
  if (sz(path) < ceildiv(sz(g), 2)) path.pop_back();
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while(T--) {
    int n, m;
    cin >> n >> m;
    graph g(n);
    rep(it, 0, m) {
      int u, v;
      cin >> u >> v;
      --u; --v;
      g[u].PB({v});
      g[v].PB({u});
    }
    vi vis(n);
    vector<vi> bydepth(n);
    vi path;
    dfs(g, 0, vis, bydepth, path);
    if (sz(path) >= ceildiv(n, 2)) {
      cout << "PATH" << '\n';
      cout << sz(path) << '\n';
      trav(i, path) cout << (i + 1) << " "; cout << '\n';
    } else {
      vector<pii> pairings;
      rep(i, 0, n) {
        for (int j = 0; j + 1 < sz(bydepth[i]); j += 2)
          pairings.PB({bydepth[i][j], bydepth[i][j + 1]});
      }
      cout << "PAIRING" << '\n';
      cout << sz(pairings) << '\n';
      trav(p, pairings) cout << (p.first + 1) << " " << (p.second + 1) << '\n';
    }
  }
}
