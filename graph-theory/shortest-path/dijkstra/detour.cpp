// dijkstra, edge labels (for killing edges), path reconstruction from a to b
// https://open.kattis.com/problems/detour
// 2017 Benelux Algorithm Programming Contest

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

struct edge{int to; ll w; int id;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;

auto minn(auto& a, auto b){return b < a ? a = b, true : false;}

constexpr ll INF = 1e15;
void dijkstra(const auto& g, int src, auto& par) {
  vi vis(sz(g));
  vector<ll> dist(sz(g), INF);
  min_queue<pair<ll, int>> pq;
  dist[src] = 0;
  pq.push({dist[src], src});
  while (!empty(pq)) {
    auto [d, i] = pq.top(); pq.pop();
    if (vis[i]) continue;
    vis[i] = true;
    trav(e, g[i]) if (minn(dist[e.to], d + e.w)) {
      pq.push({dist[e.to], e.to});
      par[e.to] = e.id;
    }
  }
}

bool dfs(const auto& g, int i, int dst, auto& vis, const auto& bad, vi& path) {
  if (i == dst) {
    path.PB(i);
    return true;
  } else {
    if (vis[i]) return false;
    vis[i] = true;
    trav(e, g[i]) if (!bad[e.id] and !vis[e.to]) { // can't just use edge-visitedness since we can't repeat nodes on our path
      if (dfs(g, e.to, dst, vis, bad, path)) {
        path.PB(i);
        return true;
      }
    }
    return false;
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  graph g(n);
  rep(it, 0, m) {
    int u, v; ll d;
    cin >> u >> v >> d;
    g[u].PB({v, d, 2 * it});
    g[v].PB({u, d, 2 * it + 1});
  }

  vi shpar(n, -1);
  dijkstra(g, 1, shpar);

  vi bad(2 * m); // bad[i] => edge i cannot be used since it lies on a shortest path to node 1
  trav(i, shpar) if (i != -1)
    bad[i ^ 1] = true; // since dijkstra's was run starting from 1, we want to kill the reverse edge

  vi path;
  vi vis(n);
  auto feas = dfs(g, 0, 1, vis, bad, path);
  if (feas) {cout << sz(path) << " "; for(auto i: vector(rbegin(path), rend(path))) cout << i << " "; cout << '\n';}
  else cout << "impossible" << '\n';
}
