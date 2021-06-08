// bottleneck sh. path queries (binary lifting, MST)
// https://codeforces.com/gym/102021 (problem M)
// 2018 German Collegiate Programming Contest

#include <bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(auto i=(a); i<(b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(x) begin(x),end(x)
#define sz(x) (int)size(x)
#define PB push_back
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int,int>;
 
constexpr bool dbg = false;
 
struct edge{int to, w;};
using graph = vector<vector<edge>>;
 
const int INF = 1031231324;
const int MAXLOG = 19;
 
const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};
 
auto inbounds(int x, int y, int n, int m){return x >= 0 and y >= 0 and x < n and y < m;}
 
struct UF {
  vi e;
  UF (int n) : e(n, -1) {}
  int find(int x){return e[x] < 0 ? x : e[x] = find(e[x]);}
  bool join(int a, int b) {
    a = find(a), b = find(b);
    if (a == b) return false;
    if (e[a] > e[b]) swap(a, b);
    e[a] += e[b]; e[b] = a;
    return true;
  }
};
 
graph MST(int n, auto& edges) {
  UF dsu(n);
  sort(all(edges));
  graph g(n);
  for (const auto& [w, u, v]: edges) {
    if (dsu.join(u, v)) {
      g[u].PB({v, w});
      g[v].PB({u, w});
    }
  }
  return g;
}
 
void dfs(const auto& g, int i, auto& depth, auto& jmp, auto& maxs, int p, int pcost, int dep) {
  jmp[0][i] = p;
  maxs[0][i] = pcost;
  depth[i] = dep;
  trav(e, g[i]) if (e.to != p)
    dfs(g, e.to, depth, jmp, maxs, i, e.w, dep + 1);
}
 
void treeJump(int n, auto& jmp, auto& maxs){
  rep(lev, 1, MAXLOG) {
    rep(i, 0, n) {
      auto anc = jmp[lev - 1][i];
      jmp[lev][i] = jmp[lev - 1][anc];
      maxs[lev][i] = max(maxs[lev - 1][i], maxs[lev - 1][anc]);
    }
  }
}
 
int jmpacc(const auto& tbl, const auto& maxs, int nod, int steps) {
  auto acc = -INF;
  rep(i,0,sz(tbl))
    if(steps&(1<<i)) {
      acc = max(acc, maxs[i][nod]);
      nod = tbl[i][nod];
    }
  return acc;
}
 
int jmp(const vector<vi>& tbl, int nod, int steps){
  rep(i,0,sz(tbl))
    if(steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}
 
int lca(const vector<vi>& tbl, const vi& depth, int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  a = jmp(tbl, a, depth[a] - depth[b]);
  if (a == b) return a;
  for (int i = sz(tbl); i--;) {
    int c = tbl[i][a], d = tbl[i][b];
    if (c != d) a = c, b = d;
  }
  return tbl[0][a];
}
 
int calc(const auto& tbl, const auto& maxs, const auto& depth, int a, int b) {
  int c = lca(tbl, depth, a, b);
  auto a_res = jmpacc(tbl, maxs, a, depth[a] - depth[c]);    
  auto b_res = jmpacc(tbl, maxs, b, depth[b] - depth[c]);
  return max(a_res, b_res);
}
 
int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);
 
  int n, m, q;
  cin >> n >> m >> q;
  auto h = vector(n, vi(m));
  rep(i, 0, n) rep(j, 0, m) cin >> h[i][j];
  vector<array<int, 4>> qs(q);
  trav(qry, qs) trav(coord, qry) {cin >> coord; --coord;}
 
  int nn = n * m;
  auto indexof = [&](int i, int j){return i * m + j;};
 
  vector<tuple<int, int, int>> edges;
  rep(i, 0, n) rep(j, 0, m) {
    rep(k, 0, 4) {
      auto nx = i + dx[k];
      auto ny = j + dy[k];
      if (!inbounds(nx, ny, n, m)) continue;
      edges.PB({max(h[i][j], h[nx][ny]), indexof(i, j), indexof(nx, ny)});
    }
  }
  auto g = MST(nn, edges);
  
  vi depth(nn);
  auto jmp = vector(MAXLOG, vi(nn));
  auto maxs = vector(MAXLOG, vi(nn, -INF));
  dfs(g, 0, depth, jmp, maxs, 0, -INF, 0);
  treeJump(nn, jmp, maxs);
 
  vi res(q);
  rep(it, 0, q) {
    const auto& [x1, y1, x2, y2] = qs[it];
    auto u = indexof(x1, y1), v = indexof(x2, y2);
    if (x1 == x2 and y1 == y2) res[it] = h[x1][y1];
    else res[it] = calc(jmp, maxs, depth, u, v);
  }
  trav(elem, res) cout << elem << '\n';
}
