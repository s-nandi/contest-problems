// gomory-hu tree (sum of all s-t cuts)
// https://codeforces.com/gym/101480/problem/J
// 2015 Central Europe Regional

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
using vll = vector<ll>;
using vpii = vector<pii>;
 
struct edge{int to; ll w;};
using graph = vector<vector<edge>>;
 
const int inf = 1e9;
 
const ll mod = 1e9+7;
 
struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); } // if you need flows
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, ll rcap = 0) {
    adj[a].push_back({b, sz(adj[b]), c, c});
    adj[b].push_back({a, sz(adj[a]) - 1, rcap, rcap});
  }
  ll dfs(int v, int t, ll f) {
    if (v == t || !f) return f;
    for (int& i = ptr[v]; i < sz(adj[v]); i++) {
      Edge& e = adj[v][i];
      if (lvl[e.to] == lvl[v] + 1)
        if (ll p = dfs(e.to, t, min(f, e.c))) {
          e.c -= p, adj[e.to][e.rev].c += p;
          return p;
        }
    }
    return 0;
  }
  ll calc(int s, int t) {
    ll flow = 0; q[0] = s;
    rep(L,0,31) do { // 'int L=30' maybe faster for random data
      lvl = ptr = vi(sz(q));
      int qi = 0, qe = lvl[s] = 1;
      while (qi < qe && !lvl[t]) {
        int v = q[qi++];
        for (Edge e : adj[v])
          if (!lvl[e.to] && e.c >> (30 - L))
            q[qe++] = e.to, lvl[e.to] = lvl[v] + 1;
      }
      while (ll p = dfs(s, t, LLONG_MAX)) flow += p;
    } while (lvl[t]);
    return flow;
  }
  bool leftOfMinCut(int a) { return lvl[a] != 0; }
};
 
typedef array<ll, 3> Edge;
vector<Edge> gomoryHu(int N, vector<Edge> ed) {
  vector<Edge> tree;
  vi par(N);
  rep(i,1,N) {
    Dinic D(N); // Dinic also works
    for (Edge t : ed) D.addEdge(t[0], t[1], t[2], t[2]);
    tree.push_back({i, par[i], D.calc(i, par[i])});
    rep(j,i+1,N)
      if (par[j] == par[i] && D.leftOfMinCut(j)) par[j] = i;
  }
  return tree;
}
 
ll INF = 1'000'000'000'000'000'000LL;
 
ll dfs(const auto& g, int i, int root, auto cost, int prev = -1) {
  ll acc = 0;
  if (i < root) acc += cost;
  trav(e, g[i]) if (e.to != prev) {
    acc += dfs(g, e.to, root, min(cost, e.w), i);
  }
  return acc;
}
 
int main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, m; cin >> n >> m;
 
  vector<Edge> edges;
    
  rep(i, 0, m) {
    int u, v; cin >> u >> v;
    u--, v--;
    edges.PB({u, v, 1});
  }
 
  auto tree = gomoryHu(n, edges);
  graph g(n);
  trav(e, tree) {
    const auto& [i, par, w] = e;
    g[i].PB({par, w});
    g[par].PB({i, w});
  }
 
  ll acc = 0;
  rep(i, 0, n) {
    acc += dfs(g, i, i, INF);
  }
  cout << acc << '\n';
}
