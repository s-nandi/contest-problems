// bfs (sh path), expanded state graph, bitmasks
// https://utipc20s.kattis.com/problems/utipc20s.templemaze
// 2020 UT Spring Programming Contest

#include <bits/stdc++.h>
using namespace std;

#define rep(i, a, b) for(auto i = (a); i < (b); ++i)

int n;
const int MAXN = 200;
const int MAXS = 1 << 10;
char grid[MAXN + 5][MAXN + 5];
int dist[MAXN + 5][MAXN + 5][MAXS + 5];
using state = tuple<int, int, int>; // x, y, bm
array dx = {0, -1, 0, 1};
array dy = {-1, 0, 1, 0};
bool inbounds(int i, int j){return i >=0 and j >= 0 and i < n and j < n;}
int gate(char c){return (isalpha(c) and isupper(c)) ? c - 'A' : -1;}
int lever(char c){return (isalpha(c) and islower(c)) ? c - 'a' : -1;}

auto minn(auto& a, auto b){
  if (b < a or (a == -1 and b != -1)){a = b; return true;}
  return false;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  int sx, sy, tx, ty;
  rep(i, 0, n) rep(j, 0, n) {
    cin >> grid[i][j];
    if (grid[i][j] == '@') tie(sx, sy) = tuple{i, j};
    else if (grid[i][j] == '$') tie(tx, ty) = tuple{i, j};
  }
  queue<state> q;
  q.push({sx, sy, 0});
  memset(dist, -1, sizeof(dist));
  dist[sx][sy][0] = 0;
  while (!q.empty()) {
    auto [x, y, bm] = q.front(); q.pop();
    auto c  = grid[x][y];
    if (x == tx and y == ty) {
      cout << dist[x][y][bm] << '\n';
      exit(0);
    }
    auto nbm = bm;
    if (lever(c) != -1)
      nbm |= 1 << lever(c);
    rep(k, 0, 4) {
      auto nx = x + dx[k];
      auto ny = y + dy[k];
      if (!inbounds(nx, ny)) continue;
      if (grid[nx][ny] == '#') continue;
      if (gate(c) != -1 and ~nbm & (1 << gate(c))) continue;
      if (minn(dist[nx][ny][nbm], dist[x][y][bm] + 1))
        q.push({nx, ny, nbm});
    }
  }
  cout << "IMPOSSIBLE" << '\n';
}
