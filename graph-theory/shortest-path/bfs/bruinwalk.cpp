// bfs, greedy (flyers should immediately rush to exit)
// https://codesprintla20-team.kattis.com/problems/codesprintla20.bruinwalk

#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()
#define PB push_back

struct edge{int to;};
using graph = vector<vector<edge>>;

const int INF = 1031231234;
auto bfs(graph& g, int s, int t) {
  int n = sz(g);
  vi vis(n);
  vi dist(n, INF);
  queue<int> q;
  q.push(s);
  dist[s] = 0;
  while(!q.empty()) {
    auto i = q.front(); q.pop();
    trav(e, g[i]) if (dist[i] + 1 < dist[e.to]) {
      dist[e.to] = dist[i] + 1;
      if (!vis[e.to]) {
        vis[e.to] = true;
        q.push(e.to);
      }
    }
  }
  return dist[t];
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
    --u; --v;
    g[u].PB({v});
    g[v].PB({u});
  }
  int s, t;
  cin >> s >> t;
  --s; --t;
  auto mine = bfs(g, s, t);

  int k;
  cin >> k;
  auto theirs = INF;
  rep(i, 0, k) {
    int s2;
    cin >> s2;
    --s2;
    auto their = bfs(g, s2, t);
    theirs = min(their, theirs);
  }
  if (theirs <= mine) cout << "NO" << '\n';
  else cout << "YES" << '\n';
}
