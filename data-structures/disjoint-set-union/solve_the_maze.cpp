// DSU, greedy (blocking 4 squares around B's is optimal), checking path between two nodes
// https://codeforces.com/contest/1365/problem/D

#include <bits/stdc++.h>
using namespace std;
 
using vi = vector<int>;
using ll = long long;
using ld = long double;
 
#define rep(i,a,b) for(auto i = (a); i < (b); ++i)
#define trav(a,x) for(auto& a: x)
#define all(a) begin(a),end(a)
#define sz(a) (int)size(a)
#define PB push_back
 
struct edge{int to;};
using graph = vector<vector<edge>>;
 
const vi dx = {0, -1, 0, 1};
const vi dy = {-1, 0, 1, 0};
 
bool inbounds(int i, int j, int n, int m) {
  return i >= 0 and j >= 0 and i < n and j < m;
}
 
struct DSU {
  vi par;
  DSU(int n) : par(n) {iota(all(par), 0);}
  int find(int i){return (par[i] == i ? i : (par[i] = find(par[i])));}
  void join(int i, int j) {
    par[find(i)] = find(j);
  }
  bool same(int i, int j) {
    return find(i) == find(j);
  }
};
 
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
 
  int T;
  cin >> T;
  while(T--) {
    int n,m ;
    cin >> n >> m;
    auto grid = vector(n, vector<char>(m));
    trav(r, grid) trav(e, r) cin >> e;
 
    bool bad = false;
    rep(i, 0, n) {
      rep(j, 0, m) {
        if (grid[i][j] == 'B') {
          rep(k, 0, 4) {
            auto nx = i + dx[k];
            auto ny = j + dy[k];
            if (!inbounds(nx, ny, n, m)) continue;
            if (grid[nx][ny] == '.') grid[nx][ny] = '#';
            else if (grid[nx][ny] == 'G') bad = true;
          }
        }
      }
    }
    if (!bad) {
      DSU dsu(n * m);
      rep(i, 0, n) rep(j, 0, m) {
        if (grid[i][j] == 'G' or grid[i][j] == '.') {
          rep(k, 0, 4) {
            auto nx = i + dx[k];
            auto ny = j + dy[k];
            if (!inbounds(nx, ny, n, m)) continue;
            if (grid[nx][ny] != '.' and grid[nx][ny] != 'G') continue;
            dsu.join(i * m + j, nx * m + ny);
          }
        }
      }
      int lind = (n - 1) * m + (m - 1);
      rep(i, 0, n) rep(j, 0, m) {
        if (grid[i][j] != 'G') continue;
        auto ind = i * m + j;
        if (!dsu.same(lind, ind)) bad = true;
      }
    }
    cout << (bad ? "No" : "Yes") << '\n';
  }
}
