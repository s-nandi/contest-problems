// min cut (penalty construction)
// https://www.codechef.com/MAY20A/problems/NRWP

#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define sz(x) (int)(x).size()

struct edge{int to;};
using graph = vector<vector<edge>>;

struct Dinic {
  struct Edge {
    int to, rev;
    ll c, oc;
    ll flow() { return max(oc - c, 0LL); }
  };
  vi lvl, ptr, q;
  vector<vector<Edge>> adj;
  Dinic(int n) : lvl(n), ptr(n), q(n), adj(n) {}
  void addEdge(int a, int b, ll c, int rcap = 0) {
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
    rep(L,0,31) do {
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

const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  while (T--) {
    int r, c, n;
    cin >> r >> c >> n;
    auto grid = vector(r, vi(c));
    auto side = vector(r, vi(c, -1));
    auto index = vector(r, vi(c));
    auto val = vector(r, vi(c));
    rep(i, 0, r) rep(j, 0, c) 
      cin >> grid[i][j];
    
    int base = 0;
    rep(i, 0, n) {
      int x, y, p;
      cin >> x >> y >> p;
      --x; --y;
      side[x][y] = grid[x][y] > 0 ? 1 : 0;
      index[x][y] = i;
      val[x][y] = p;
      base += abs(val[x][y] * grid[x][y]);
    }
    
    int nn = n + 2;
    int src = nn - 2, snk = nn - 1;
    Dinic dnc(nn);
    int bonus = 0;
    rep(i, 0, r) rep(j, 0, c) {
      if (side[i][j] == -1) continue;
      auto value = abs(grid[i][j] * val[i][j]);
      if (side[i][j] == 0) dnc.addEdge(src, index[i][j], 2 * value);
      else dnc.addEdge(index[i][j], snk, 2 * value);
      rep(k, 0, 4) {
        auto nx = i + dx[k];
        auto ny = j + dy[k];
        if (nx < 0 or ny < 0 or nx >= r or ny >= c) continue;
        if (side[nx][ny] == -1) continue;
        auto penalty = val[i][j] * val[nx][ny];
        bonus += penalty;
        dnc.addEdge(index[i][j], index[nx][ny], 2 * penalty);
      }
    }
    auto best = dnc.calc(src, snk);
    auto res = base + bonus / 2 - best;
    vi sign(n);
    rep(i, 0, r) rep(j, 0, c) {
      if (side[i][j] == -1) continue;
      sign[index[i][j]] = dnc.leftOfMinCut(index[i][j]) ? -1 : 1;
    }
    cout << res << '\n';
    trav(i, sign) cout << i << " "; cout << '\n';
  }
}
