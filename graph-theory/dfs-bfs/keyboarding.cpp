// bfs, precomputing adjacency table (skipping identical adjacent characters)
// https://open.kattis.com/problems/keyboard
// 2015 World Finals

#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
using ld = long double;
using vi = vector<int>;
using pii = pair<int, int>;
 
#define rep(i, a, b) for(auto i = (a); i < (b); ++i)
#define trav(a, x) for(auto& a : x)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define PB push_back
 
using state = tuple<int, int, int>; // x, y, tape pos
 
const auto dx = vector{0, -1, 0, 1};
const auto dy = vector{-1, 0, 1, 0};
 
const int MAXR = 50;
const int INF = 1031231234;
const pii NIL = {-1, -1};
 
auto inbounds(unsigned i, unsigned j, int n, int m) {return i < n and j < m;}
auto minn(auto& a, auto b) {return b < a ? a = b, true : false;}

int bfs(const auto& grid, const auto& neighbor, const string& s, int n, int m) {
  auto dist = vector(n, vector(m, vi(sz(s) + 1, INF)));
  dist[0][0][0] = 0;
  queue<state> q;
  q.push({0, 0, 0});
  while (!q.empty()) {
    auto [x, y, it] = q.front(); q.pop();
    auto& d = dist[x][y][it];
    if (it == sz(s)) {
      return d;
    }
    if (grid[x][y] == s[it]) {
      if (minn(dist[x][y][it + 1], d + 1))
        q.push({x, y, it + 1});
    } else {
      rep(k, 0, 4) {
        if (neighbor[k][x][y] == NIL) continue;
        const auto& [nx, ny] = neighbor[k][x][y];
        if (minn(dist[nx][ny][it], d + 1))
          q.push({nx, ny, it});
      }
    }
  }
  assert(false);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;
  auto grid = vector(n, vector<char>(m));
  trav(row, grid) trav(elem, row) cin >> elem;
  
  string s;
  cin >> s;
  s += '*';

  auto neighbor = vector(4, vector(n, vector<pii>(m)));
  rep(i, 0, n) {
    rep(j, 0, m) {
      rep(k, 0, 4) {
        neighbor[k][i][j] = NIL;
        rep(d, 1, MAXR + 1) {
          auto nx = i + dx[k] * d;
          auto ny = j + dy[k] * d;
          if (!inbounds(nx, ny, n, m)) break;
          if (grid[nx][ny] != grid[i][j]) {
            neighbor[k][i][j] = {nx, ny};
            break;
          }
        }
      }
    }
  }
  auto res = bfs(grid, neighbor, s, n, m);
  cout << res << '\n';
}
