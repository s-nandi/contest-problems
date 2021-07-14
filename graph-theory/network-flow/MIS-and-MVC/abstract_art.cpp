// Konig's theorem (construction, find vertices that MUST be in every MVC), mvc nodes on right side of construction must be in every MVC (proof?) -- flip L/R sets to find all such nodes 
// http://serjudging.vanb.org/?p=1305
// 2018 Southeast USA Regional
// Note: not on any online judge, check against tests locally

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

struct edge{int to;};
using graph = vector<vector<edge>>;

constexpr auto dbg = false;

const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};

struct Dinic {
  struct edge{int to, id;};
  using graph = vector<vector<edge>>;
  using flowT = int;
  static constexpr flowT INF = numeric_limits<flowT>::max();
  
  graph g;
  vector<flowT> cap, flow;
  vi lvl, ptr;
  Dinic(int s) : g(s), lvl(s), ptr(s) {}
  void addEdge(int from, int to, flowT capacity) {
    g[from].PB({to, sz(flow)});
    cap.PB(capacity), flow.PB(0);
    g[to].PB({from, sz(flow)});
    cap.PB(0), flow.PB(0);
  }
  flowT residual(int id) { return cap[id] - flow[id]; }
  bool build(int s, int t) {
    queue<int> q;
    q.push(s);
    fill(all(lvl), -1);
    lvl[s] = 0;
    while (!q.empty()) {
      int i = q.front();
      q.pop();
      trav(e, g[i])
        if (lvl[e.to] == -1 and residual(e.id) > 0)
          q.push(e.to), lvl[e.to] = lvl[i] + 1;
    }
    return lvl[t] != -1;
  }
  flowT push(int i, int t, flowT lo = INF) {
    if (i == t) return lo;
    for (; ptr[i] < sz(g[i]); ptr[i]++) {
      edge e = g[i][ptr[i]];
      if (lvl[e.to] == lvl[i] + 1 and residual(e.id) > 0) {
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
      fill(all(ptr), 0);
      while (auto delta = push(s, t)) res += delta;
    }
    return res;
  }
  bool leftOfMinCut(int a) { return lvl[a] != -1; }
};

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  auto grid = vector(n, string{});
  trav(row, grid) cin >> row;

  auto indexof = [&](int i, int j){return i * m + j;};
  auto inbounds = [&](int i, int j){return i >= 0 and j >= 0 and i < n and j < m;};

  map<char, int> freq;
  rep(i, 0, n) rep(j, 0, m) if (grid[i][j] != '#')
    freq[grid[i][j]]++;

  set<pii> musttake;
  auto checkavoid = [&](int iter) {
                      auto inleft = [&](int i, int j){return (i + j) % 2 == (iter & 1);};
                      
                      int nn = n * m + 2;
                      int src = nn - 2, snk = nn - 1;
                      Dinic dnc(nn);
                      int tot = 0;
                      rep(i, 0, n) rep(j, 0, m) {
                        if (grid[i][j] == '#') continue;
                        tot++;
                        if (inleft(i, j)) dnc.addEdge(src, indexof(i, j), 1);
                        else dnc.addEdge(indexof(i, j), snk, 1);
                        rep(k, 0, sz(dx)) {
                          auto nx = i + dx[k];
                          auto ny = j + dy[k];
                          if (!inbounds(nx, ny)) continue;
                          if (grid[nx][ny] == '#') continue;
                          if (grid[i][j] != grid[nx][ny] and inleft(i, j)) {
                            dnc.addEdge(indexof(i, j), indexof(nx, ny), 1);
                          }
                        }
                      }
                      auto best = dnc.calc(src, snk);
                      vi mvc;
                      rep(i, 0, n) rep(j, 0, m) {
                        if (grid[i][j] == '#') continue;
                        auto ind = indexof(i, j);
                        if (inleft(i, j) and !dnc.leftOfMinCut(ind)) {
                          mvc.PB(ind);
                        }
                        if (!inleft(i, j) and dnc.leftOfMinCut(ind)) {
                          musttake.insert({i, j});
                          mvc.PB(ind);
                        }
                      }
                      assert(sz(mvc) == best);
                      return mvc;
                    };
  vi mvc;
  mvc = checkavoid(0);
  mvc = checkavoid(1);
  
  for (const auto& [i, j]: musttake) {
    assert(grid[i][j] != '#');
    freq[grid[i][j]]--;
  }

  cout << sz(mvc) << '\n';
  for (const auto& [ch, cnt]: freq) {
    if (cnt > 0)
      cout << ch;
  }
  cout << '\n';
}
