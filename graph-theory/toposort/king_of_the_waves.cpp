// constructive, dfs (toposorting a tree), greedy
// https://open.kattis.com/problems/kingofthewaves
// 2017 Benelux Algorithm Programming Challenge

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

void dfs(const auto& g, int i, auto& vis, vi& path, int p = -1) {
  if (vis[i]) return;
  vis[i] = true;
  path.PB(i);
  trav(e, g[i]) if (!vis[e.to])
    dfs(g, e.to, vis, path, i);
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  graph g(n);
  rep(i, 0, n) {
    string s;
    cin >> s;
    rep(j, 0, n) if (i != j) {
      if (s[j] == '1' and j != 0) g[i].PB({j}); // i can beat j
                                                // don't allow edges that would involve player 0 losing
    }
  }
  vi vis(n), path;
  dfs(g, 0, vis, path); // construct a toposort rooted at 0
  if (any_of(all(vis), [](auto visited){return !visited;})) cout << "impossible" << '\n';
  else
    for (int i: vector(rbegin(path), rend(path))) cout << i << " "; cout << '\n';
}
