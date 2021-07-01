// flow (hard construction), start with a brick per '#' and find max merges, max indep set on bipartite
// https://codeforces.com/contest/1404/problem/E

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

constexpr auto dbg = false;

struct edge{int to, id;};
using graph = vector<vector<edge>>;
using flowT = int;
constexpr auto INF = 1031231234;
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

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  auto grid = vector(n, string{});
  trav(row, grid) cin >> row;

  auto indexof = [&](int i, int j){return i * m + j;};
  vector<pii> verticals, horizontals;

  int base = 0;
  rep(i, 0, n) rep(j, 0, m) {
    base += grid[i][j] == '#';
    if (i + 1 < n and grid[i][j] == '#' and grid[i + 1][j] == '#') {
      verticals.PB({indexof(i, j), indexof(i + 1, j)});
    }
    if (j + 1 < m and grid[i][j] == '#' and grid[i][j + 1] == '#') {
      horizontals.PB({indexof(i, j), indexof(i, j + 1)});
    }
  }

  int nn = sz(verticals) + sz(horizontals) + 2;
  int src = nn - 2, snk = nn -1;

  dinic dnc(nn);
  rep(i, 0, sz(verticals))
    dnc.addEdge(src, i, 1);
  rep(j, 0, sz(horizontals))
    dnc.addEdge(sz(verticals) + j, snk, 1);
  rep(i, 0, sz(verticals)) rep(j, 0, sz(horizontals)) {
    bool conflict = false;
    conflict |= (verticals[i].first == horizontals[j].first);
    conflict |= (verticals[i].first == horizontals[j].second);
    conflict |= (verticals[i].second == horizontals[j].first);
    conflict |= (verticals[i].second == horizontals[j].second);
    auto from = i, to = sz(verticals) + j;
    if (conflict)
      dnc.addEdge(from, to, 1);
  }
  auto mf = dnc.maxflow(src, snk);
  auto merges = sz(verticals) + sz(horizontals) - mf;
  cout << (base - merges) << '\n';
}
