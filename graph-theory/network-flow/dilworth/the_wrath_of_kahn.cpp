// dilworth's thm, dfs matching, treating directed graph as partial ordering
// https://open.kattis.com/problems/thewrathofkahn
// 2020 Mount Allison Programming Contest

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back

using graph = vector<vector<int>>;

vi topo_sort(const graph& gr) {
  vi indeg(sz(gr)), ret;
  trav(li, gr) trav(x, li) indeg[x]++;
  queue<int> q;
  rep(i,0,sz(gr)) if (indeg[i] == 0) q.push(-i);
  while (!q.empty()) {
    int i = -q.front();
    ret.push_back(i);
    q.pop();
    trav(x, gr[i])
      if (--indeg[x] == 0) q.push(-x);
  }
  return ret;
}

bool find(int j, const vector<vi>& g, vi& btoa, vi& vis) {
  if (btoa[j] == -1) return 1;
  vis[j] = 1; int di = btoa[j];
  trav(e, g[di])
    if (!vis[e] && find(e, g, btoa, vis)) {
      btoa[e] = di;
      return 1;
    }
  return 0;
}
int dfsMatching(const vector<vi>& g, vi& btoa) {
  vi vis;
  rep(i,0,sz(g)) {
    vis.assign(sz(btoa), 0);
    trav(j,g[i])
      if (find(j, g, btoa, vis)) {
        btoa[j] = i;
        break;
      }
  }
  return sz(btoa) - (int)count(all(btoa), -1);
}

graph condense(const graph& g, const vi& used) {
  vi mapping(sz(used), -1);
  int it = 0;
  rep(i, 0, sz(used))
    if (used[i]) mapping[i] = it++;
  graph res(it);
  rep(i, 0, sz(g)) if (used[i])
    trav(e, g[i]) if (used[e])
      res[mapping[i]].PB(mapping[e]);
  return res;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(i, 0, m) {
    int u, v;
    cin >> u >> v;
    g[u].PB(v);
  }
  vi used(n);
  auto tp = topo_sort(g);
  trav(i, tp) used[i] = true;
  g = condense(g, used);
  n = sz(g);
  auto haspath = vector(n, vi(n));
  rep(i, 0, n) trav(e, g[i])
    haspath[i][e] = true;
  rep(k, 0, n) rep(i, 0, n) rep(j, 0, n)
    haspath[i][j] |= haspath[i][k] && haspath[k][j];
  rep(i, 0, n) rep(j, 0, n)
    if (haspath[i][j])
      g[i].PB(j); // duplicate edges are fine here
  vi btoa(n, -1);
  auto matched = dfsMatching(g, btoa);
  cout << n - matched << '\n'; // thank you dilworth
}
