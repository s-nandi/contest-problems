// sh. path property, edge disjoint path, only people starting same dist away (from 0) can collide
// https://codeforces.com/gym/101208/problem/C
// 2013 World Finals

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a);i<(b);++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
struct edge{int to, w;};
using graph = vector<vector<edge>>;
 
constexpr auto dbg = false;

struct Dinic {
  struct edge{int to, id;};
  using graph = vector<vector<edge>>;

  using flowT = int;
  static constexpr flowT INF = numeric_limits<flowT>::max() / 2;
  
  graph g;
  vector<flowT> capacities, flow;
  vi level, start;
  Dinic(int s) : g(s), level(s), start(s) {}
  void addEdge(int from, int to, flowT capacity) {
    g[from].push_back({to, sz(flow)});
    capacities.push_back(capacity), flow.push_back(0);
    g[to].push_back({from, sz(flow)});
    capacities.push_back(0), flow.push_back(0);
  }
  flowT residual(int id) { return capacities[id] - flow[id]; }
  bool build(int s, int t) {
    queue<int> q;
    q.push(s);
    fill(all(level), -1);
    level[s] = 0;
    while (!q.empty()) {
      int curr = q.front();
      q.pop();
      trav(e, g[curr])
        if (level[e.to] == -1 and residual(e.id) > 0)
          q.push(e.to), level[e.to] = level[curr] + 1;
    }
    return level[t] != -1;
  }
  flowT push(int i, int t, flowT lo = INF) {
    if (i == t) return lo;
    for (; start[i] < sz(g[i]); start[i]++) {
      edge e = g[i][start[i]];
      if (level[e.to] == level[i] + 1 and residual(e.id) > 0) {
        flowT got = push(e.to, t, min(lo, residual(e.id)));
        if (got > 0) {
          flow[e.id] += got;
          flow[e.id ^ 1] -= got;
          return got;
        }
      }
    }
    return 0;
  }
  flowT calc(int s, int t) {
    flowT res = 0;
    while (build(s, t)) {
      fill(all(start), 0);
      while (auto delta = push(s, t)) res += delta;
    }
    return res;
  }
};

const int INF = 1031231234;

template <typename T>
using min_queue = priority_queue<T, vector<T>, greater<T>>;
 
auto minn(auto& a, auto b){return b < a ? a = b, true : false;}

auto dijkstra(int n, const auto& g) {
  vector<ll> dists(n, INF);
  vi vis(n);
  min_queue<pair<ll, int>> pq;
  dists[0] = 0;
  pq.push({dists[0], 0});
  while (!empty(pq)) {
    auto [d, i] = pq.top(); pq.pop();
    if (vis[i]) continue;
    vis[i] = true;
    trav(e, g[i])
      if (minn(dists[e.to], dists[i] + e.w))
        pq.push({dists[e.to], e.to});
  }
  graph res(n);
  rep(i, 0, n) trav(e, g[i]) {
    if (dists[i] + e.w == dists[e.to])
      res[e.to].PB({i, 1});
  }
  return pair{res, dists};
}
 
int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int n, m, c;
  cin >> n >> m >> c;
 
  graph adj(n);
  rep(it, 0, m) {
    int u, v, w;
    cin >> u >> v >> w;
    --u; --v;
    adj[u].PB({v, w});
    adj[v].PB({u, w});
  }
  vi queries(c);
  trav(i, queries) { cin >> i; --i; }
  
  auto [g, dists] = dijkstra(n, adj);
  map<ll, vi> bydist;
  trav(i, queries)
    bydist[dists[i]].PB(i);
 
  int res = 0;
  for (const auto& [d, initial]: bydist) {
    int nn = n + 2;
    int src = nn - 2, snk = nn - 1;
    auto dnc = Dinic(nn);
    dnc.addEdge(0, snk, INF);
    trav(i, initial) dnc.addEdge(src, i, 1);
    rep(i, 0, n) trav(e, g[i])
      dnc.addEdge(i, e.to, 1);
    res += dnc.calc(src, snk);
  }
  cout << res << '\n';
}
