// max flow with demands (construction), greedy, bipartite column/row node construction
// https://codeforces.com/contest/704/problem/D

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
using vll = vector<ll>;
using vpii = vector<pii>;
 
unsigned seed_ = chrono::high_resolution_clock::now().time_since_epoch().count();
mt19937 generator_{seed_};
template <typename T>
auto rng(T lo, T hi) {
  auto dist = uniform_int_distribution<T>(lo, hi);
  return dist(generator_);
}
constexpr auto custom = false;
auto dbg = false;
 
struct edge{int to, id;};
using graph = vector<vector<edge>>;
using flowT = ll;
const ll INF = numeric_limits<ll>::max() / 4;
struct dinic {
  graph g;
  vector <flowT> capacities, flow;
  vector <int> level, startEdge;
  dinic(int s) : g(s), level(s), startEdge(s) {}
  void addEdge(int from, int to, flowT capacity) {
    g[from].push_back({to, (int) flow.size()});
    capacities.push_back(capacity), flow.push_back(0);
    g[to].push_back({from, (int) flow.size()});
    capacities.push_back(0), flow.push_back(0);
  }
  flowT residual(int id){return capacities[id] - flow[id];}
  bool buildLevelGraph(int source, int sink) {
    queue <int> q;
    q.push(source);
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    while (!q.empty())
      {
        int curr = q.front();
        q.pop();
        for (edge e: g[curr])
          if (level[e.to] == -1 and residual(e.id) > 0) {
            q.push(e.to), level[e.to] = level[curr] + 1;
          }
      }
    return level[sink] != -1;
  }
  flowT blockingFlow(int curr, int sink, flowT sent = INF) {
    if (curr == sink) return sent;
    for (; startEdge[curr] < sz(g[curr]); startEdge[curr]++)
      {
        edge e = g[curr][startEdge[curr]];
        if (level[e.to] == level[curr] + 1 and residual(e.id) > 0)
          {
            flowT augment = blockingFlow(e.to, sink, min(sent, residual(e.id)));
            if (augment > 0)
              {
                flow[e.id] += augment;
                flow[e.id ^ 1] -= augment;
                return augment;
              }
          }
      }
    return 0;
  }
  flowT maxflow(int source, int sink) {
    flowT res = 0;
    while (buildLevelGraph(source, sink)) {
      fill(startEdge.begin(), startEdge.end(), 0);
      while (flowT delta = blockingFlow(source, sink))
        res += delta;
    }
    return res;
  }
};
 
// const ll INF = numeric_limits<ll>::max() / 4;
template <typename Solver>
struct FlowWithDemands {
  using Result = pair<ll, map<pii, ll>>;
  int n;
  Solver solver;
  map<pii, ll> lb;
  vll net_lb;
  bool impossible = false;
  FlowWithDemands(int nn) : n{nn}, solver(n + 2),  net_lb(n) {} // node n = src, n+1 = snk
  void addEdge(int i, int j, auto demand, auto cap) {
    assert(demand >= 0 && cap >= 0);
    impossible |= demand > cap;
    solver.addEdge(i, j, cap - demand);
    lb[{i, j}] += demand;
    net_lb[i] += demand;
    net_lb[j] -= demand;
  }
  optional<Result> maxflow(int s, int t, ll lim = INF) {
    if (impossible) return nullopt;
    ll net_supply = 0, net_demand = 0;
    rep(i, 0, n) {
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
    auto bflow = solver.maxflow(n, n + 1);
    if (bflow < net_supply) return nullopt;
    auto dflow = solver.maxflow(s, t);
    map<pii, ll> res;
    ll revflow = 0;
    for (auto [from_to, demand]: lb) if (demand > 0) res[from_to] += demand;
    rep(i, 0, n) for (auto e: solver.g[i]) {
      auto j = e.to;
      auto f = solver.flow[e.id];
      if (f > 0) {
        res[{i, j}] += f;
      }
      if (i == t && j == s) revflow = f;
    }
    return Result{dflow + revflow, res};
  }
};
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
  cout << fixed << setprecision(15);
 
  int n, m;
  cin >> n >> m;
  
  int r, b;
  cin >> r >> b;
 
  int big = r, small = b;
  char bigch = 'r', smallch = 'b';
  if (r < b) {
    swap(big, small);
    swap(bigch, smallch);
  }
 
  map<int, int> x_indexer, y_indexer;
  auto getindex = [](auto& indexer, int val) {
                    if (indexer.count(val)) return indexer[val];
                    else {
                      auto res = sz(indexer);
                      indexer[val] = res;
                      return res;
                    }
                  };
  auto getindex_x = [&](int val) {return getindex(x_indexer, val);};
  auto getindex_y = [&](int val) {return getindex(y_indexer, val);};
  vector<array<int, 2>> shields(n);
  for (auto& [x, y]: shields) {
    cin >> x >> y;
    x = getindex_x(x);
    y = getindex_y(y);
  }
 
  int numx = sz(x_indexer), numy = sz(y_indexer);
  auto xnode = [&](int ind){return ind;};
  auto ynode = [&](int ind){return ind + numx;};
  auto invnode = [&](int i){ // node i -> (index, in left set)
                   if (i >= 0 and i < numx) return pair{i, true};
                   else if (i >= numx and i < numx + numy) return pair{i - numx, false};
                   else assert(false);
                 };
  for (auto& [x, y]: shields) x = xnode(x), y = ynode(y);
  
  int nn = numx + numy + 2;
  auto src = nn - 2, snk = nn - 1;
  FlowWithDemands<dinic> mf(nn);
  vi total(numx + numy), maxdiff(numx + numy, n + 1);
  for (const auto& [x, y]: shields) {
    mf.addEdge(x, y, 0, 1);
    total[x]++, total[y]++;
  }
  rep(i, 0, m) {
    int t, l, d;
    cin >> t >> l >> d;
    int node = -1;
    if (t == 1) {
      auto x = getindex_x(l);
      if (x >= numx) continue;
      else node = xnode(x);
    } else { assert(t == 2);
      auto y = getindex_y(l);
      if (y >= numy) continue;
      else node = ynode(y);
    } assert(node != -1);
    maxdiff[node] = min(maxdiff[node], d);
  }
  rep(i, 0, numx + numy) {
    maxdiff[i] = min(maxdiff[i], total[i]);
    auto lo = (total[i] - maxdiff[i] + 1) / 2;
    auto hi = (total[i] + maxdiff[i]) / 2;
    auto [__, on_left] = invnode(i);
    if (on_left) mf.addEdge(src, i, lo, hi);
    else mf.addEdge(i, snk, lo, hi);
  }
  auto res = mf.maxflow(src, snk);
  if (!res) cout << -1 << '\n';
  else {
    auto [flow, construction] = *res;
    auto sol = (ll) flow * small + (ll) (n - flow) * big;
    string tape{};
    for (const auto& [x, y]: shields) {
      if (construction[{x, y}]-- > 0) tape += smallch;
      else tape += bigch;
    }
    cout << sol << '\n';
    cout << tape << '\n';
  }
}
