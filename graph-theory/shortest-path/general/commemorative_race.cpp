// longest path tree (identifying edges that MUST be taken on any longest path down the tree)
// https://open.kattis.com/problems/commemorativerace
// 2019 mid-central regional

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

int dfs(const graph& g, int i, auto& vis, auto& mx) {
  if (vis[i]) return mx[i][0];
  vis[i] = true;
  trav(e, g[i]) {
    auto got = dfs(g, e.to, vis, mx) + 1;
    rep(t, 0, 2) if (got > mx[i][t]) swap(got, mx[i][t]);
  }
  return mx[i][0];
}

void solve(const graph& g, int i, vi& vis, const auto& mx, auto& max_delta_bydepth) {
  if (vis[i]) return;
  vis[i] = true;
  trav(e, g[i]) if (mx[e.to][0] == mx[i][0] - 1) { // i to e.to is part of some longest path
    if (i) max_delta_bydepth[mx[i][0]].PB(mx[i][0] - mx[i][1]); // longest - (mx[i][0] - mx[i][1]) is a possible result if
                                                                // we remove the worst-case edge going from i downwards
                                                                // since we can't remove the fake-edge from the sentinel node 0,
                                                                // we need the if(i) check
    solve(g, e.to, vis, mx, max_delta_bydepth);
  }
}

int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;
  ++n; // 0 is used as a sentinel root so everything is in one connected component
  
  graph g(n);
  rep(it, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].PB({v});
  }
  rep(i, 1, n) g[0].PB({i});

  vi vis(n);
  vector<array<int, 2>> mx(n, {0, 0}); // mx[i][0/1] = first/second longest path to a leaf
  int longest = dfs(g, 0, vis, mx);
  
  fill(all(vis), 0);
  vector<vi> max_delta_bydepth(n);
  solve(g, 0, vis, mx, max_delta_bydepth);

  int best = longest;
  rep(d, 0, n + 1) if (sz(max_delta_bydepth[d]) == 1) { // if there's a bottleneck edge at depth d
    auto possible = longest - max_delta_bydepth[d][0];
    best = min(best, possible);
  }
  cout << (best - 1) << '\n'; // subtract 1 since we have a sentinel node at the top
}
