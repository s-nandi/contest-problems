// nontrivial graph construction, tree distance
// https://codeforces.com/gym/102021 (problem A)
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
using pii = array<int,2>;

constexpr bool dbg = false;

struct edge{int to;};
using graph = vector<vector<edge>>;

int n, m;
const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};
auto printnode(int i) {
  stringstream ss;
  ss << "(" << (i / m) << ", " << (i % m) << ")";
  return ss.str();
}
auto indexof(int i, int j){return i * m + j;}

void dfs(const auto& grid, int x, int y, auto& depth, auto& par, int px, int py, int dep) {
  par[indexof(x, y)] = indexof(px, py);
  depth[indexof(x, y)] = dep;
  rep(k, 0, 4) {
    auto nx = x + dx[k];
    auto ny = y + dy[k];
    if (nx < 0 or ny < 0 or nx >= n or ny >= m) continue;
    if (nx == px and ny == py) continue;
    if (k & 1) { // up/down
      if (k == 1 and grid[x][2 * y + 1] == '_') continue;
      if (k == 3 and grid[x + 1][2 * y + 1] == '_') continue ;
    } else { // left/right
      auto prev = 2 * y + 1;
      auto nw = 2 * ny + 1;
      if (grid[x + 1][(prev + nw) / 2] == '|') continue;
    }
    dfs(grid, nx, ny, depth, par, x, y, dep + 1);
  }
}

vector<vi> treeJump(vi& P){
  int on = 1, d = 1;
  while(on < sz(P)) on *= 2, d++;
  vector<vi> jmp(d, P);
  rep(i,1,d) rep(j,0,sz(P))
    jmp[i][j] = jmp[i-1][jmp[i-1][j]];
  return jmp;
}

int jmp(vector<vi>& tbl, int nod, int steps){
  rep(i,0,sz(tbl))
    if(steps&(1<<i)) nod = tbl[i][nod];
  return nod;
}

int lca(vector<vi>& tbl, vi& depth, int a, int b) {
  if (depth[a] < depth[b]) swap(a, b);
  a = jmp(tbl, a, depth[a] - depth[b]);
  if (a == b) return a;
  for (int i = sz(tbl); i--;) {
    int c = tbl[i][a], d = tbl[i][b];
    if (c != d) a = c, b = d;
  }
  return tbl[0][a];
}

int32_t main() {
  cin.sync_with_stdio(0); cin.tie(0);
  cin.exceptions(cin.failbit);

  cin >> n >> m;
  cin.ignore();
  auto grid = vector(n + 1, string{});
  trav(row, grid) {
    string s;
    getline(cin, s);
    while (sz(s) < 2 * m + 1) s += ' ';
    row = s;
  }
  int k;
  cin >> k;
  vector<pii> checkpoints(k);
  trav(c, checkpoints) trav(coord, c) {cin >> coord; --coord;}

  int nn = n * m;
  vi par(nn);
  vi depth(nn);
  dfs(grid, 0, 0, depth, par, 0, 0, 0);

  if (dbg){
    rep(i, 0, n + 1) {
      rep(j, 0, 2 * m + 1) {
        cout << (grid[i][j] != ' ' ? 'x' : 'o');
      }
      cout << endl;
    }
    rep(i, 0, nn) {
      auto j = par[i];
      cout << printnode(j) << " -> " << printnode(i) << endl;
    }
  }

  ll acc = 0;
  auto jmp = treeJump(par);
  rep(i, 0, k - 1) {
    auto u = indexof(checkpoints[i][0], checkpoints[i][1]);
    auto v = indexof(checkpoints[i + 1][0], checkpoints[i + 1][1]);
    auto anc = lca(jmp, depth, u, v);
    auto dist = depth[u] + depth[v] - 2 * depth[anc];
    acc += dist;
  }
  cout << acc << '\n';
}
