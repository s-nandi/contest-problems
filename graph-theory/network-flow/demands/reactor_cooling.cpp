// circulation with demands (check feasibility, reconstruct solution)
// https://codeforces.com/gym/100199/attachments (problem B)

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
#define cauto const auto
using ll = long long;
using ld = long double;
using pii = pair<int,int>;
using vi = vector<int>;
 
struct edge{int to;};
using graph = vector<vector<edge>>;

struct PushRelabel {
  struct Edge {
    int dest, back;
    ll f, c;
  };
  vector<vector<Edge>> g;
  vector<ll> ec;
  vector<Edge*> cur;
  vector<vi> hs; vi H;
  PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}
 
  void addEdge(int s, int t, ll cap, ll rcap=0) {
    if (s == t) return;
    g[s].push_back({t, sz(g[t]), 0, cap});
    g[t].push_back({s, sz(g[s])-1, 0, rcap});
  }
 
  void addFlow(Edge& e, ll f) {
    Edge &back = g[e.dest][e.back];
    if (!ec[e.dest] && f) hs[H[e.dest]].push_back(e.dest);
    e.f += f; e.c -= f; ec[e.dest] += f;
    back.f -= f; back.c += f; ec[back.dest] -= f;
  }
  ll calc(int s, int t) {
    int v = sz(g); H[s] = v; ec[t] = 1;
    vi co(2*v); co[0] = v-1;
    rep(i,0,v) cur[i] = g[i].data();
    for (Edge& e : g[s]) addFlow(e, e.c);
 
    for (int hi = 0;;) {
      while (hs[hi].empty()) if (!hi--) return -ec[s];
      int u = hs[hi].back(); hs[hi].pop_back();
      while (ec[u] > 0)  // discharge u
        if (cur[u] == g[u].data() + sz(g[u])) {
          H[u] = 1e9;
          for (Edge& e : g[u]) if (e.c && H[u] > H[e.dest]+1)
                                 H[u] = H[e.dest]+1, cur[u] = &e;
          if (++co[H[u]], !--co[hi] && hi < v)
            rep(i,0,v) if (hi < H[i] && H[i] < v)
              --co[H[i]], H[i] = v + 1;
          hi = H[u];
        } else if (cur[u]->c && H[u] == H[cur[u]->dest]+1)
          addFlow(*cur[u], min(ec[u], cur[u]->c));
        else ++cur[u];
    }
  }
  bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};
 
const ll INF = numeric_limits<ll>::max() / 4;
template <typename Solver>
struct FlowWithDemands {
  using Result = pair<ll, map<pii, ll>>;
  int n;
  Solver solver;
  map<pii, ll> lb;
  vll net_lb;
  FlowWithDemands(int nn) : n{nn}, solver(n + 2),  net_lb(n) {}
  void addEdge(int i, int j, auto demand, auto cap) { 
    assert(demand <= cap);
    solver.addEdge(i, j, cap - demand); 
    lb[{i, j}] += demand;
    net_lb[i] += demand;
    net_lb[j] -= demand;
  }
  optional<Result> maxflow(int s, int t, ll lim = INF) {
    ll net_supply = 0, net_demand = 0;
    rep(i, 0, n) { // n = src, n+1 = snk
      if (net_lb[i] < 0) {
        solver.addEdge(n, i, -net_lb[i]);
        net_supply += -net_lb[i];
      } else if (net_lb[i] > 0) {
        solver.addEdge(i, n + 1, net_lb[i]);
        net_demand += net_lb[i];
      }
    }
    solver.addEdge(t, s, lim); 
    if (net_supply != net_demand) return nullopt;
    else {
      auto bflow = solver.calc(n, n + 1); 
      if (bflow < net_supply) {
        return nullopt;
      } else {
        auto dflow = solver.calc(s, t); 
        map<pii, ll> res;
        rep(i, 0, n) for (auto ed: solver.g[i]) {
          auto j = ed.dest;
          res[{i, j}] = ed.f + lb[{i, j}];
        }
        return Result{bflow + dflow, res};
      }
    }
  }
};
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  cout << fixed << setprecision(15);
 
  freopen("cooling.in", "r", stdin);
  freopen("cooling.out", "w", stdout);
 
  int n, m;
  cin >> n >> m;
  auto mf = FlowWithDemands<PushRelabel>(n + 2);
  vector<pii> edges;
  rep(i, 0, m) {
    int u, v, lb, ub;
    cin >> u >> v >> lb >> ub;
    --u; --v;
    mf.addEdge(u, v, lb, ub);
    edges.PB({u, v});
  }
  auto res = mf.maxflow(n, n + 1);
  if (!res) {
    cout << "NO" << '\n';
  } else {
    cout << "YES" << '\n';
    const auto& [flow, construction] = *res;
    for (const auto& [u, v]: edges) {
      cout << construction.at({u, v}) << '\n';
    }
  }
}
