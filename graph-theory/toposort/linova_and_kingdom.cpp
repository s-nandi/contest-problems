// toposort, greedy (best local deltas)
// https://codeforces.com/contest/1336/problem/A

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

int dfs(auto& g, int i, auto& depths, auto& weights, int p = -1, int d = 0) {
  depths[i] = d;
  weights[i] = 1;
  trav(e, g[i])
    if (e.to != p)
      weights[i] += dfs(g, e.to, depths, weights, i, d + 1);
  return weights[i];
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;
  graph g(n);
  vi deg(n);
  rep(i, 0, n - 1) {
    int u, v;
    cin >> u >> v;
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
    ++deg[u];
    ++deg[v];
  }
  vi depths(n), weights(n);
  dfs(g, 0, depths, weights);
  auto priority = [&](int i){return depths[i] - (weights[i] - 1);};
  auto cmp = [&](int i, int j){return priority(i) < priority(j);};
  priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
  rep(i, 0, n) {
    if (deg[i] == 1) {
      q.push(i);
      --deg[i];
    }
  }
  int took = 0;
  auto sol = 0LL;
  while (!q.empty() and took < k) {
    auto i = q.top();
    q.pop();
    took++;
    sol += priority(i);
    trav(e, g[i])
      if (--deg[e.to] == 1)
        q.push(e.to);
  }
  cout << sol << '\n';
}
